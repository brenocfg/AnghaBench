#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ bus_track; TYPE_2__* unit; } ;
struct TYPE_8__ {TYPE_1__* manager; } ;
struct TYPE_7__ {int /*<<< orphan*/  api_bus; } ;
typedef  TYPE_3__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  bus_job_track_handler ; 
 int sd_bus_track_new (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int bus_job_allocate_bus_track(Job *j) {

        assert(j);

        if (j->bus_track)
                return 0;

        return sd_bus_track_new(j->unit->manager->api_bus, &j->bus_track, bus_job_track_handler, j);
}