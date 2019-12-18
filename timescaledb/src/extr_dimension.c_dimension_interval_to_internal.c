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
typedef  int int64 ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DATEOID ; 
 int /*<<< orphan*/  DEFAULT_CHUNK_TIME_INTERVAL ; 
 int /*<<< orphan*/  DEFAULT_CHUNK_TIME_INTERVAL_ADAPTIVE ; 
 int /*<<< orphan*/  DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
#define  INT2OID 131 
#define  INT4OID 130 
#define  INT8OID 129 
#define  INTERVALOID 128 
 scalar_t__ IS_INTEGER_TYPE (int) ; 
 int /*<<< orphan*/  IS_VALID_OPEN_DIM_TYPE (int) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int) ; 
 int USECS_PER_DAY ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int get_validated_integer_interval (int,int /*<<< orphan*/ ) ; 
 int interval_to_usec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64
dimension_interval_to_internal(const char *colname, Oid dimtype, Oid valuetype, Datum value,
							   bool adaptive_chunking)
{
	int64 interval;

	if (!IS_VALID_OPEN_DIM_TYPE(dimtype))
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("invalid dimension type: \"%s\" must be an integer, date or timestamp",
						colname)));

	if (!OidIsValid(valuetype))
	{
		if (IS_INTEGER_TYPE(dimtype))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("integer dimensions require an explicit interval")));

		value = Int64GetDatum(adaptive_chunking ? DEFAULT_CHUNK_TIME_INTERVAL_ADAPTIVE :
												  DEFAULT_CHUNK_TIME_INTERVAL);
		valuetype = INT8OID;
	}

	switch (valuetype)
	{
		case INT2OID:
			interval = get_validated_integer_interval(dimtype, DatumGetInt16(value));
			break;
		case INT4OID:
			interval = get_validated_integer_interval(dimtype, DatumGetInt32(value));
			break;
		case INT8OID:
			interval = get_validated_integer_interval(dimtype, DatumGetInt64(value));
			break;
		case INTERVALOID:
			if (IS_INTEGER_TYPE(dimtype))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg(
							 "invalid interval: must be an integer type for integer dimensions")));

			interval = interval_to_usec(DatumGetIntervalP(value));
			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("invalid interval: must be an interval or integer type")));
	}

	if (dimtype == DATEOID && (interval <= 0 || interval % USECS_PER_DAY != 0))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid interval: must be multiples of one day")));

	return interval;
}