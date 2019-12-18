#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rdbSaveInfo ;
typedef  int pid_t ;
struct TYPE_2__ {int lastbgsave_status; int rdb_child_pid; int /*<<< orphan*/  rdb_child_type; void* rdb_save_time_start; void* lastbgsave_try; int /*<<< orphan*/  dirty; int /*<<< orphan*/  dirty_before_bgsave; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHILD_INFO_TYPE_RDB ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  RDB_CHILD_TYPE_DISK ; 
 int /*<<< orphan*/  closeChildInfoPipe () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exitFromChild (int) ; 
 scalar_t__ hasActiveChildProcess () ; 
 int /*<<< orphan*/  openChildInfoPipe () ; 
 int rdbSave (char*,int /*<<< orphan*/ *) ; 
 int redisFork () ; 
 int /*<<< orphan*/  redisSetProcTitle (char*) ; 
 int /*<<< orphan*/  sendChildCOWInfo (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 void* time (int /*<<< orphan*/ *) ; 

int rdbSaveBackground(char *filename, rdbSaveInfo *rsi) {
    pid_t childpid;

    if (hasActiveChildProcess()) return C_ERR;

    server.dirty_before_bgsave = server.dirty;
    server.lastbgsave_try = time(NULL);
    openChildInfoPipe();

    if ((childpid = redisFork()) == 0) {
        int retval;

        /* Child */
        redisSetProcTitle("redis-rdb-bgsave");
        retval = rdbSave(filename,rsi);
        if (retval == C_OK) {
            sendChildCOWInfo(CHILD_INFO_TYPE_RDB, "RDB");
        }
        exitFromChild((retval == C_OK) ? 0 : 1);
    } else {
        /* Parent */
        if (childpid == -1) {
            closeChildInfoPipe();
            server.lastbgsave_status = C_ERR;
            serverLog(LL_WARNING,"Can't save in background: fork: %s",
                strerror(errno));
            return C_ERR;
        }
        serverLog(LL_NOTICE,"Background saving started by pid %d",childpid);
        server.rdb_save_time_start = time(NULL);
        server.rdb_child_pid = childpid;
        server.rdb_child_type = RDB_CHILD_TYPE_DISK;
        return C_OK;
    }
    return C_OK; /* unreached */
}