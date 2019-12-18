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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ CGROUP_CPU_SHARES_INVALID ; 
 scalar_t__ CGROUP_CPU_SHARES_MAX ; 
 scalar_t__ CGROUP_CPU_SHARES_MIN ; 

__attribute__((used)) static inline bool CGROUP_CPU_SHARES_IS_OK(uint64_t x) {
        return
            x == CGROUP_CPU_SHARES_INVALID ||
            (x >= CGROUP_CPU_SHARES_MIN && x <= CGROUP_CPU_SHARES_MAX);
}