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
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ fd; } ;
struct TYPE_9__ {int reserved_worker; int may_need_mark_end; TYPE_2__ job; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_3__ ScheduledBgwJob ;
typedef  int /*<<< orphan*/  BgwJobStat ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  JOB_FAILURE ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  assert_that_worker_has_stopped (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_job_as_ended (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_bgw_job_get_share_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_job_stat_end_was_marked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_bgw_job_stat_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_worker_release () ; 

__attribute__((used)) static void
worker_state_cleanup(ScheduledBgwJob *sjob)
{
	/*
	 * This function needs to be safe wrt failures occurring at any point in
	 * the job starting process.
	 */
	if (sjob->handle != NULL)
	{
#if USE_ASSERT_CHECKING
		/* Sanity check: worker has stopped (if it was started) */
		assert_that_worker_has_stopped(sjob);
#endif
		pfree(sjob->handle);
		sjob->handle = NULL;
	}

	/*
	 * first cleanup reserved workers before accessing db. Want to minimize
	 * the possibility of errors before worker is released
	 */
	if (sjob->reserved_worker)
	{
		ts_bgw_worker_release();
		sjob->reserved_worker = false;
	}

	if (sjob->may_need_mark_end)
	{
		BgwJobStat *job_stat;

		if (!ts_bgw_job_get_share_lock(sjob->job.fd.id, CurrentMemoryContext))
		{
			elog(WARNING,
				 "scheduler detected that job %d was deleted after job quit",
				 sjob->job.fd.id);
			sjob->may_need_mark_end = false;
			return;
		}

		job_stat = ts_bgw_job_stat_find(sjob->job.fd.id);

		Assert(job_stat != NULL);

		if (!ts_bgw_job_stat_end_was_marked(job_stat))
		{
			/*
			 * Usually the job process will mark the end, but if the job gets
			 * a signal (cancel or terminate), it won't be able to so we
			 * should.
			 */
			mark_job_as_ended(sjob, JOB_FAILURE);
			/* reload updated value */
			job_stat = ts_bgw_job_stat_find(sjob->job.fd.id);
		}
		else
		{
			sjob->may_need_mark_end = false;
		}
	}
}