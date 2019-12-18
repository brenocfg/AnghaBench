#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  scanrel; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_8__ {int last_run_success; scalar_t__ consecutive_failures; int /*<<< orphan*/  last_finish; int /*<<< orphan*/  next_start; int /*<<< orphan*/  total_failures; int /*<<< orphan*/  last_successful_finish; int /*<<< orphan*/  total_success; scalar_t__ consecutive_crashes; int /*<<< orphan*/  total_crashes; int /*<<< orphan*/  total_duration; int /*<<< orphan*/  last_start; } ;
struct TYPE_7__ {scalar_t__ result; int /*<<< orphan*/  job; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  TYPE_2__ JobResultCtx ;
typedef  int /*<<< orphan*/  Interval ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ FormData_bgw_job_stat ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntervalPGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ JOB_SUCCESS ; 
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgw_job_stat_next_start_was_set (TYPE_3__*) ; 
 int /*<<< orphan*/  calculate_next_start_on_failure (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_next_start_on_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interval_pl ; 
 int /*<<< orphan*/  timestamp_mi ; 
 int /*<<< orphan*/  ts_catalog_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_timer_get_current_timestamp () ; 

__attribute__((used)) static ScanTupleResult
bgw_job_stat_tuple_mark_end(TupleInfo *ti, void *const data)
{
	JobResultCtx *result_ctx = data;
	HeapTuple tuple = heap_copytuple(ti->tuple);
	FormData_bgw_job_stat *fd = (FormData_bgw_job_stat *) GETSTRUCT(tuple);
	Interval *duration;

	fd->last_finish = ts_timer_get_current_timestamp();

	duration = DatumGetIntervalP(DirectFunctionCall2(timestamp_mi,
													 TimestampTzGetDatum(fd->last_finish),
													 TimestampTzGetDatum(fd->last_start)));
	fd->total_duration =
		*DatumGetIntervalP(DirectFunctionCall2(interval_pl,
											   IntervalPGetDatum(&fd->total_duration),
											   IntervalPGetDatum(duration)));

	/* undo marking created by start marks */
	fd->last_run_success = result_ctx->result == JOB_SUCCESS ? true : false;
	fd->total_crashes--;
	fd->consecutive_crashes = 0;

	if (result_ctx->result == JOB_SUCCESS)
	{
		fd->total_success++;
		fd->consecutive_failures = 0;
		fd->last_successful_finish = fd->last_finish;
		/* Mark the next start at the end if the job itself hasn't */
		if (!bgw_job_stat_next_start_was_set(fd))
			fd->next_start = calculate_next_start_on_success(fd->last_finish, result_ctx->job);
	}
	else
	{
		fd->total_failures++;
		fd->consecutive_failures++;

		/*
		 * Mark the next start at the end if the job itself hasn't (this may
		 * have happened before failure)
		 */
		if (!bgw_job_stat_next_start_was_set(fd))
			fd->next_start = calculate_next_start_on_failure(fd->last_finish,
															 fd->consecutive_failures,
															 result_ctx->job);
	}

	ts_catalog_update(ti->scanrel, tuple);
	heap_freetuple(tuple);

	return SCAN_DONE;
}