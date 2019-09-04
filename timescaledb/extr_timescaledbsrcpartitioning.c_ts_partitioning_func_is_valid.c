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
typedef  int /*<<< orphan*/  regproc ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Form_pg_proc ;
typedef  int /*<<< orphan*/  DimensionType ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int IS_VALID_PARTITIONING_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

bool
ts_partitioning_func_is_valid(regproc funcoid, DimensionType dimtype, Oid argtype)
{
	HeapTuple tuple;
	bool isvalid;

	tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcoid));

	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for function %u", funcoid);

	isvalid = IS_VALID_PARTITIONING_FUNC((Form_pg_proc) GETSTRUCT(tuple), dimtype, argtype);

	ReleaseSysCache(tuple);

	return isvalid;
}