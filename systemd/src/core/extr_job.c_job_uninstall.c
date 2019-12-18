#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  jobs; } ;
struct TYPE_10__ {TYPE_1__* job; TYPE_1__* nop_job; } ;
struct TYPE_9__ {int installed; scalar_t__ type; int /*<<< orphan*/  id; TYPE_8__* manager; TYPE_2__* unit; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 scalar_t__ JOB_NOP ; 
 int /*<<< orphan*/  JOB_WAITING ; 
 int /*<<< orphan*/  MANAGER_IS_RELOADING (TYPE_8__*) ; 
 int /*<<< orphan*/  UINT32_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bus_job_send_removed_signal (TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_remove_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  job_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_add_to_dbus_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  unit_add_to_gc_queue (TYPE_2__*) ; 

void job_uninstall(Job *j) {
        Job **pj;

        assert(j->installed);

        job_set_state(j, JOB_WAITING);

        pj = (j->type == JOB_NOP) ? &j->unit->nop_job : &j->unit->job;
        assert(*pj == j);

        /* Detach from next 'bigger' objects */

        /* daemon-reload should be transparent to job observers */
        if (!MANAGER_IS_RELOADING(j->manager))
                bus_job_send_removed_signal(j);

        *pj = NULL;

        unit_add_to_gc_queue(j->unit);

        unit_add_to_dbus_queue(j->unit); /* The Job property of the unit has changed now */

        hashmap_remove_value(j->manager->jobs, UINT32_TO_PTR(j->id), j);
        j->installed = false;
}