#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  refs_by_target; struct TYPE_10__* target; struct TYPE_10__* source; } ;
typedef  TYPE_1__ UnitRef ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  refs_by_target ; 
 int /*<<< orphan*/  unit_ref_unset (TYPE_1__*) ; 

Unit* unit_ref_set(UnitRef *ref, Unit *source, Unit *target) {
        assert(ref);
        assert(source);
        assert(target);

        if (ref->target)
                unit_ref_unset(ref);

        ref->source = source;
        ref->target = target;
        LIST_PREPEND(refs_by_target, target->refs_by_target, ref);
        return target;
}