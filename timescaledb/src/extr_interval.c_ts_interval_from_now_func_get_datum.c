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
typedef  scalar_t__ int64 ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt16 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INTERVAL_FIELD_OVERFLOW ; 
 int /*<<< orphan*/  ERROR ; 
#define  INT2OID 130 
#define  INT4OID 129 
#define  INT8OID 128 
 int /*<<< orphan*/  IS_INTEGER_TYPE (int) ; 
 int /*<<< orphan*/  Int16GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  Int32GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  Int64GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  OidFunctionCall0 (int) ; 
 scalar_t__ PG_INT16_MAX ; 
 scalar_t__ PG_INT16_MIN ; 
 scalar_t__ PG_INT32_MAX ; 
 scalar_t__ PG_INT32_MIN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pg_unreachable () ; 
 int /*<<< orphan*/  ts_interval_now_func_validate (int,int) ; 

__attribute__((used)) static Datum
ts_interval_from_now_func_get_datum(int64 interval, Oid time_dim_type, Oid now_func)
{
	Datum now;
	int64 res;

	AssertArg(IS_INTEGER_TYPE(time_dim_type));

	ts_interval_now_func_validate(now_func, time_dim_type);
	now = OidFunctionCall0(now_func);

	switch (time_dim_type)
	{
		case INT2OID:
			res = DatumGetInt16(now) - interval;
			if (res < PG_INT16_MIN || res > PG_INT16_MAX)
				ereport(ERROR,
						(errcode(ERRCODE_INTERVAL_FIELD_OVERFLOW), errmsg("ts_interval overflow")));
			return Int16GetDatum(res);
		case INT4OID:
			res = DatumGetInt32(now) - interval;
			if (res < PG_INT32_MIN || res > PG_INT32_MAX)
				ereport(ERROR,
						(errcode(ERRCODE_INTERVAL_FIELD_OVERFLOW), errmsg("ts_interval overflow")));
			return Int32GetDatum(res);
		case INT8OID:
			res = DatumGetInt64(now) - interval;
			if (res > DatumGetInt64(now))
				ereport(ERROR,
						(errcode(ERRCODE_INTERVAL_FIELD_OVERFLOW), errmsg("ts_interval overflow")));
			return Int64GetDatum(res);
		default:
			pg_unreachable();
	}
}