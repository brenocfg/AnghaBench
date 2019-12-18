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
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  CGroupMask ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_MASK_BPF_FIREWALL ; 
 scalar_t__ unit_get_needs_bpf_firewall (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CGroupMask unit_get_bpf_mask(Unit *u) {
        CGroupMask mask = 0;

        /* Figure out which controllers we need, based on the cgroup context, possibly taking into account children
         * too. */

        if (unit_get_needs_bpf_firewall(u))
                mask |= CGROUP_MASK_BPF_FIREWALL;

        return mask;
}