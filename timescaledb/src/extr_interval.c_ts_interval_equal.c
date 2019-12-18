#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ is_time_interval; scalar_t__ integer_interval; int /*<<< orphan*/  time_interval; } ;
typedef  TYPE_1__ FormData_ts_interval ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntervalPGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interval_eq ; 

bool
ts_interval_equal(FormData_ts_interval *invl1, FormData_ts_interval *invl2)
{
	AssertArg(invl1 != NULL);
	AssertArg(invl2 != NULL);

	if (invl1->is_time_interval != invl2->is_time_interval)
		return false;

	if (invl1->is_time_interval &&
		!DatumGetBool(DirectFunctionCall2(interval_eq,
										  IntervalPGetDatum(&invl1->time_interval),
										  IntervalPGetDatum(&invl2->time_interval))))
		return false;

	if (!invl1->is_time_interval && invl1->integer_interval != invl2->integer_interval)
	{
		return false;
	}

	return true;
}