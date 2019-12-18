#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bus_track; } ;
typedef  TYPE_1__ sd_bus_track ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  job_add_to_gc_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_bus_track_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bus_job_track_handler(sd_bus_track *t, void *userdata) {
        Job *j = userdata;

        assert(t);
        assert(j);

        j->bus_track = sd_bus_track_unref(j->bus_track); /* make sure we aren't called again */

        /* Last client dropped off the bus, maybe we should GC this now? */
        job_add_to_gc_queue(j);
        return 0;
}