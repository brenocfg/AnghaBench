#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rio ;
typedef  int /*<<< orphan*/  rdbSaveInfo ;
typedef  int pid_t ;
struct TYPE_6__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  connection ;
struct TYPE_7__ {scalar_t__ replstate; int /*<<< orphan*/  conn; } ;
typedef  TYPE_2__ client ;
struct TYPE_8__ {int rdb_pipe_read; int rdb_pipe_write; int rdb_child_pid; int /*<<< orphan*/  el; int /*<<< orphan*/  rdb_child_type; int /*<<< orphan*/  rdb_save_time_start; scalar_t__ rdb_pipe_numconns_writing; scalar_t__ rdb_pipe_numconns; int /*<<< orphan*/ * rdb_pipe_conns; int /*<<< orphan*/  slaves; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  CHILD_INFO_TYPE_RDB ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  RDB_CHILD_TYPE_SOCKET ; 
 scalar_t__ SLAVE_STATE_WAIT_BGSAVE_END ; 
 scalar_t__ SLAVE_STATE_WAIT_BGSAVE_START ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  anetNonBlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closeChildInfoPipe () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exitFromChild (int) ; 
 int /*<<< orphan*/  getPsyncInitialOffset () ; 
 scalar_t__ hasActiveChildProcess () ; 
 int listLength (int /*<<< orphan*/ ) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openChildInfoPipe () ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  rdbPipeReadHandler ; 
 int rdbSaveRioWithEOFMark (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int redisFork () ; 
 int /*<<< orphan*/  redisSetProcTitle (char*) ; 
 int /*<<< orphan*/  replicationSetupSlaveForFullResync (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ rioFlush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rioFreeFd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rioInitWithFd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sendChildCOWInfo (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zmalloc (int) ; 

int rdbSaveToSlavesSockets(rdbSaveInfo *rsi) {
    listNode *ln;
    listIter li;
    pid_t childpid;
    int pipefds[2];

    if (hasActiveChildProcess()) return C_ERR;

    /* Even if the previous fork child exited, don't start a new one until we
     * drained the pipe. */
    if (server.rdb_pipe_conns) return C_ERR;

    /* Before to fork, create a pipe that is used to transfer the rdb bytes to
     * the parent, we can't let it write directly to the sockets, since in case
     * of TLS we must let the parent handle a continuous TLS state when the
     * child terminates and parent takes over. */
    if (pipe(pipefds) == -1) return C_ERR;
    server.rdb_pipe_read = pipefds[0];
    server.rdb_pipe_write = pipefds[1];
    anetNonBlock(NULL, server.rdb_pipe_read);

    /* Collect the connections of the replicas we want to transfer
     * the RDB to, which are i WAIT_BGSAVE_START state. */
    server.rdb_pipe_conns = zmalloc(sizeof(connection *)*listLength(server.slaves));
    server.rdb_pipe_numconns = 0;
    server.rdb_pipe_numconns_writing = 0;
    listRewind(server.slaves,&li);
    while((ln = listNext(&li))) {
        client *slave = ln->value;
        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
            server.rdb_pipe_conns[server.rdb_pipe_numconns++] = slave->conn;
            replicationSetupSlaveForFullResync(slave,getPsyncInitialOffset());
        }
    }

    /* Create the child process. */
    openChildInfoPipe();
    if ((childpid = redisFork()) == 0) {
        /* Child */
        int retval;
        rio rdb;

        rioInitWithFd(&rdb,server.rdb_pipe_write);

        redisSetProcTitle("redis-rdb-to-slaves");

        retval = rdbSaveRioWithEOFMark(&rdb,NULL,rsi);
        if (retval == C_OK && rioFlush(&rdb) == 0)
            retval = C_ERR;

        if (retval == C_OK) {
            sendChildCOWInfo(CHILD_INFO_TYPE_RDB, "RDB");
        }

        rioFreeFd(&rdb);
        close(server.rdb_pipe_write); /* wake up the reader, tell it we're done. */
        exitFromChild((retval == C_OK) ? 0 : 1);
    } else {
        /* Parent */
        if (childpid == -1) {
            serverLog(LL_WARNING,"Can't save in background: fork: %s",
                strerror(errno));

            /* Undo the state change. The caller will perform cleanup on
             * all the slaves in BGSAVE_START state, but an early call to
             * replicationSetupSlaveForFullResync() turned it into BGSAVE_END */
            listRewind(server.slaves,&li);
            while((ln = listNext(&li))) {
                client *slave = ln->value;
                if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
                    slave->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
                }
            }
            close(server.rdb_pipe_write);
            close(server.rdb_pipe_read);
            zfree(server.rdb_pipe_conns);
            server.rdb_pipe_conns = NULL;
            server.rdb_pipe_numconns = 0;
            server.rdb_pipe_numconns_writing = 0;
            closeChildInfoPipe();
        } else {
            serverLog(LL_NOTICE,"Background RDB transfer started by pid %d",
                childpid);
            server.rdb_save_time_start = time(NULL);
            server.rdb_child_pid = childpid;
            server.rdb_child_type = RDB_CHILD_TYPE_SOCKET;
            close(server.rdb_pipe_write); /* close write in parent so that it can detect the close on the child. */
            if (aeCreateFileEvent(server.el, server.rdb_pipe_read, AE_READABLE, rdbPipeReadHandler,NULL) == AE_ERR) {
                serverPanic("Unrecoverable error creating server.rdb_pipe_read file event.");
            }
        }
        return (childpid == -1) ? C_ERR : C_OK;
    }
    return C_OK; /* Unreached. */
}