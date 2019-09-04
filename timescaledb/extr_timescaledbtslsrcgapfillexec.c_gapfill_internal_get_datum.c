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
#define  INT2OID 132 
#define  INT4OID 131 
#define  INT8OID 130 
 int /*<<< orphan*/  Int16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 

__attribute__((used)) static inline Datum
gapfill_internal_get_datum(int64 value, Oid type)
{
	switch (type)
	{
		case INT2OID:
			return Int16GetDatum(value);
		case DATEOID:
		case INT4OID:
			return Int32GetDatum(value);
		case TIMESTAMPOID:
		case TIMESTAMPTZOID:
		case INT8OID:
			return Int64GetDatum(value);
		default:

			/*
			 * should never happen since time_bucket_gapfill is not defined
			 * for other datatypes
			 */
			Assert(false);
			return Int64GetDatum(0);
	}
}