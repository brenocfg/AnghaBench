#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  register_background_worker_callback_type ;
typedef  int /*<<< orphan*/  int32 ;
typedef  scalar_t__ TimestampTz ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  AcceptInvalidationMessages () ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ DT_NOEND ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  ProcDiePending ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 scalar_t__ TimestampTzPlusMilliseconds (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  check_for_stopped_and_timed_out_jobs () ; 
 int /*<<< orphan*/  earliest_job_timeout () ; 
 int /*<<< orphan*/  earliest_time_to_start_next_job () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int got_SIGHUP ; 
 int jobs_list_needs_update ; 
 scalar_t__ least_timestamp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scheduled_jobs ; 
 int /*<<< orphan*/  start_scheduled_jobs (int /*<<< orphan*/ ) ; 
 scalar_t__ ts_shutdown_bgw ; 
 scalar_t__ ts_timer_get_current_timestamp () ; 
 int /*<<< orphan*/  ts_timer_wait (scalar_t__) ; 
 int /*<<< orphan*/  ts_update_scheduled_jobs_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_all_jobs_to_shutdown () ; 

void
ts_bgw_scheduler_process(int32 run_for_interval_ms,
						 register_background_worker_callback_type bgw_register)
{
	TimestampTz start = ts_timer_get_current_timestamp();
	TimestampTz quit_time = DT_NOEND;
	MemoryContext scheduler_mctx = CurrentMemoryContext;

	/* txn to read the list of jobs from the DB */
	StartTransactionCommand();
	scheduled_jobs = ts_update_scheduled_jobs_list(scheduled_jobs, scheduler_mctx);
	CommitTransactionCommand();

	jobs_list_needs_update = false;

	if (run_for_interval_ms > 0)
		quit_time = TimestampTzPlusMilliseconds(start, run_for_interval_ms);

	ereport(DEBUG1, (errmsg("database scheduler starting for database %d", MyDatabaseId)));

	/*
	 * on SIGTERM the process will usually die from the CHECK_FOR_INTERRUPTS
	 * in the die() called from the sigterm handler. Child reaping is then
	 * handled in the before_shmem_exit,
	 * bgw_scheduler_before_shmem_exit_callback.
	 */
	while (quit_time > ts_timer_get_current_timestamp() && !ProcDiePending && !ts_shutdown_bgw)
	{
		TimestampTz next_wakeup = quit_time;

		/* start jobs, and then check when to next wake up */
		start_scheduled_jobs(bgw_register);
		next_wakeup = least_timestamp(next_wakeup, earliest_time_to_start_next_job());
		next_wakeup = least_timestamp(next_wakeup, earliest_job_timeout());

		ts_timer_wait(next_wakeup);

		CHECK_FOR_INTERRUPTS();

		if (got_SIGHUP)
		{
			got_SIGHUP = false;
			ProcessConfigFile(PGC_SIGHUP);
		}

		/*
		 * Process any cache invalidation message that indicates we need to
		 * update the jobs list
		 */
		AcceptInvalidationMessages();

		/* txn to read the list of jobs from the DB */
		if (jobs_list_needs_update)
		{
			StartTransactionCommand();
			scheduled_jobs = ts_update_scheduled_jobs_list(scheduled_jobs, scheduler_mctx);
			CommitTransactionCommand();
			jobs_list_needs_update = false;
		}

		check_for_stopped_and_timed_out_jobs();
	}

#ifdef TS_DEBUG
	if (ts_shutdown_bgw)
		elog(WARNING, "bgw scheduler stopped due to shutdown_bgw guc");
#endif

	CHECK_FOR_INTERRUPTS();

	wait_for_all_jobs_to_shutdown();
	check_for_stopped_and_timed_out_jobs();
}