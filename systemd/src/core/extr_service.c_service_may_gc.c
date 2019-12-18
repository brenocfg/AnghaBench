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
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  Service ;

/* Variables and functions */
 int /*<<< orphan*/ * SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ control_pid_good (int /*<<< orphan*/ *) ; 
 scalar_t__ main_pid_good (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool service_may_gc(Unit *u) {
        Service *s = SERVICE(u);

        assert(s);

        /* Never clean up services that still have a process around, even if the service is formally dead. Note that
         * unit_may_gc() already checked our cgroup for us, we just check our two additional PIDs, too, in case they
         * have moved outside of the cgroup. */

        if (main_pid_good(s) > 0 ||
            control_pid_good(s) > 0)
                return false;

        return true;
}