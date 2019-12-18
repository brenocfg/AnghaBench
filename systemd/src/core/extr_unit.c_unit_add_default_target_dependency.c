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
struct TYPE_8__ {scalar_t__ type; scalar_t__ load_state; int /*<<< orphan*/ * dependencies; int /*<<< orphan*/  default_dependencies; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_AFTER ; 
 size_t UNIT_BEFORE ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_DEFAULT ; 
 scalar_t__ UNIT_LOADED ; 
 scalar_t__ UNIT_TARGET ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ hashmap_get (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int unit_add_dependency (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int unit_add_default_target_dependency(Unit *u, Unit *target) {
        assert(u);
        assert(target);

        if (target->type != UNIT_TARGET)
                return 0;

        /* Only add the dependency if both units are loaded, so that
         * that loop check below is reliable */
        if (u->load_state != UNIT_LOADED ||
            target->load_state != UNIT_LOADED)
                return 0;

        /* If either side wants no automatic dependencies, then let's
         * skip this */
        if (!u->default_dependencies ||
            !target->default_dependencies)
                return 0;

        /* Don't create loops */
        if (hashmap_get(target->dependencies[UNIT_BEFORE], u))
                return 0;

        return unit_add_dependency(target, UNIT_AFTER, u, true, UNIT_DEPENDENCY_DEFAULT);
}