#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  Timer ;
struct TYPE_4__ {int /*<<< orphan*/ * dependencies; } ;

/* Variables and functions */
 TYPE_1__* UNIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNIT_BEFORE ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_IMPLICIT ; 
 size_t UNIT_TRIGGERS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_isempty (int /*<<< orphan*/ ) ; 
 int unit_add_two_dependencies (TYPE_1__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int unit_load_related_unit (TYPE_1__*,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int timer_add_trigger_dependencies(Timer *t) {
        Unit *x;
        int r;

        assert(t);

        if (!hashmap_isempty(UNIT(t)->dependencies[UNIT_TRIGGERS]))
                return 0;

        r = unit_load_related_unit(UNIT(t), ".service", &x);
        if (r < 0)
                return r;

        return unit_add_two_dependencies(UNIT(t), UNIT_BEFORE, UNIT_TRIGGERS, x, true, UNIT_DEPENDENCY_IMPLICIT);
}