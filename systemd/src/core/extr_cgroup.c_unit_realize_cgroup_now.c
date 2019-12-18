#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ cgroup_invalidated_mask; int /*<<< orphan*/  slice; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  ManagerState ;
typedef  int /*<<< orphan*/  CGroupMask ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_DEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int unit_create_cgroup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_get_enable_mask (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_get_target_mask (TYPE_1__*) ; 
 scalar_t__ unit_has_mask_realized (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int unit_realize_cgroup_now_disable (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int unit_realize_cgroup_now_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_remove_from_cgroup_realize_queue (TYPE_1__*) ; 

__attribute__((used)) static int unit_realize_cgroup_now(Unit *u, ManagerState state) {
        CGroupMask target_mask, enable_mask;
        int r;

        assert(u);

        unit_remove_from_cgroup_realize_queue(u);

        target_mask = unit_get_target_mask(u);
        enable_mask = unit_get_enable_mask(u);

        if (unit_has_mask_realized(u, target_mask, enable_mask))
                return 0;

        /* Disable controllers below us, if there are any */
        r = unit_realize_cgroup_now_disable(u, state);
        if (r < 0)
                return r;

        /* Enable controllers above us, if there are any */
        if (UNIT_ISSET(u->slice)) {
                r = unit_realize_cgroup_now_enable(UNIT_DEREF(u->slice), state);
                if (r < 0)
                        return r;
        }

        /* Now actually deal with the cgroup we were trying to realise and set attributes */
        r = unit_create_cgroup(u, target_mask, enable_mask, state);
        if (r < 0)
                return r;

        /* Now, reset the invalidation mask */
        u->cgroup_invalidated_mask = 0;
        return 0;
}