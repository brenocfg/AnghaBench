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
typedef  int UnitNotifyFlags ;
typedef  int /*<<< orphan*/  UnitActiveState ;
struct TYPE_6__ {scalar_t__ state; int type; } ;
typedef  int /*<<< orphan*/  JobResult ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB_DONE ; 
 int /*<<< orphan*/  JOB_FAILED ; 
#define  JOB_RELOAD 135 
#define  JOB_RELOAD_OR_START 134 
#define  JOB_RESTART 133 
 scalar_t__ JOB_RUNNING ; 
 int /*<<< orphan*/  JOB_SKIPPED ; 
#define  JOB_START 132 
#define  JOB_STOP 131 
#define  JOB_TRY_RELOAD 130 
#define  JOB_TRY_RESTART 129 
#define  JOB_VERIFY_ACTIVE 128 
 scalar_t__ JOB_WAITING ; 
 int /*<<< orphan*/  UNIT_ACTIVATING ; 
 int /*<<< orphan*/  UNIT_ACTIVE ; 
 int /*<<< orphan*/  UNIT_DEACTIVATING ; 
 int /*<<< orphan*/  UNIT_FAILED ; 
 int /*<<< orphan*/  UNIT_IS_ACTIVE_OR_RELOADING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_IS_INACTIVE_OR_FAILED (int /*<<< orphan*/ ) ; 
 int UNIT_NOTIFY_RELOAD_FAILURE ; 
 int /*<<< orphan*/  UNIT_NOTIFY_SKIP_CONDITION ; 
 int /*<<< orphan*/  UNIT_RELOADING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  job_add_to_run_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  job_finish_and_invalidate (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool unit_process_job(Job *j, UnitActiveState ns, UnitNotifyFlags flags) {
        bool unexpected = false;
        JobResult result;

        assert(j);

        if (j->state == JOB_WAITING)

                /* So we reached a different state for this job. Let's see if we can run it now if it failed previously
                 * due to EAGAIN. */
                job_add_to_run_queue(j);

        /* Let's check whether the unit's new state constitutes a finished job, or maybe contradicts a running job and
         * hence needs to invalidate jobs. */

        switch (j->type) {

        case JOB_START:
        case JOB_VERIFY_ACTIVE:

                if (UNIT_IS_ACTIVE_OR_RELOADING(ns))
                        job_finish_and_invalidate(j, JOB_DONE, true, false);
                else if (j->state == JOB_RUNNING && ns != UNIT_ACTIVATING) {
                        unexpected = true;

                        if (UNIT_IS_INACTIVE_OR_FAILED(ns)) {
                                if (ns == UNIT_FAILED)
                                        result = JOB_FAILED;
                                else if (FLAGS_SET(flags, UNIT_NOTIFY_SKIP_CONDITION))
                                        result = JOB_SKIPPED;
                                else
                                        result = JOB_DONE;

                                job_finish_and_invalidate(j, result, true, false);
                        }
                }

                break;

        case JOB_RELOAD:
        case JOB_RELOAD_OR_START:
        case JOB_TRY_RELOAD:

                if (j->state == JOB_RUNNING) {
                        if (ns == UNIT_ACTIVE)
                                job_finish_and_invalidate(j, (flags & UNIT_NOTIFY_RELOAD_FAILURE) ? JOB_FAILED : JOB_DONE, true, false);
                        else if (!IN_SET(ns, UNIT_ACTIVATING, UNIT_RELOADING)) {
                                unexpected = true;

                                if (UNIT_IS_INACTIVE_OR_FAILED(ns))
                                        job_finish_and_invalidate(j, ns == UNIT_FAILED ? JOB_FAILED : JOB_DONE, true, false);
                        }
                }

                break;

        case JOB_STOP:
        case JOB_RESTART:
        case JOB_TRY_RESTART:

                if (UNIT_IS_INACTIVE_OR_FAILED(ns))
                        job_finish_and_invalidate(j, JOB_DONE, true, false);
                else if (j->state == JOB_RUNNING && ns != UNIT_DEACTIVATING) {
                        unexpected = true;
                        job_finish_and_invalidate(j, JOB_FAILED, true, false);
                }

                break;

        default:
                assert_not_reached("Job type unknown");
        }

        return unexpected;
}