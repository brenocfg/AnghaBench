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
struct TYPE_5__ {int /*<<< orphan*/  job_type; int /*<<< orphan*/  application_name; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Interval ;
typedef  TYPE_2__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/ * DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Float8GetDatum (double) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
#define  TEST_JOB_TYPE_JOB_1 134 
#define  TEST_JOB_TYPE_JOB_2_ERROR 133 
#define  TEST_JOB_TYPE_JOB_3_LONG 132 
#define  TEST_JOB_TYPE_JOB_4 131 
#define  TEST_JOB_TYPE_JOB_5_LOCK 130 
#define  TEST_JOB_TYPE_JOB_6_LOCK_NOTXN 129 
#define  _MAX_TEST_JOB_TYPE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int get_test_job_type_from_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_interval ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int test_job_1 () ; 
 int test_job_2_error () ; 
 int test_job_3_long () ; 
 int /*<<< orphan*/  test_job_4 ; 
 int test_job_5_lock () ; 
 int test_job_6_lock_notxn () ; 
 int ts_bgw_job_run_and_set_next_start (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_bgw_log_set_application_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_params_get () ; 
 int /*<<< orphan*/  ts_register_emit_log_hook () ; 

__attribute__((used)) static bool
test_job_dispatcher(BgwJob *job)
{
	ts_register_emit_log_hook();
	ts_bgw_log_set_application_name(strdup(NameStr(job->fd.application_name)));

	StartTransactionCommand();
	ts_params_get();
	CommitTransactionCommand();

	switch (get_test_job_type_from_name(&job->fd.job_type))
	{
		case TEST_JOB_TYPE_JOB_1:
			return test_job_1();
		case TEST_JOB_TYPE_JOB_2_ERROR:
			return test_job_2_error();
		case TEST_JOB_TYPE_JOB_3_LONG:
			return test_job_3_long();
		case TEST_JOB_TYPE_JOB_4:
		{
			/* Set next_start to 200ms */
			Interval *new_interval = DatumGetIntervalP(DirectFunctionCall7(make_interval,
																		   Int32GetDatum(0),
																		   Int32GetDatum(0),
																		   Int32GetDatum(0),
																		   Int32GetDatum(0),
																		   Int32GetDatum(0),
																		   Int32GetDatum(0),
																		   Float8GetDatum(0.2)));

			return ts_bgw_job_run_and_set_next_start(job, test_job_4, 3, new_interval);
		}
		case TEST_JOB_TYPE_JOB_5_LOCK:
			return test_job_5_lock();
		case TEST_JOB_TYPE_JOB_6_LOCK_NOTXN:
			return test_job_6_lock_notxn();
		case _MAX_TEST_JOB_TYPE:
			elog(ERROR,
				 "unrecognized test job type: %s %d",
				 NameStr(job->fd.job_type),
				 get_test_job_type_from_name(&job->fd.job_type));
	}
	return false;
}