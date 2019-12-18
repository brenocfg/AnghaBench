#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  scanrel; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_3__ TupleInfo ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_12__ {int /*<<< orphan*/  retry_period; int /*<<< orphan*/  max_retries; int /*<<< orphan*/  max_runtime; int /*<<< orphan*/  schedule_interval; } ;
struct TYPE_16__ {TYPE_2__ fd; } ;
struct TYPE_11__ {int /*<<< orphan*/  last_finish; } ;
struct TYPE_15__ {TYPE_1__ fd; } ;
struct TYPE_14__ {int /*<<< orphan*/  retry_period; int /*<<< orphan*/  max_retries; int /*<<< orphan*/  max_runtime; int /*<<< orphan*/  schedule_interval; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_4__ FormData_bgw_job ;
typedef  TYPE_5__ BgwJobStat ;
typedef  TYPE_6__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntervalPGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interval_eq ; 
 int /*<<< orphan*/  timestamptz_pl_interval ; 
 int /*<<< orphan*/  ts_bgw_job_permission_check (TYPE_6__*) ; 
 TYPE_5__* ts_bgw_job_stat_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_job_stat_update_next_start (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_catalog_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
bgw_job_tuple_update_by_id(TupleInfo *ti, void *const data)
{
	BgwJob *updated_job = (BgwJob *) data;
	HeapTuple tuple = heap_copytuple(ti->tuple);
	FormData_bgw_job *fd = (FormData_bgw_job *) GETSTRUCT(tuple);
	TimestampTz next_start;

	ts_bgw_job_permission_check(updated_job);
	/* when we update the schedule interval, modify the next start time as well*/
	if (!DatumGetBool(DirectFunctionCall2(interval_eq,
										  IntervalPGetDatum(&fd->schedule_interval),
										  IntervalPGetDatum(&updated_job->fd.schedule_interval))))
	{
		BgwJobStat *stat = ts_bgw_job_stat_find(fd->id);

		if (stat != NULL)
		{
			next_start = DatumGetTimestampTz(
				DirectFunctionCall2(timestamptz_pl_interval,
									TimestampTzGetDatum(stat->fd.last_finish),
									IntervalPGetDatum(&updated_job->fd.schedule_interval)));
			/* allow DT_NOBEGIN for next_start here through allow_unset=true in the case that
			 * last_finish is DT_NOBEGIN,
			 * This means the value is counted as unset which is what we want */
			ts_bgw_job_stat_update_next_start(updated_job, next_start, true);
		}
		fd->schedule_interval = updated_job->fd.schedule_interval;
	}
	fd->max_runtime = updated_job->fd.max_runtime;
	fd->max_retries = updated_job->fd.max_retries;
	fd->retry_period = updated_job->fd.retry_period;

	ts_catalog_update(ti->scanrel, tuple);
	heap_freetuple(tuple);
	return SCAN_DONE;
}