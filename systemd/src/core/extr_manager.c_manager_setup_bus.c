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
 int /*<<< orphan*/  MANAGER_IS_RELOADING (int /*<<< orphan*/ *) ; 
 scalar_t__ MANAGER_IS_SYSTEM (int /*<<< orphan*/ *) ; 
 scalar_t__ MANAGER_IS_USER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_init_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_init_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_init_system (int /*<<< orphan*/ *) ; 
 scalar_t__ manager_dbus_is_running (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void manager_setup_bus(Manager *m) {
        assert(m);

        /* Let's set up our private bus connection now, unconditionally */
        (void) bus_init_private(m);

        /* If we are in --user mode also connect to the system bus now */
        if (MANAGER_IS_USER(m))
                (void) bus_init_system(m);

        /* Let's connect to the bus now, but only if the unit is supposed to be up */
        if (manager_dbus_is_running(m, MANAGER_IS_RELOADING(m))) {
                (void) bus_init_api(m);

                if (MANAGER_IS_SYSTEM(m))
                        (void) bus_init_system(m);
        }
}