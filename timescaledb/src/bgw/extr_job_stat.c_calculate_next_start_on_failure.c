#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int float8 ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_4__ {int /*<<< orphan*/  schedule_interval; int /*<<< orphan*/  retry_period; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ BgwJob ;

/* Variables and functions */
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Float8GetDatum (int) ; 
 int /*<<< orphan*/  IntervalPGetDatum (int /*<<< orphan*/ *) ; 
 int MAX_INTERVALS_BACKOFF ; 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int calculate_jitter_percent () ; 
 int /*<<< orphan*/  interval_cmp ; 
 int /*<<< orphan*/  interval_mul ; 
 int /*<<< orphan*/  timestamptz_pl_interval ; 

__attribute__((used)) static TimestampTz
calculate_next_start_on_failure(TimestampTz last_finish, int consecutive_failures, BgwJob *job)
{
	float8 jitter = calculate_jitter_percent();
	/* consecutive failures includes this failure */
	float8 multiplier = 1 << (consecutive_failures - 1);

	/* ival = retry_period * 2^(consecutive_failures - 1)  */
	Datum ival = DirectFunctionCall2(interval_mul,
									 IntervalPGetDatum(&job->fd.retry_period),
									 Float8GetDatum(multiplier));

	/* ival_max is the ceiling = MAX_INTERVALS_BACKOFF * schedule_interval */
	Datum ival_max = DirectFunctionCall2(interval_mul,
										 IntervalPGetDatum(&job->fd.schedule_interval),
										 Float8GetDatum(MAX_INTERVALS_BACKOFF));

	if (DatumGetInt32(DirectFunctionCall2(interval_cmp, ival, ival_max)) > 0)
		ival = ival_max;

	/* Add some random jitter to prevent stampeding-herds, interval will be within about +-13% */
	ival = DirectFunctionCall2(interval_mul, ival, Float8GetDatum(1.0 + jitter));

	return DatumGetTimestampTz(
		DirectFunctionCall2(timestamptz_pl_interval, TimestampTzGetDatum(last_finish), ival));
}