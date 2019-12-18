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
typedef  int /*<<< orphan*/  sd_bus_message ;
struct TYPE_4__ {int /*<<< orphan*/  bus_track; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int EUNATCH ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_track_remove_sender (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bus_unit_track_remove_sender(Unit *u, sd_bus_message *m) {
        assert(u);

        /* If we haven't allocated the bus track object yet, then there's definitely no reference taken yet, return an
         * error */
        if (!u->bus_track)
                return -EUNATCH;

        return sd_bus_track_remove_sender(u->bus_track, m);
}