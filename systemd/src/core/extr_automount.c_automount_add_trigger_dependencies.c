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
typedef  int /*<<< orphan*/  Automount ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNIT_BEFORE ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_IMPLICIT ; 
 int /*<<< orphan*/  UNIT_TRIGGERS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int unit_add_two_dependencies (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int unit_load_related_unit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int automount_add_trigger_dependencies(Automount *a) {
        Unit *x;
        int r;

        assert(a);

        r = unit_load_related_unit(UNIT(a), ".mount", &x);
        if (r < 0)
                return r;

        return unit_add_two_dependencies(UNIT(a), UNIT_BEFORE, UNIT_TRIGGERS, x, true, UNIT_DEPENDENCY_IMPLICIT);
}