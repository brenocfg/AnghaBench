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
 int /*<<< orphan*/  Assert (int) ; 
#define  DATEOID 133 
 int DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
#define  INT2OID 132 
#define  INT4OID 131 
#define  INT8OID 130 
 int INTERVALOID ; 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 
 int USECS_PER_DAY ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int) ; 
 int interval_to_usec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_unreachable () ; 

__attribute__((used)) static inline int64
gapfill_period_get_internal(Oid timetype, Oid argtype, Datum arg)
{
	switch (timetype)
	{
		case DATEOID:
			Assert(INTERVALOID == argtype);
			return interval_to_usec(DatumGetIntervalP(arg)) / USECS_PER_DAY;
			break;
		case TIMESTAMPOID:
		case TIMESTAMPTZOID:
			Assert(INTERVALOID == argtype);
			return interval_to_usec(DatumGetIntervalP(arg));
			break;
		case INT2OID:
			Assert(INT2OID == argtype);
			return DatumGetInt16(arg);
		case INT4OID:
			Assert(INT4OID == argtype);
			return DatumGetInt32(arg);
		case INT8OID:
			Assert(INT8OID == argtype);
			return DatumGetInt64(arg);
		default:

			/*
			 * should never happen since time_bucket_gapfill is not defined
			 * for other datatypes
			 */
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("unsupported datatype for time_bucket_gapfill: %s",
							format_type_be(timetype))));
			pg_unreachable();
			break;
	}
}