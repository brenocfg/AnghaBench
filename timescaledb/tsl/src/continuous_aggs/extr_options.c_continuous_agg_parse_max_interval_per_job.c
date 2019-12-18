#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_3__ {int /*<<< orphan*/  parsed; int /*<<< orphan*/  is_default; } ;
typedef  TYPE_1__ WithClauseResult ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t ContinuousViewOptionMaxIntervalPerRun ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ parse_interval (char*,int /*<<< orphan*/ ,char*) ; 

int64
continuous_agg_parse_max_interval_per_job(Oid column_type, WithClauseResult *with_clause_options,
										  int64 bucket_width)
{
	char *value;
	int64 result;

	Assert(!with_clause_options[ContinuousViewOptionMaxIntervalPerRun].is_default);

	value = TextDatumGetCString(with_clause_options[ContinuousViewOptionMaxIntervalPerRun].parsed);

	result = parse_interval(value, column_type, "max_interval_per_job");

	if (result < bucket_width)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("parameter timescaledb.max_interval_per_job must be at least the size "
						"of the time_bucket width")));
	return result;
}