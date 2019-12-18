#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long long psync_initial_offset; int flags; int /*<<< orphan*/  conn; int /*<<< orphan*/  replstate; } ;
typedef  TYPE_1__ client ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int slaveseldb; char* replid; } ;

/* Variables and functions */
 int CLIENT_PRE_PSYNC ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  SLAVE_STATE_WAIT_BGSAVE_END ; 
 int connWrite (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  freeClientAsync (TYPE_1__*) ; 
 TYPE_2__ server ; 
 int snprintf (char*,int,char*,char*,long long) ; 

int replicationSetupSlaveForFullResync(client *slave, long long offset) {
    char buf[128];
    int buflen;

    slave->psync_initial_offset = offset;
    slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
    /* We are going to accumulate the incremental changes for this
     * slave as well. Set slaveseldb to -1 in order to force to re-emit
     * a SELECT statement in the replication stream. */
    server.slaveseldb = -1;

    /* Don't send this reply to slaves that approached us with
     * the old SYNC command. */
    if (!(slave->flags & CLIENT_PRE_PSYNC)) {
        buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
                          server.replid,offset);
        if (connWrite(slave->conn,buf,buflen) != buflen) {
            freeClientAsync(slave);
            return C_ERR;
        }
    }
    return C_OK;
}