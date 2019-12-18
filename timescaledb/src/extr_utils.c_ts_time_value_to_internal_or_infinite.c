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
typedef  int /*<<< orphan*/  TimevalInfinity ;
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  Timestamp ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  DateADT ;

/* Variables and functions */
#define  DATEOID 130 
 int /*<<< orphan*/  DATE_IS_NOBEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATE_NOT_FINITE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetDateADT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetTimestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_INT64_MAX ; 
 int /*<<< orphan*/  PG_INT64_MIN ; 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 
 int /*<<< orphan*/  TIMESTAMP_IS_NOBEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMESTAMP_NOT_FINITE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TimevalNegInfinity ; 
 int /*<<< orphan*/  TimevalPosInfinity ; 
 int /*<<< orphan*/  ts_time_value_to_internal (int /*<<< orphan*/ ,int) ; 

int64
ts_time_value_to_internal_or_infinite(Datum time_val, Oid type_oid,
									  TimevalInfinity *is_infinite_out)
{
	switch (type_oid)
	{
		case TIMESTAMPOID:
		{
			Timestamp ts = DatumGetTimestamp(time_val);
			if (TIMESTAMP_NOT_FINITE(ts))
			{
				if (TIMESTAMP_IS_NOBEGIN(ts))
				{
					if (is_infinite_out != NULL)
						*is_infinite_out = TimevalNegInfinity;
					return PG_INT64_MIN;
				}
				else
				{
					if (is_infinite_out != NULL)
						*is_infinite_out = TimevalPosInfinity;
					return PG_INT64_MAX;
				}
			}

			return ts_time_value_to_internal(time_val, type_oid);
		}
		case TIMESTAMPTZOID:
		{
			TimestampTz ts = DatumGetTimestampTz(time_val);
			if (TIMESTAMP_NOT_FINITE(ts))
			{
				if (TIMESTAMP_IS_NOBEGIN(ts))
				{
					if (is_infinite_out != NULL)
						*is_infinite_out = TimevalNegInfinity;
					return PG_INT64_MIN;
				}
				else
				{
					if (is_infinite_out != NULL)
						*is_infinite_out = TimevalPosInfinity;
					return PG_INT64_MAX;
				}
			}

			return ts_time_value_to_internal(time_val, type_oid);
		}
		case DATEOID:
		{
			DateADT d = DatumGetDateADT(time_val);
			if (DATE_NOT_FINITE(d))
			{
				if (DATE_IS_NOBEGIN(d))
				{
					if (is_infinite_out != NULL)
						*is_infinite_out = TimevalNegInfinity;
					return PG_INT64_MIN;
				}
				else
				{
					if (is_infinite_out != NULL)
						*is_infinite_out = TimevalPosInfinity;
					return PG_INT64_MAX;
				}
			}

			return ts_time_value_to_internal(time_val, type_oid);
		}
	}

	return ts_time_value_to_internal(time_val, type_oid);
}