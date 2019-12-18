#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ provolatile; scalar_t__ pronargs; scalar_t__ prorettype; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_NO_DATA_FOUND ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_INTEGER_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  PROCOID ; 
 scalar_t__ PROVOLATILE_IMMUTABLE ; 
 scalar_t__ PROVOLATILE_STABLE ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 

void
ts_interval_now_func_validate(Oid now_func_oid, Oid open_dim_type)
{
	HeapTuple tuple;
	Form_pg_proc now_func;

	/* this function should only be called for hypertabes with integer open time dimension */
	Assert(IS_INTEGER_TYPE(open_dim_type));

	if (!OidIsValid(now_func_oid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION), (errmsg("invalid integer_now function"))));

	tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(now_func_oid));
	if (!HeapTupleIsValid(tuple))
	{
		ReleaseSysCache(tuple);
		ereport(ERROR,
				(errcode(ERRCODE_NO_DATA_FOUND),
				 errmsg("cache lookup failed for function %u", now_func_oid)));
	}

	now_func = (Form_pg_proc) GETSTRUCT(tuple);

	if ((now_func->provolatile != PROVOLATILE_IMMUTABLE &&
		 now_func->provolatile != PROVOLATILE_STABLE) ||
		now_func->pronargs != 0)
	{
		ReleaseSysCache(tuple);
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("integer_now_func must take no arguments and it must be STABLE")));
	}

	if (now_func->prorettype != open_dim_type)
	{
		ReleaseSysCache(tuple);
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("return type of integer_now_func must be the same as "
						"the type of the time partitioning column of the hypertable")));
	}
	ReleaseSysCache(tuple);
}