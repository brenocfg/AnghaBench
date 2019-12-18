#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_3__ {int consttype; int /*<<< orphan*/  constvalue; int /*<<< orphan*/  constisnull; } ;
typedef  TYPE_1__ Const ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
#define  INT2OID 130 
#define  INT4OID 129 
#define  INT8OID 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pg_unreachable () ; 

__attribute__((used)) static int64
const_datum_get_int(Const *cnst)
{
	Assert(!cnst->constisnull);

	switch (cnst->consttype)
	{
		case INT2OID:
			return (int64)(DatumGetInt16(cnst->constvalue));
		case INT4OID:
			return (int64)(DatumGetInt32(cnst->constvalue));
		case INT8OID:
			return DatumGetInt64(cnst->constvalue);
	}

	ereport(ERROR,
			(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
			 errmsg("can only use const_datum_get_int with integer types")));

	pg_unreachable();
}