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
typedef  int /*<<< orphan*/  int64 ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  DATEOID 133 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
#define  INT2OID 132 
#define  INT4OID 131 
#define  INT8OID 130 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  timestamp_date ; 
 int /*<<< orphan*/  timestamp_mi_interval ; 
 int /*<<< orphan*/  timestamptz_mi_interval ; 
 int /*<<< orphan*/  timestamptz_timestamp ; 
 int /*<<< orphan*/  ts_time_value_to_internal (int /*<<< orphan*/ ,int) ; 

int64
ts_interval_from_now_to_internal(Datum interval, Oid type_oid)
{
	Datum res = TimestampTzGetDatum(GetCurrentTimestamp());

	switch (type_oid)
	{
		case TIMESTAMPOID:
			res = DirectFunctionCall1(timestamptz_timestamp, res);
			res = DirectFunctionCall2(timestamp_mi_interval, res, interval);

			return ts_time_value_to_internal(res, type_oid);
		case TIMESTAMPTZOID:
			res = DirectFunctionCall2(timestamptz_mi_interval, res, interval);

			return ts_time_value_to_internal(res, type_oid);
		case DATEOID:
			res = DirectFunctionCall1(timestamptz_timestamp, res);
			res = DirectFunctionCall2(timestamp_mi_interval, res, interval);
			res = DirectFunctionCall1(timestamp_date, res);

			return ts_time_value_to_internal(res, type_oid);
		case INT8OID:
		case INT4OID:
		case INT2OID:

			/*
			 * should never get here as the case is handled by
			 * time_dim_typecheck
			 */
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("can only use this with an INTERVAL for "
							"TIMESTAMP, TIMESTAMPTZ, and DATE types")));
		default:
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("unknown time type OID %d", type_oid)));
	}
	/* suppress compiler warnings on MSVC */
	Assert(false);
	return 0;
}