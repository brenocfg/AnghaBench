#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__* manager; scalar_t__ id; } ;
struct TYPE_5__ {int /*<<< orphan*/  current_job_id; } ;
typedef  scalar_t__ JobType ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 scalar_t__ _JOB_TYPE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* job_new_raw (int /*<<< orphan*/ *) ; 

Job* job_new(Unit *unit, JobType type) {
        Job *j;

        assert(type < _JOB_TYPE_MAX);

        j = job_new_raw(unit);
        if (!j)
                return NULL;

        j->id = j->manager->current_job_id++;
        j->type = type;

        /* We don't link it here, that's what job_dependency() is for */

        return j;
}