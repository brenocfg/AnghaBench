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
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 scalar_t__ MANAGER_IS_RELOADING (int /*<<< orphan*/ *) ; 
 scalar_t__ MANAGER_IS_SYSTEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_done_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_done_system (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_init_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_init_system (int /*<<< orphan*/ *) ; 
 scalar_t__ manager_dbus_is_running (int /*<<< orphan*/ *,int) ; 

void manager_recheck_dbus(Manager *m) {
        assert(m);

        /* Connects to the bus if the dbus service and socket are running. If we are running in user mode this is all
         * it does. In system mode we'll also connect to the system bus (which will most likely just reuse the
         * connection of the API bus). That's because the system bus after all runs as service of the system instance,
         * while in the user instance we can assume it's already there. */

        if (MANAGER_IS_RELOADING(m))
                return; /* don't check while we are reloading… */

        if (manager_dbus_is_running(m, false)) {
                (void) bus_init_api(m);

                if (MANAGER_IS_SYSTEM(m))
                        (void) bus_init_system(m);
        } else {
                (void) bus_done_api(m);

                if (MANAGER_IS_SYSTEM(m))
                        (void) bus_done_system(m);
        }
}