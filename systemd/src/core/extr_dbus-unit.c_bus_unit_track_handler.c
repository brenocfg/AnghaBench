#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bus_track; } ;
typedef  TYPE_1__ sd_bus_track ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_bus_track_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_add_to_cgroup_empty_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_add_to_gc_queue (TYPE_1__*) ; 

__attribute__((used)) static int bus_unit_track_handler(sd_bus_track *t, void *userdata) {
        Unit *u = userdata;

        assert(t);
        assert(u);

        u->bus_track = sd_bus_track_unref(u->bus_track); /* make sure we aren't called again */

        /* If the client that tracks us disappeared, then there's reason to believe that the cgroup is empty now too,
         * let's see */
        unit_add_to_cgroup_empty_queue(u);

        /* Also add the unit to the GC queue, after all if the client left it might be time to GC this unit */
        unit_add_to_gc_queue(u);

        return 0;
}