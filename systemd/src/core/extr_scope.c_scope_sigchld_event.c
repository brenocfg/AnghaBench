#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_enqueue_rewatch_pids (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scope_sigchld_event(Unit *u, pid_t pid, int code, int status) {
        assert(u);

        /* If we get a SIGCHLD event for one of the processes we were interested in, then we look for others to
         * watch, under the assumption that we'll sooner or later get a SIGCHLD for them, as the original
         * process we watched was probably the parent of them, and they are hence now our children. */

        (void) unit_enqueue_rewatch_pids(u);
}