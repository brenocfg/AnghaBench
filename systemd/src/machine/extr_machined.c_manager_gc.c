#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int in_gc_queue; } ;
struct TYPE_12__ {TYPE_2__* machine_gc_queue; } ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_2__ Machine ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ MACHINE_CLOSING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  gc_queue ; 
 int /*<<< orphan*/  machine_finalize (TYPE_2__*) ; 
 int /*<<< orphan*/  machine_free (TYPE_2__*) ; 
 scalar_t__ machine_get_state (TYPE_2__*) ; 
 scalar_t__ machine_may_gc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  machine_stop (TYPE_2__*) ; 

__attribute__((used)) static void manager_gc(Manager *m, bool drop_not_started) {
        Machine *machine;

        assert(m);

        while ((machine = m->machine_gc_queue)) {
                LIST_REMOVE(gc_queue, m->machine_gc_queue, machine);
                machine->in_gc_queue = false;

                /* First, if we are not closing yet, initiate stopping */
                if (machine_may_gc(machine, drop_not_started) &&
                    machine_get_state(machine) != MACHINE_CLOSING)
                        machine_stop(machine);

                /* Now, the stop probably made this referenced
                 * again, but if it didn't, then it's time to let it
                 * go entirely. */
                if (machine_may_gc(machine, drop_not_started)) {
                        machine_finalize(machine);
                        machine_free(machine);
                }
        }
}