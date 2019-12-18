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
struct TYPE_4__ {struct TYPE_4__* result; struct TYPE_4__* name; int /*<<< orphan*/  bus; int /*<<< orphan*/  slot_job_removed; int /*<<< orphan*/  slot_disconnected; int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ BusWaitForJobs ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 

void bus_wait_for_jobs_free(BusWaitForJobs *d) {
        if (!d)
                return;

        set_free_free(d->jobs);

        sd_bus_slot_unref(d->slot_disconnected);
        sd_bus_slot_unref(d->slot_job_removed);

        sd_bus_unref(d->bus);

        free(d->name);
        free(d->result);

        free(d);
}