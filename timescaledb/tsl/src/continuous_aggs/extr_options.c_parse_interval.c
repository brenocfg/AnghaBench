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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
#define  DATEOID 133 
 int /*<<< orphan*/  ERROR ; 
#define  INT2OID 132 
#define  INT4OID 131 
#define  INT8OID 130 
 int /*<<< orphan*/  INTERVALOID ; 
 int /*<<< orphan*/  OidInputFunctionCall (int,char*,int,int) ; 
 int /*<<< orphan*/  OidIsValid (int) ; 
 int /*<<< orphan*/  PG_INT16_MAX ; 
 int /*<<< orphan*/  PG_INT16_MIN ; 
 int /*<<< orphan*/  PG_INT32_MAX ; 
 int /*<<< orphan*/  PG_INT32_MIN ; 
 int /*<<< orphan*/  PG_INT64_MAX ; 
 int /*<<< orphan*/  PG_INT64_MIN ; 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  getTypeInputInfo (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  parse_int_interval (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pg_unreachable () ; 
 int /*<<< orphan*/  ts_interval_value_to_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64
parse_interval(char *value, Oid column_type, const char *option_name)
{
	Datum interval;
	Oid in_fn;
	Oid typIOParam;

	switch (column_type)
	{
		case INT2OID:
			return parse_int_interval(value, PG_INT16_MIN, PG_INT16_MAX, option_name);
		case INT4OID:
			return parse_int_interval(value, PG_INT32_MIN, PG_INT32_MAX, option_name);
		case INT8OID:
			return parse_int_interval(value, PG_INT64_MIN, PG_INT64_MAX, option_name);
		case TIMESTAMPTZOID:
		case TIMESTAMPOID:
		case DATEOID:
			getTypeInputInfo(INTERVALOID, &in_fn, &typIOParam);
			Assert(OidIsValid(in_fn));
			interval = OidInputFunctionCall(in_fn, value, typIOParam, -1);
			return ts_interval_value_to_internal(interval, INTERVALOID);
		default:
			elog(ERROR, "unknown time type when parsing timescaledb.%s", option_name);
			pg_unreachable();
	}
}