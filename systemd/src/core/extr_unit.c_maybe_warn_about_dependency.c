#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnitDependency ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_AFTER ; 
 int /*<<< orphan*/  UNIT_BEFORE ; 
 int /*<<< orphan*/  UNIT_CONFLICTED_BY ; 
 int /*<<< orphan*/  UNIT_CONFLICTS ; 
 int /*<<< orphan*/  UNIT_ON_FAILURE ; 
 int /*<<< orphan*/  UNIT_TRIGGERED_BY ; 
 int /*<<< orphan*/  UNIT_TRIGGERS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ streq_ptr (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strna (char const*) ; 
 int /*<<< orphan*/  unit_dependency_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void maybe_warn_about_dependency(Unit *u, const char *other, UnitDependency dependency) {
        assert(u);

        /* Only warn about some unit types */
        if (!IN_SET(dependency, UNIT_CONFLICTS, UNIT_CONFLICTED_BY, UNIT_BEFORE, UNIT_AFTER, UNIT_ON_FAILURE, UNIT_TRIGGERS, UNIT_TRIGGERED_BY))
                return;

        if (streq_ptr(u->id, other))
                log_unit_warning(u, "Dependency %s=%s dropped", unit_dependency_to_string(dependency), u->id);
        else
                log_unit_warning(u, "Dependency %s=%s dropped, merged into %s", unit_dependency_to_string(dependency), strna(other), u->id);
}