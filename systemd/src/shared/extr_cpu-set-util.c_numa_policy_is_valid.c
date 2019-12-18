#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ set; int /*<<< orphan*/  allocated; } ;
struct TYPE_7__ {TYPE_1__ nodes; } ;
typedef  TYPE_2__ NUMAPolicy ;

/* Variables and functions */
 int CPU_COUNT_S (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MPOL_DEFAULT ; 
 int /*<<< orphan*/  MPOL_LOCAL ; 
 scalar_t__ MPOL_PREFERRED ; 
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 
 int /*<<< orphan*/  mpol_is_valid (scalar_t__) ; 
 scalar_t__ numa_policy_get_type (TYPE_2__ const*) ; 

bool numa_policy_is_valid(const NUMAPolicy *policy) {
        assert(policy);

        if (!mpol_is_valid(numa_policy_get_type(policy)))
                return false;

        if (!policy->nodes.set &&
            !IN_SET(numa_policy_get_type(policy), MPOL_DEFAULT, MPOL_LOCAL, MPOL_PREFERRED))
                return false;

        if (policy->nodes.set &&
            numa_policy_get_type(policy) == MPOL_PREFERRED &&
            CPU_COUNT_S(policy->nodes.allocated, policy->nodes.set) != 1)
                return false;

        return true;
}