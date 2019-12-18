#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int ref_by_private_bus; int /*<<< orphan*/  bus_track; TYPE_2__* unit; } ;
typedef  TYPE_3__ sd_bus_message ;
struct TYPE_12__ {TYPE_1__* manager; } ;
struct TYPE_11__ {scalar_t__ api_bus; } ;
typedef  TYPE_3__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int bus_job_allocate_bus_track (TYPE_3__*) ; 
 scalar_t__ sd_bus_message_get_bus (TYPE_3__*) ; 
 int sd_bus_track_add_sender (int /*<<< orphan*/ ,TYPE_3__*) ; 

int bus_job_track_sender(Job *j, sd_bus_message *m) {
        int r;

        assert(j);
        assert(m);

        if (sd_bus_message_get_bus(m) != j->unit->manager->api_bus) {
                j->ref_by_private_bus = true;
                return 0;
        }

        r = bus_job_allocate_bus_track(j);
        if (r < 0)
                return r;

        return sd_bus_track_add_sender(j->bus_track, m);
}