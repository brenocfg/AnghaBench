#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnitDependencyMask ;
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  slice; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  SPECIAL_ROOT_SLICE ; 
 int /*<<< orphan*/  UNIT_AFTER ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_FILE ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_IMPLICIT ; 
 int /*<<< orphan*/  UNIT_DEREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_HAS_CGROUP_CONTEXT (TYPE_1__*) ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_REQUIRES ; 
 scalar_t__ UNIT_SLICE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int unit_add_two_dependencies (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int unit_add_two_dependencies_by_name (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unit_has_name (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unit_add_slice_dependencies(Unit *u) {
        UnitDependencyMask mask;
        assert(u);

        if (!UNIT_HAS_CGROUP_CONTEXT(u))
                return 0;

        /* Slice units are implicitly ordered against their parent slices (as this relationship is encoded in the
           name), while all other units are ordered based on configuration (as in their case Slice= configures the
           relationship). */
        mask = u->type == UNIT_SLICE ? UNIT_DEPENDENCY_IMPLICIT : UNIT_DEPENDENCY_FILE;

        if (UNIT_ISSET(u->slice))
                return unit_add_two_dependencies(u, UNIT_AFTER, UNIT_REQUIRES, UNIT_DEREF(u->slice), true, mask);

        if (unit_has_name(u, SPECIAL_ROOT_SLICE))
                return 0;

        return unit_add_two_dependencies_by_name(u, UNIT_AFTER, UNIT_REQUIRES, SPECIAL_ROOT_SLICE, true, mask);
}