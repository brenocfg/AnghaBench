#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  application_name; int /*<<< orphan*/  id; } ;
struct TYPE_14__ {TYPE_1__ fd; } ;
struct TYPE_13__ {int reserved_worker; int state; int /*<<< orphan*/ * handle; TYPE_4__ job; int /*<<< orphan*/  timeout_at; int /*<<< orphan*/  next_start; } ;
typedef  TYPE_2__ ScheduledBgwJob ;
typedef  int JobState ;
typedef  int /*<<< orphan*/  BgwJobStat ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DT_NOEND ; 
#define  JOB_STATE_DISABLED 131 
#define  JOB_STATE_SCHEDULED 130 
#define  JOB_STATE_STARTED 129 
#define  JOB_STATE_TERMINATING 128 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  TerminateBackgroundWorker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_job_as_started (TYPE_2__*) ; 
 int /*<<< orphan*/  on_failure_to_start_job (TYPE_2__*) ; 
 int prev_state ; 
 int /*<<< orphan*/  ts_bgw_job_has_timeout (TYPE_4__*) ; 
 int /*<<< orphan*/ * ts_bgw_job_start (TYPE_4__*) ; 
 int /*<<< orphan*/ * ts_bgw_job_stat_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_job_stat_next_start (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ts_bgw_job_stat_should_execute (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ts_bgw_job_timeout_at (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ts_bgw_worker_reserve () ; 
 int /*<<< orphan*/  ts_timer_get_current_timestamp () ; 
 int /*<<< orphan*/  worker_state_cleanup (TYPE_2__*) ; 

__attribute__((used)) static void
scheduled_bgw_job_transition_state_to(ScheduledBgwJob *sjob, JobState new_state)
{
#if USE_ASSERT_CHECKING
	JobState prev_state = sjob->state;
#endif

	BgwJobStat *job_stat;

	switch (new_state)
	{
		case JOB_STATE_DISABLED:
			Assert(prev_state == JOB_STATE_STARTED || prev_state == JOB_STATE_TERMINATING);
			sjob->handle = NULL;
			break;
		case JOB_STATE_SCHEDULED:
			/* prev_state can be any value, including itself */

			worker_state_cleanup(sjob);

			job_stat = ts_bgw_job_stat_find(sjob->job.fd.id);

			if (!ts_bgw_job_stat_should_execute(job_stat, &sjob->job))
			{
				scheduled_bgw_job_transition_state_to(sjob, JOB_STATE_DISABLED);
				return;
			}

			Assert(!sjob->reserved_worker);
			sjob->next_start = ts_bgw_job_stat_next_start(job_stat, &sjob->job);
			break;
		case JOB_STATE_STARTED:
			Assert(prev_state == JOB_STATE_SCHEDULED);
			Assert(sjob->handle == NULL);
			Assert(!sjob->reserved_worker);

			StartTransactionCommand();

			/*
			 * start the job before you can encounter any errors so that they
			 * are always registered
			 */
			mark_job_as_started(sjob);
			if (ts_bgw_job_has_timeout(&sjob->job))
				sjob->timeout_at =
					ts_bgw_job_timeout_at(&sjob->job, ts_timer_get_current_timestamp());
			else
				sjob->timeout_at = DT_NOEND;
			CommitTransactionCommand();

			sjob->reserved_worker = ts_bgw_worker_reserve();
			if (!sjob->reserved_worker)
			{
				elog(WARNING,
					 "failed to launch job %d \"%s\": out of background workers",
					 sjob->job.fd.id,
					 NameStr(sjob->job.fd.application_name));
				on_failure_to_start_job(sjob);
				return;
			}

			elog(DEBUG1,
				 "launching job %d \"%s\"",
				 sjob->job.fd.id,
				 NameStr(sjob->job.fd.application_name));

			sjob->handle = ts_bgw_job_start(&sjob->job);
			if (sjob->handle == NULL)
			{
				elog(WARNING,
					 "failed to launch job %d \"%s\": failed to start a background worker",
					 sjob->job.fd.id,
					 NameStr(sjob->job.fd.application_name));
				on_failure_to_start_job(sjob);
				return;
			}
			Assert(sjob->reserved_worker);
			break;
		case JOB_STATE_TERMINATING:
			Assert(prev_state == JOB_STATE_STARTED);
			Assert(sjob->handle != NULL);
			Assert(sjob->reserved_worker);
			TerminateBackgroundWorker(sjob->handle);
			break;
	}
	sjob->state = new_state;
}