#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_7__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_8__ {scalar_t__ replstate; int id; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ client ;
struct TYPE_9__ {int rdb_child_pid; int rdb_save_time_start; int /*<<< orphan*/  slaves; int /*<<< orphan*/  rdb_pipe_write_result_to_parent; int /*<<< orphan*/  rdb_pipe_read_result_from_child; int /*<<< orphan*/  rdb_child_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_ERR ; 
 int /*<<< orphan*/  C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  RDB_CHILD_TYPE_NONE ; 
 int /*<<< orphan*/  RDB_CHILD_TYPE_SOCKET ; 
 scalar_t__ SLAVE_STATE_WAIT_BGSAVE_END ; 
 int /*<<< orphan*/  anetNonBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anetSendTimeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeClient (TYPE_2__*) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int replicationGetSlaveName (TYPE_2__*) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  updateSlavesWaitingBgsave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int*) ; 
 int* zmalloc (int) ; 
 int* zrealloc (int*,int) ; 

void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
    uint64_t *ok_slaves;

    if (!bysignal && exitcode == 0) {
        serverLog(LL_NOTICE,
            "Background RDB transfer terminated with success");
    } else if (!bysignal && exitcode != 0) {
        serverLog(LL_WARNING, "Background transfer error");
    } else {
        serverLog(LL_WARNING,
            "Background transfer terminated by signal %d", bysignal);
    }
    server.rdb_child_pid = -1;
    server.rdb_child_type = RDB_CHILD_TYPE_NONE;
    server.rdb_save_time_start = -1;

    /* If the child returns an OK exit code, read the set of slave client
     * IDs and the associated status code. We'll terminate all the slaves
     * in error state.
     *
     * If the process returned an error, consider the list of slaves that
     * can continue to be empty, so that it's just a special case of the
     * normal code path. */
    ok_slaves = zmalloc(sizeof(uint64_t)); /* Make space for the count. */
    ok_slaves[0] = 0;
    if (!bysignal && exitcode == 0) {
        int readlen = sizeof(uint64_t);

        if (read(server.rdb_pipe_read_result_from_child, ok_slaves, readlen) ==
                 readlen)
        {
            readlen = ok_slaves[0]*sizeof(uint64_t)*2;

            /* Make space for enough elements as specified by the first
             * uint64_t element in the array. */
            ok_slaves = zrealloc(ok_slaves,sizeof(uint64_t)+readlen);
            if (readlen &&
                read(server.rdb_pipe_read_result_from_child, ok_slaves+1,
                     readlen) != readlen)
            {
                ok_slaves[0] = 0;
            }
        }
    }

    close(server.rdb_pipe_read_result_from_child);
    close(server.rdb_pipe_write_result_to_parent);

    /* We can continue the replication process with all the slaves that
     * correctly received the full payload. Others are terminated. */
    listNode *ln;
    listIter li;

    listRewind(server.slaves,&li);
    while((ln = listNext(&li))) {
        client *slave = ln->value;

        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
            uint64_t j;
            int errorcode = 0;

            /* Search for the slave ID in the reply. In order for a slave to
             * continue the replication process, we need to find it in the list,
             * and it must have an error code set to 0 (which means success). */
            for (j = 0; j < ok_slaves[0]; j++) {
                if (slave->id == ok_slaves[2*j+1]) {
                    errorcode = ok_slaves[2*j+2];
                    break; /* Found in slaves list. */
                }
            }
            if (j == ok_slaves[0] || errorcode != 0) {
                serverLog(LL_WARNING,
                "Closing slave %s: child->slave RDB transfer failed: %s",
                    replicationGetSlaveName(slave),
                    (errorcode == 0) ? "RDB transfer child aborted"
                                     : strerror(errorcode));
                freeClient(slave);
            } else {
                serverLog(LL_WARNING,
                "Slave %s correctly received the streamed RDB file.",
                    replicationGetSlaveName(slave));
                /* Restore the socket as non-blocking. */
                anetNonBlock(NULL,slave->fd);
                anetSendTimeout(NULL,slave->fd,0);
            }
        }
    }
    zfree(ok_slaves);

    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? C_OK : C_ERR, RDB_CHILD_TYPE_SOCKET);
}