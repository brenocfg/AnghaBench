#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int honor_device_enumeration; int /*<<< orphan*/  objective; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_OK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_catchup (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_enqueue_sync_bus_names (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_recheck_dbus (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_recheck_journal (TYPE_1__*) ; 

__attribute__((used)) static void manager_ready(Manager *m) {
        assert(m);

        /* After having loaded everything, do the final round of catching up with what might have changed */

        m->objective = MANAGER_OK; /* Tell everyone we are up now */

        /* It might be safe to log to the journal now and connect to dbus */
        manager_recheck_journal(m);
        manager_recheck_dbus(m);

        /* Sync current state of bus names with our set of listening units */
        (void) manager_enqueue_sync_bus_names(m);

        /* Let's finally catch up with any changes that took place while we were reloading/reexecing */
        manager_catchup(m);

        m->honor_device_enumeration = true;
}