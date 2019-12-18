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
typedef  int pid_t ;
struct TYPE_4__ {void* done_handler_user_data; int /*<<< orphan*/  done_handler; } ;
struct TYPE_3__ {int module_child_pid; } ;
typedef  int /*<<< orphan*/  RedisModuleForkDoneHandler ;

/* Variables and functions */
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  closeChildInfoPipe () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ hasActiveChildProcess () ; 
 TYPE_2__ moduleForkInfo ; 
 int /*<<< orphan*/  openChildInfoPipe () ; 
 int redisFork () ; 
 int /*<<< orphan*/  redisSetProcTitle (char*) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int) ; 
 int strerror (int /*<<< orphan*/ ) ; 

int RM_Fork(RedisModuleForkDoneHandler cb, void *user_data) {
    pid_t childpid;
    if (hasActiveChildProcess()) {
        return -1;
    }

    openChildInfoPipe();
    if ((childpid = redisFork()) == 0) {
        /* Child */
        redisSetProcTitle("redis-module-fork");
    } else if (childpid == -1) {
        closeChildInfoPipe();
        serverLog(LL_WARNING,"Can't fork for module: %s", strerror(errno));
    } else {
        /* Parent */
        server.module_child_pid = childpid;
        moduleForkInfo.done_handler = cb;
        moduleForkInfo.done_handler_user_data = user_data;
        serverLog(LL_NOTICE, "Module fork started pid: %d ", childpid);
    }
    return childpid;
}