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
typedef  int Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
#define  DATEOID 130 
 int /*<<< orphan*/  DATEVAL_NOEND ; 
 int /*<<< orphan*/  DT_NOEND ; 
 int /*<<< orphan*/  DateADTGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_INT64_MAX ; 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 
 int /*<<< orphan*/  TimestampGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_internal_to_time_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Datum
time_range_internal_to_max_time_value(Oid type)
{
	switch (type)
	{
		case TIMESTAMPOID:
			return TimestampGetDatum(DT_NOEND);
		case TIMESTAMPTZOID:
			return TimestampTzGetDatum(DT_NOEND);
		case DATEOID:
			return DateADTGetDatum(DATEVAL_NOEND);
			break;
		default:
			return ts_internal_to_time_value(PG_INT64_MAX, type);
	}
}