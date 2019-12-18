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
struct TYPE_5__ {size_t rqueue_size; size_t wqueue_size; scalar_t__ wqueue_allocated; int /*<<< orphan*/ * wqueue; scalar_t__ rqueue_allocated; int /*<<< orphan*/ * rqueue; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_message_unref_queued (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* mfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bus_reset_queues(sd_bus *b) {
        assert(b);

        while (b->rqueue_size > 0)
                bus_message_unref_queued(b->rqueue[--b->rqueue_size], b);

        b->rqueue = mfree(b->rqueue);
        b->rqueue_allocated = 0;

        while (b->wqueue_size > 0)
                bus_message_unref_queued(b->wqueue[--b->wqueue_size], b);

        b->wqueue = mfree(b->wqueue);
        b->wqueue_allocated = 0;
}