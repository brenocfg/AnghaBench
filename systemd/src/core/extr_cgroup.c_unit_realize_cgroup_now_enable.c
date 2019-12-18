#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int cgroup_realized_mask; int cgroup_enabled_mask; int /*<<< orphan*/  slice; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  ManagerState ;
typedef  int CGroupMask ;

/* Variables and functions */
 TYPE_1__* UNIT_DEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int unit_create_cgroup (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int unit_get_enable_mask (TYPE_1__*) ; 
 int unit_get_target_mask (TYPE_1__*) ; 
 scalar_t__ unit_has_mask_enables_realized (TYPE_1__*,int,int) ; 

__attribute__((used)) static int unit_realize_cgroup_now_enable(Unit *u, ManagerState state) {
        CGroupMask target_mask, enable_mask, new_target_mask, new_enable_mask;
        int r;

        assert(u);

        /* First go deal with this unit's parent, or we won't be able to enable
         * any new controllers at this layer. */
        if (UNIT_ISSET(u->slice)) {
                r = unit_realize_cgroup_now_enable(UNIT_DEREF(u->slice), state);
                if (r < 0)
                        return r;
        }

        target_mask = unit_get_target_mask(u);
        enable_mask = unit_get_enable_mask(u);

        /* We can only enable in this direction, don't try to disable anything.
         */
        if (unit_has_mask_enables_realized(u, target_mask, enable_mask))
                return 0;

        new_target_mask = u->cgroup_realized_mask | target_mask;
        new_enable_mask = u->cgroup_enabled_mask | enable_mask;

        return unit_create_cgroup(u, new_target_mask, new_enable_mask, state);
}