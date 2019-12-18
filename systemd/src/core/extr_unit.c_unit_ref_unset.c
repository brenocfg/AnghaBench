#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* target; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ UnitRef ;
struct TYPE_7__ {int /*<<< orphan*/  refs_by_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  refs_by_target ; 
 int /*<<< orphan*/  unit_add_to_gc_queue (TYPE_3__*) ; 

void unit_ref_unset(UnitRef *ref) {
        assert(ref);

        if (!ref->target)
                return;

        /* We are about to drop a reference to the unit, make sure the garbage collection has a look at it as it might
         * be unreferenced now. */
        unit_add_to_gc_queue(ref->target);

        LIST_REMOVE(refs_by_target, ref->target->refs_by_target, ref);
        ref->source = ref->target = NULL;
}