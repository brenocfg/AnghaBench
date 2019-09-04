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
typedef  int /*<<< orphan*/  mstime_t ;
struct TYPE_2__ {int rdb_child_pid; int rdb_save_time_start; void* rdb_save_time_last; int /*<<< orphan*/  rdb_child_type; void* lastbgsave_status; void* lastsave; scalar_t__ dirty_before_bgsave; scalar_t__ dirty; } ;

/* Variables and functions */
 void* C_ERR ; 
 void* C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  RDB_CHILD_TYPE_DISK ; 
 int /*<<< orphan*/  RDB_CHILD_TYPE_NONE ; 
 int SIGUSR1 ; 
 int /*<<< orphan*/  latencyAddSampleIfNeeded (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latencyEndMonitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latencyStartMonitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdbRemoveTempFile (int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 void* time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updateSlavesWaitingBgsave (void*,int /*<<< orphan*/ ) ; 

void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {
    if (!bysignal && exitcode == 0) {
        serverLog(LL_NOTICE,
            "Background saving terminated with success");
        server.dirty = server.dirty - server.dirty_before_bgsave;
        server.lastsave = time(NULL);
        server.lastbgsave_status = C_OK;
    } else if (!bysignal && exitcode != 0) {
        serverLog(LL_WARNING, "Background saving error");
        server.lastbgsave_status = C_ERR;
    } else {
        mstime_t latency;

        serverLog(LL_WARNING,
            "Background saving terminated by signal %d", bysignal);
        latencyStartMonitor(latency);
        rdbRemoveTempFile(server.rdb_child_pid);
        latencyEndMonitor(latency);
        latencyAddSampleIfNeeded("rdb-unlink-temp-file",latency);
        /* SIGUSR1 is whitelisted, so we have a way to kill a child without
         * tirggering an error condition. */
        if (bysignal != SIGUSR1)
            server.lastbgsave_status = C_ERR;
    }
    server.rdb_child_pid = -1;
    server.rdb_child_type = RDB_CHILD_TYPE_NONE;
    server.rdb_save_time_last = time(NULL)-server.rdb_save_time_start;
    server.rdb_save_time_start = -1;
    /* Possibly there are slaves waiting for a BGSAVE in order to be served
     * (the first stage of SYNC is a bulk transfer of dump.rdb) */
    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? C_OK : C_ERR, RDB_CHILD_TYPE_DISK);
}