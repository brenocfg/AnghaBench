#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct redis_stat {scalar_t__ st_size; } ;
struct TYPE_8__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_9__ {scalar_t__ replstate; int slave_capa; int repl_put_online_on_ack; int repldbfd; int /*<<< orphan*/  fd; scalar_t__ repldbsize; int /*<<< orphan*/  replpreamble; scalar_t__ repldboff; int /*<<< orphan*/  repl_ack_time; } ;
typedef  TYPE_2__ client ;
struct TYPE_10__ {int /*<<< orphan*/  el; int /*<<< orphan*/  rdb_filename; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  slaves; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int RDB_CHILD_TYPE_SOCKET ; 
 scalar_t__ SLAVE_STATE_ONLINE ; 
 scalar_t__ SLAVE_STATE_SEND_BULK ; 
 scalar_t__ SLAVE_STATE_WAIT_BGSAVE_END ; 
 scalar_t__ SLAVE_STATE_WAIT_BGSAVE_START ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeClient (TYPE_2__*) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int redis_fstat (int,struct redis_stat*) ; 
 int /*<<< orphan*/  replicationGetSlaveName (TYPE_2__*) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sendBulkToSlave ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  startBgsaveForReplication (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
    listNode *ln;
    int startbgsave = 0;
    int mincapa = -1;
    listIter li;

    listRewind(server.slaves,&li);
    while((ln = listNext(&li))) {
        client *slave = ln->value;

        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
            startbgsave = 1;
            mincapa = (mincapa == -1) ? slave->slave_capa :
                                        (mincapa & slave->slave_capa);
        } else if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
            struct redis_stat buf;

            /* If this was an RDB on disk save, we have to prepare to send
             * the RDB from disk to the slave socket. Otherwise if this was
             * already an RDB -> Slaves socket transfer, used in the case of
             * diskless replication, our work is trivial, we can just put
             * the slave online. */
            if (type == RDB_CHILD_TYPE_SOCKET) {
                serverLog(LL_NOTICE,
                    "Streamed RDB transfer with replica %s succeeded (socket). Waiting for REPLCONF ACK from slave to enable streaming",
                        replicationGetSlaveName(slave));
                /* Note: we wait for a REPLCONF ACK message from slave in
                 * order to really put it online (install the write handler
                 * so that the accumulated data can be transferred). However
                 * we change the replication state ASAP, since our slave
                 * is technically online now. */
                slave->replstate = SLAVE_STATE_ONLINE;
                slave->repl_put_online_on_ack = 1;
                slave->repl_ack_time = server.unixtime; /* Timeout otherwise. */
            } else {
                if (bgsaveerr != C_OK) {
                    freeClient(slave);
                    serverLog(LL_WARNING,"SYNC failed. BGSAVE child returned an error");
                    continue;
                }
                if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
                    redis_fstat(slave->repldbfd,&buf) == -1) {
                    freeClient(slave);
                    serverLog(LL_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
                    continue;
                }
                slave->repldboff = 0;
                slave->repldbsize = buf.st_size;
                slave->replstate = SLAVE_STATE_SEND_BULK;
                slave->replpreamble = sdscatprintf(sdsempty(),"$%lld\r\n",
                    (unsigned long long) slave->repldbsize);

                aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
                if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE, sendBulkToSlave, slave) == AE_ERR) {
                    freeClient(slave);
                    continue;
                }
            }
        }
    }
    if (startbgsave) startBgsaveForReplication(mincapa);
}