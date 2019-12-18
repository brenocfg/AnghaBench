#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cgroup_invalidated_mask; } ;
typedef  TYPE_1__ Unit ;
typedef  int CGroupMask ;

/* Variables and functions */
 int CGROUP_MASK_BLKIO ; 
 int CGROUP_MASK_CPU ; 
 int CGROUP_MASK_CPUACCT ; 
 int CGROUP_MASK_IO ; 
 scalar_t__ FLAGS_SET (int,int) ; 
 int /*<<< orphan*/  UNIT_HAS_CGROUP_CONTEXT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_add_to_cgroup_realize_queue (TYPE_1__*) ; 

void unit_invalidate_cgroup(Unit *u, CGroupMask m) {
        assert(u);

        if (!UNIT_HAS_CGROUP_CONTEXT(u))
                return;

        if (m == 0)
                return;

        /* always invalidate compat pairs together */
        if (m & (CGROUP_MASK_IO | CGROUP_MASK_BLKIO))
                m |= CGROUP_MASK_IO | CGROUP_MASK_BLKIO;

        if (m & (CGROUP_MASK_CPU | CGROUP_MASK_CPUACCT))
                m |= CGROUP_MASK_CPU | CGROUP_MASK_CPUACCT;

        if (FLAGS_SET(u->cgroup_invalidated_mask, m)) /* NOP? */
                return;

        u->cgroup_invalidated_mask |= m;
        unit_add_to_cgroup_realize_queue(u);
}