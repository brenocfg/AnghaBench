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
struct TYPE_2__ {int aof_child_pid; int aof_rewrite_time_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  aofClosePipes () ; 
 int /*<<< orphan*/  aofRemoveTempFile (int) ; 
 int /*<<< orphan*/  aofRewriteBufferReset () ; 
 int /*<<< orphan*/  closeChildInfoPipe () ; 
 int kill (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  updateDictResizePolicy () ; 
 int wait3 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void killAppendOnlyChild(void) {
    int statloc;
    /* No AOFRW child? return. */
    if (server.aof_child_pid == -1) return;
    /* Kill AOFRW child, wait for child exit. */
    serverLog(LL_NOTICE,"Killing running AOF rewrite child: %ld",
        (long) server.aof_child_pid);
    if (kill(server.aof_child_pid,SIGUSR1) != -1) {
        while(wait3(&statloc,0,NULL) != server.aof_child_pid);
    }
    /* Reset the buffer accumulating changes while the child saves. */
    aofRewriteBufferReset();
    aofRemoveTempFile(server.aof_child_pid);
    server.aof_child_pid = -1;
    server.aof_rewrite_time_start = -1;
    /* Close pipes used for IPC between the two processes. */
    aofClosePipes();
    closeChildInfoPipe();
    updateDictResizePolicy();
}