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
typedef  int uint64_t ;

/* Variables and functions */
 int CGROUP_CPU_SHARES_DEFAULT ; 
 int /*<<< orphan*/  CGROUP_CPU_SHARES_MAX ; 
 int /*<<< orphan*/  CGROUP_CPU_SHARES_MIN ; 
 int CGROUP_WEIGHT_DEFAULT ; 
 int CLAMP (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t cgroup_cpu_weight_to_shares(uint64_t weight) {
        return CLAMP(weight * CGROUP_CPU_SHARES_DEFAULT / CGROUP_WEIGHT_DEFAULT,
                     CGROUP_CPU_SHARES_MIN, CGROUP_CPU_SHARES_MAX);
}