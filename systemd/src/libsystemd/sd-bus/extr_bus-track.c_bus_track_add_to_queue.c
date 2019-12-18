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
struct TYPE_7__ {int in_queue; scalar_t__ n_adding; TYPE_1__* bus; int /*<<< orphan*/  in_list; int /*<<< orphan*/  handler; int /*<<< orphan*/  names; } ;
typedef  TYPE_2__ sd_bus_track ;
struct TYPE_6__ {int /*<<< orphan*/  track_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ hashmap_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue ; 

__attribute__((used)) static void bus_track_add_to_queue(sd_bus_track *track) {
        assert(track);

        /* Adds the bus track object to the queue of objects we should dispatch next, subject to a number of
         * conditions. */

        /* Already in the queue? */
        if (track->in_queue)
                return;

        /* if we are currently in the process of adding a new name, then let's not enqueue this just yet, let's wait
         * until the addition is complete. */
        if (track->n_adding > 0)
                return;

        /* still referenced? */
        if (hashmap_size(track->names) > 0)
                return;

        /* Nothing to call? */
        if (!track->handler)
                return;

        /* Already closed? */
        if (!track->in_list)
                return;

        LIST_PREPEND(queue, track->bus->track_queue, track);
        track->in_queue = true;
}