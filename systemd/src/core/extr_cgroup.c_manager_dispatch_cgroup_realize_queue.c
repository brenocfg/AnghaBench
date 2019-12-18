#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  id; TYPE_2__* in_cgroup_realize_queue; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_10__ {TYPE_1__* cgroup_realize_queue; } ;
typedef  int /*<<< orphan*/  ManagerState ;
typedef  TYPE_2__ Manager ;

/* Variables and functions */
 scalar_t__ UNIT_IS_INACTIVE_OR_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_state (TYPE_2__*) ; 
 int /*<<< orphan*/  unit_active_state (TYPE_1__*) ; 
 int unit_realize_cgroup_now (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_remove_from_cgroup_realize_queue (TYPE_1__*) ; 

unsigned manager_dispatch_cgroup_realize_queue(Manager *m) {
        ManagerState state;
        unsigned n = 0;
        Unit *i;
        int r;

        assert(m);

        state = manager_state(m);

        while ((i = m->cgroup_realize_queue)) {
                assert(i->in_cgroup_realize_queue);

                if (UNIT_IS_INACTIVE_OR_FAILED(unit_active_state(i))) {
                        /* Maybe things changed, and the unit is not actually active anymore? */
                        unit_remove_from_cgroup_realize_queue(i);
                        continue;
                }

                r = unit_realize_cgroup_now(i, state);
                if (r < 0)
                        log_warning_errno(r, "Failed to realize cgroups for queued unit %s, ignoring: %m", i->id);

                n++;
        }

        return n;
}