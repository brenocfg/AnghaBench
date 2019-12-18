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
struct TYPE_4__ {int /*<<< orphan*/ * done_handler_user_data; int /*<<< orphan*/  (* done_handler ) (int,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int module_child_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_NOTICE ; 
 TYPE_2__ moduleForkInfo ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ *) ; 

void ModuleForkDoneHandler(int exitcode, int bysignal) {
    serverLog(LL_NOTICE,
        "Module fork exited pid: %d, retcode: %d, bysignal: %d",
        server.module_child_pid, exitcode, bysignal);
    if (moduleForkInfo.done_handler) {
        moduleForkInfo.done_handler(exitcode, bysignal,
            moduleForkInfo.done_handler_user_data);
    }
    server.module_child_pid = -1;
    moduleForkInfo.done_handler = NULL;
    moduleForkInfo.done_handler_user_data = NULL;
}