#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int in_gc_queue; TYPE_1__* manager; scalar_t__ in_cleanup_queue; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_7__ {int /*<<< orphan*/  gc_unit_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  gc_queue ; 
 int /*<<< orphan*/  unit_may_gc (TYPE_2__*) ; 

void unit_add_to_gc_queue(Unit *u) {
        assert(u);

        if (u->in_gc_queue || u->in_cleanup_queue)
                return;

        if (!unit_may_gc(u))
                return;

        LIST_PREPEND(gc_queue, u->manager->gc_unit_queue, u);
        u->in_gc_queue = true;
}