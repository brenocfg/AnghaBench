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
 int /*<<< orphan*/  DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
#define  INT2OID 130 
#define  INT4OID 129 
#define  INT8OID 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int64
ts_integer_to_internal(Datum time_val, Oid type_oid)
{
	switch (type_oid)
	{
		case INT8OID:
			return DatumGetInt64(time_val);
		case INT4OID:
			return (int64) DatumGetInt32(time_val);
		case INT2OID:
			return (int64) DatumGetInt16(time_val);
		default:
			elog(ERROR, "unknown interval type OID %d", type_oid);
			return -1;
	}
}