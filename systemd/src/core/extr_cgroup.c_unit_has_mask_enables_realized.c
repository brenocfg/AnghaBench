#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cgroup_realized_mask; int cgroup_enabled_mask; scalar_t__ cgroup_realized; } ;
typedef  TYPE_1__ Unit ;
typedef  int CGroupMask ;

/* Variables and functions */
 int CGROUP_MASK_V1 ; 
 int CGROUP_MASK_V2 ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static bool unit_has_mask_enables_realized(
                Unit *u,
                CGroupMask target_mask,
                CGroupMask enable_mask) {

        assert(u);

        /* Returns true if all controllers which should be enabled are indeed enabled.
         *
         * Unlike unit_has_mask_realized, we don't care about the controllers that are not present, only that anything
         * we want to add is already added. */

        return u->cgroup_realized &&
                ((u->cgroup_realized_mask | target_mask) & CGROUP_MASK_V1) == (u->cgroup_realized_mask & CGROUP_MASK_V1) &&
                ((u->cgroup_enabled_mask | enable_mask) & CGROUP_MASK_V2) == (u->cgroup_enabled_mask & CGROUP_MASK_V2);
}