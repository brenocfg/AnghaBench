#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rdbSaveInfo ;
typedef  int pid_t ;
struct TYPE_3__ {size_t cow_size; } ;
struct TYPE_4__ {int aof_child_pid; int rdb_child_pid; long long stat_fork_time; double stat_fork_rate; int lastbgsave_status; int /*<<< orphan*/  rdb_child_type; void* rdb_save_time_start; TYPE_1__ child_info_data; void* lastbgsave_try; int /*<<< orphan*/  dirty; int /*<<< orphan*/  dirty_before_bgsave; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHILD_INFO_TYPE_RDB ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  RDB_CHILD_TYPE_DISK ; 
 int /*<<< orphan*/  closeChildInfoPipe () ; 
 int /*<<< orphan*/  closeListeningSockets (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exitFromChild (int) ; 
 int fork () ; 
 int /*<<< orphan*/  latencyAddSampleIfNeeded (char*,int) ; 
 int /*<<< orphan*/  openChildInfoPipe () ; 
 int rdbSave (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redisSetProcTitle (char*) ; 
 int /*<<< orphan*/  sendChildInfo (int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 void* time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updateDictResizePolicy () ; 
 long long ustime () ; 
 size_t zmalloc_get_private_dirty (int) ; 
 scalar_t__ zmalloc_used_memory () ; 

int rdbSaveBackground(char *filename, rdbSaveInfo *rsi) {
    pid_t childpid;
    long long start;

    if (server.aof_child_pid != -1 || server.rdb_child_pid != -1) return C_ERR;

    server.dirty_before_bgsave = server.dirty;
    server.lastbgsave_try = time(NULL);
    openChildInfoPipe();

    start = ustime();
    if ((childpid = fork()) == 0) {
        int retval;

        /* Child */
        closeListeningSockets(0);
        redisSetProcTitle("redis-rdb-bgsave");
        retval = rdbSave(filename,rsi);
        if (retval == C_OK) {
            size_t private_dirty = zmalloc_get_private_dirty(-1);

            if (private_dirty) {
                serverLog(LL_NOTICE,
                    "RDB: %zu MB of memory used by copy-on-write",
                    private_dirty/(1024*1024));
            }

            server.child_info_data.cow_size = private_dirty;
            sendChildInfo(CHILD_INFO_TYPE_RDB);
        }
        exitFromChild((retval == C_OK) ? 0 : 1);
    } else {
        /* Parent */
        server.stat_fork_time = ustime()-start;
        server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
        latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
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
        updateDictResizePolicy();
        return C_OK;
    }
    return C_OK; /* unreached */
}