#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* bgw_policy_job_execute ) (TYPE_2__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  job_type; } ;
struct TYPE_9__ {int bgw_type; TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Interval ;
typedef  TYPE_2__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Float8GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
#define  JOB_TYPE_COMPRESS_CHUNKS 134 
#define  JOB_TYPE_CONTINUOUS_AGGREGATE 133 
#define  JOB_TYPE_DROP_CHUNKS 132 
#define  JOB_TYPE_REORDER 131 
#define  JOB_TYPE_UNKNOWN 130 
#define  JOB_TYPE_VERSION_CHECK 129 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TELEMETRY_INITIAL_NUM_RUNS ; 
#define  _MAX_JOB_TYPE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_interval ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*) ; 
 int ts_bgw_job_run_and_set_next_start (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* ts_cm_functions ; 
 int /*<<< orphan*/  ts_telemetry_main_wrapper ; 
 int unknown_job_type_hook (TYPE_2__*) ; 

bool
ts_bgw_job_execute(BgwJob *job)
{
	switch (job->bgw_type)
	{
		case JOB_TYPE_VERSION_CHECK:
		{
			bool next_start_set;
			/*
			 * In the first 12 hours, we want telemetry to ping every
			 * hour. After that initial period, we default to the
			 * schedule_interval listed in the job table.
			 */
			Interval *one_hour = DatumGetIntervalP(DirectFunctionCall7(make_interval,
																	   Int32GetDatum(0),
																	   Int32GetDatum(0),
																	   Int32GetDatum(0),
																	   Int32GetDatum(0),
																	   Int32GetDatum(1),
																	   Int32GetDatum(0),
																	   Float8GetDatum(0)));

			next_start_set = ts_bgw_job_run_and_set_next_start(job,
															   ts_telemetry_main_wrapper,
															   TELEMETRY_INITIAL_NUM_RUNS,
															   one_hour);
			pfree(one_hour);
			return next_start_set;
		}
		case JOB_TYPE_REORDER:
		case JOB_TYPE_DROP_CHUNKS:
		case JOB_TYPE_CONTINUOUS_AGGREGATE:
		case JOB_TYPE_COMPRESS_CHUNKS:
			return ts_cm_functions->bgw_policy_job_execute(job);
		case JOB_TYPE_UNKNOWN:
			if (unknown_job_type_hook != NULL)
				return unknown_job_type_hook(job);
			elog(ERROR, "unknown job type \"%s\"", NameStr(job->fd.job_type));
			break;
		case _MAX_JOB_TYPE:
			elog(ERROR, "unknown job type \"%s\"", NameStr(job->fd.job_type));
			break;
	}
	Assert(false);
	return false;
}