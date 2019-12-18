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
typedef  int CGroupMask ;

/* Variables and functions */
 int CGROUP_MASK_CPU ; 
 int CGROUP_MASK_CPUACCT ; 

__attribute__((used)) static inline CGroupMask CGROUP_MASK_EXTEND_JOINED(CGroupMask mask) {
        /* We always mount "cpu" and "cpuacct" in the same hierarchy. Hence, when one bit is set also set the other */

        if (mask & (CGROUP_MASK_CPU|CGROUP_MASK_CPUACCT))
                mask |= (CGROUP_MASK_CPU|CGROUP_MASK_CPUACCT);

        return mask;
}