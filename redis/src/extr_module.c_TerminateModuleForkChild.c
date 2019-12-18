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
struct TYPE_4__ {int /*<<< orphan*/ * done_handler_user_data; int /*<<< orphan*/ * done_handler; } ;
struct TYPE_3__ {int module_child_pid; } ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  closeChildInfoPipe () ; 
 int kill (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ moduleForkInfo ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  updateDictResizePolicy () ; 
 int wait4 (int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int TerminateModuleForkChild(int child_pid, int wait) {
    /* Module child should be active and pid should match. */
    if (server.module_child_pid == -1 ||
        server.module_child_pid != child_pid) return C_ERR;

    int statloc;
    serverLog(LL_NOTICE,"Killing running module fork child: %ld",
        (long) server.module_child_pid);
    if (kill(server.module_child_pid,SIGUSR1) != -1 && wait) {
        while(wait4(server.module_child_pid,&statloc,0,NULL) !=
              server.module_child_pid);
    }
    /* Reset the buffer accumulating changes while the child saves. */
    server.module_child_pid = -1;
    moduleForkInfo.done_handler = NULL;
    moduleForkInfo.done_handler_user_data = NULL;
    closeChildInfoPipe();
    updateDictResizePolicy();
    return C_OK;
}