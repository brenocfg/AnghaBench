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
struct TYPE_3__ {int /*<<< orphan*/  integer_interval; int /*<<< orphan*/  time_interval; scalar_t__ is_time_interval; } ;
typedef  int Oid ;
typedef  TYPE_1__ FormData_ts_interval ;
typedef  int /*<<< orphan*/  Dimension ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
#define  DATEOID 130 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  IntervalPGetDatum (int /*<<< orphan*/ *) ; 
 int InvalidOid ; 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int get_integer_now_func (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_unreachable () ; 
 int /*<<< orphan*/  timestamp_date ; 
 int /*<<< orphan*/  timestamp_mi_interval ; 
 int /*<<< orphan*/  timestamptz_mi_interval ; 
 int /*<<< orphan*/  timestamptz_timestamp ; 
 int ts_dimension_get_partition_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_interval_from_now_func_get_datum (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ts_interval_now_func_validate (int,int) ; 

Datum
ts_interval_subtract_from_now(FormData_ts_interval *invl, Dimension *open_dim)
{
	Oid type_oid;
	AssertArg(invl != NULL);
	AssertArg(open_dim != NULL);

	type_oid = ts_dimension_get_partition_type(open_dim);

	if (invl->is_time_interval)
	{
		Datum res = TimestampTzGetDatum(GetCurrentTimestamp());

		switch (type_oid)
		{
			case TIMESTAMPOID:
				res = DirectFunctionCall1(timestamptz_timestamp, res);
				res = DirectFunctionCall2(timestamp_mi_interval,
										  res,
										  IntervalPGetDatum(&invl->time_interval));

				return res;
			case TIMESTAMPTZOID:
				res = DirectFunctionCall2(timestamptz_mi_interval,
										  res,
										  IntervalPGetDatum(&invl->time_interval));

				return res;
			case DATEOID:
				res = DirectFunctionCall1(timestamptz_timestamp, res);
				res = DirectFunctionCall2(timestamp_mi_interval,
										  res,
										  IntervalPGetDatum(&invl->time_interval));
				res = DirectFunctionCall1(timestamp_date, res);

				return res;
			default:
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("unknown time type OID %d", type_oid)));
		}
	}
	else
	{
		Oid now_func = get_integer_now_func(open_dim);
		ts_interval_now_func_validate(now_func, type_oid);

		if (InvalidOid == now_func)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("integer_now function must be set")));

		return ts_interval_from_now_func_get_datum(invl->integer_interval, type_oid, now_func);
	}
	/* suppress compiler warnings on MSVC */
	pg_unreachable();
	return 0;
}