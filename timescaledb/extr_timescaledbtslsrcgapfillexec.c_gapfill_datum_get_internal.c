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
#define  DATEOID 133 
 int /*<<< orphan*/  DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
#define  INT2OID 132 
#define  INT4OID 131 
#define  INT8OID 130 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int) ; 
 int /*<<< orphan*/  pg_unreachable () ; 

int64
gapfill_datum_get_internal(Datum value, Oid type)
{
	switch (type)
	{
		case INT2OID:
			return DatumGetInt16(value);
		case DATEOID:
		case INT4OID:
			return DatumGetInt32(value);
		case TIMESTAMPOID:
		case TIMESTAMPTZOID:
		case INT8OID:
			return DatumGetInt64(value);
		default:

			/*
			 * should never happen since time_bucket_gapfill is not defined
			 * for other datatypes
			 */
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("unsupported datatype for time_bucket_gapfill: %s",
							format_type_be(type))));
			pg_unreachable();
			break;
	}
}