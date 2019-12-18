#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int (* job_main_func ) () ;
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_1__ fd; } ;
struct TYPE_9__ {scalar_t__ total_runs; int /*<<< orphan*/  last_start; } ;
struct TYPE_10__ {TYPE_2__ fd; } ;
typedef  int /*<<< orphan*/  Interval ;
typedef  TYPE_3__ BgwJobStat ;
typedef  TYPE_4__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntervalPGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamptz_pl_interval ; 
 TYPE_3__* ts_bgw_job_stat_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_job_stat_set_next_start (TYPE_4__*,int /*<<< orphan*/ ) ; 

bool
ts_bgw_job_run_and_set_next_start(BgwJob *job, job_main_func func, int64 initial_runs,
								  Interval *next_interval)
{
	BgwJobStat *job_stat;
	bool ret = func();

	/* Now update next_start. */
	StartTransactionCommand();

	job_stat = ts_bgw_job_stat_find(job->fd.id);

	/*
	 * Note that setting next_start explicitly from this function will
	 * override any backoff calculation due to failure.
	 */
	if (job_stat->fd.total_runs < initial_runs)
	{
		TimestampTz next_start =
			DatumGetTimestampTz(DirectFunctionCall2(timestamptz_pl_interval,
													TimestampTzGetDatum(job_stat->fd.last_start),
													IntervalPGetDatum(next_interval)));

		ts_bgw_job_stat_set_next_start(job, next_start);
	}
	CommitTransactionCommand();

	return ret;
}