#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnitDependencyMask ;
struct TYPE_9__ {int /*<<< orphan*/  manager; } ;
struct TYPE_8__ {scalar_t__ from_fragment; } ;
typedef  int /*<<< orphan*/  MountParameters ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPECIAL_QUOTACHECK_SERVICE ; 
 int /*<<< orphan*/  SPECIAL_QUOTAON_SERVICE ; 
 TYPE_2__* UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  UNIT_BEFORE ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_FILE ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_MOUNTINFO_IMPLICIT ; 
 int /*<<< orphan*/  UNIT_WANTS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * get_mount_parameters_fragment (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_needs_quota (int /*<<< orphan*/ *) ; 
 int unit_add_two_dependencies_by_name (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_add_quota_dependencies(Mount *m) {
        UnitDependencyMask mask;
        MountParameters *p;
        int r;

        assert(m);

        if (!MANAGER_IS_SYSTEM(UNIT(m)->manager))
                return 0;

        p = get_mount_parameters_fragment(m);
        if (!p)
                return 0;

        if (!mount_needs_quota(p))
                return 0;

        mask = m->from_fragment ? UNIT_DEPENDENCY_FILE : UNIT_DEPENDENCY_MOUNTINFO_IMPLICIT;

        r = unit_add_two_dependencies_by_name(UNIT(m), UNIT_BEFORE, UNIT_WANTS, SPECIAL_QUOTACHECK_SERVICE, true, mask);
        if (r < 0)
                return r;

        r = unit_add_two_dependencies_by_name(UNIT(m), UNIT_BEFORE, UNIT_WANTS, SPECIAL_QUOTAON_SERVICE, true, mask);
        if (r < 0)
                return r;

        return 0;
}