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
struct TYPE_4__ {int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_CANCELED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * hashmap_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_finish_and_invalidate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void manager_clear_jobs(Manager *m) {
        Job *j;

        assert(m);

        while ((j = hashmap_first(m->jobs)))
                /* No need to recurse. We're cancelling all jobs. */
                job_finish_and_invalidate(j, JOB_CANCELED, false, false);
}