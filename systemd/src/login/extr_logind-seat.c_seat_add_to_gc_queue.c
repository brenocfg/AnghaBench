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
struct TYPE_7__ {int in_gc_queue; TYPE_1__* manager; } ;
struct TYPE_6__ {int /*<<< orphan*/  seat_gc_queue; } ;
typedef  TYPE_2__ Seat ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  gc_queue ; 

void seat_add_to_gc_queue(Seat *s) {
        assert(s);

        if (s->in_gc_queue)
                return;

        LIST_PREPEND(gc_queue, s->manager->seat_gc_queue, s);
        s->in_gc_queue = true;
}