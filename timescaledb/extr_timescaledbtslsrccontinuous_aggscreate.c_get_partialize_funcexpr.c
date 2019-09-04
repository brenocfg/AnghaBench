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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FuncExpr ;
typedef  int /*<<< orphan*/  Aggref ;

/* Variables and functions */
 int /*<<< orphan*/  ANYELEMENTOID ; 
 int /*<<< orphan*/  BYTEAOID ; 
 int /*<<< orphan*/  COERCE_EXPLICIT_CALL ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupFuncName (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PARTIALFN ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeFuncExpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FuncExpr *
get_partialize_funcexpr(Aggref *agg)
{
	FuncExpr *partialize_fnexpr;
	Oid partfnoid, partargtype;
	partargtype = ANYELEMENTOID;
	partfnoid = LookupFuncName(list_make2(makeString(INTERNAL_SCHEMA_NAME), makeString(PARTIALFN)),
							   1,
							   &partargtype,
							   false);
	partialize_fnexpr = makeFuncExpr(partfnoid,
									 BYTEAOID,
									 list_make1(agg), /*args*/
									 InvalidOid,
									 InvalidOid,
									 COERCE_EXPLICIT_CALL);
	return partialize_fnexpr;
}