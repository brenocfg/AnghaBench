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
struct TYPE_7__ {int in_queue; TYPE_1__* bus; } ;
typedef  TYPE_2__ sd_bus_track ;
struct TYPE_6__ {int /*<<< orphan*/  track_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  queue ; 

__attribute__((used)) static void bus_track_remove_from_queue(sd_bus_track *track) {
        assert(track);

        if (!track->in_queue)
                return;

        LIST_REMOVE(queue, track->bus->track_queue, track);
        track->in_queue = false;
}