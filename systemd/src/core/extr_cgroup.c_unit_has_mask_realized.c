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
struct TYPE_4__ {int cgroup_realized_mask; int cgroup_enabled_mask; scalar_t__ cgroup_invalidated_mask; scalar_t__ cgroup_realized; } ;
typedef  TYPE_1__ Unit ;
typedef  int CGroupMask ;

/* Variables and functions */
 int CGROUP_MASK_V1 ; 
 int CGROUP_MASK_V2 ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static bool unit_has_mask_realized(
                Unit *u,
                CGroupMask target_mask,
                CGroupMask enable_mask) {

        assert(u);

        /* Returns true if this unit is fully realized. We check four things:
         *
         * 1. Whether the cgroup was created at all
         * 2. Whether the cgroup was created in all the hierarchies we need it to be created in (in case of cgroup v1)
         * 3. Whether the cgroup has all the right controllers enabled (in case of cgroup v2)
         * 4. Whether the invalidation mask is currently zero
         *
         * If you wonder why we mask the target realization and enable mask with CGROUP_MASK_V1/CGROUP_MASK_V2: note
         * that there are three sets of bitmasks: CGROUP_MASK_V1 (for real cgroup v1 controllers), CGROUP_MASK_V2 (for
         * real cgroup v2 controllers) and CGROUP_MASK_BPF (for BPF-based pseudo-controllers). Now, cgroup_realized_mask
         * is only matters for cgroup v1 controllers, and cgroup_enabled_mask only used for cgroup v2, and if they
         * differ in the others, we don't really care. (After all, the cgroup_enabled_mask tracks with controllers are
         * enabled through cgroup.subtree_control, and since the BPF pseudo-controllers don't show up there, they
         * simply don't matter. */

        return u->cgroup_realized &&
                ((u->cgroup_realized_mask ^ target_mask) & CGROUP_MASK_V1) == 0 &&
                ((u->cgroup_enabled_mask ^ enable_mask) & CGROUP_MASK_V2) == 0 &&
                u->cgroup_invalidated_mask == 0;
}