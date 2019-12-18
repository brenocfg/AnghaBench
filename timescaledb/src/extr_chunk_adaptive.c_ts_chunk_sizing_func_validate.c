#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regproc ;
struct TYPE_7__ {int /*<<< orphan*/  func_name; int /*<<< orphan*/  func_schema; int /*<<< orphan*/  func; } ;
struct TYPE_5__ {scalar_t__* values; } ;
struct TYPE_6__ {scalar_t__ pronargs; scalar_t__ prorettype; int /*<<< orphan*/  proname; int /*<<< orphan*/  pronamespace; TYPE_1__ proargtypes; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;
typedef  TYPE_3__ ChunkSizingInfo ;

/* Variables and functions */
 scalar_t__ CHUNK_SIZING_FUNC_NARGS ; 
 int /*<<< orphan*/  ERRCODE_INVALID_FUNCTION_DEFINITION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ INT4OID ; 
 scalar_t__ INT8OID ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ts_chunk_sizing_func_validate(regproc func, ChunkSizingInfo *info)
{
	HeapTuple tuple;
	Form_pg_proc form;
	Oid *typearr;

	if (!OidIsValid(func))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION), (errmsg("invalid chunk sizing function"))));

	tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(func));

	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for function %u", func);

	form = (Form_pg_proc) GETSTRUCT(tuple);
	typearr = form->proargtypes.values;

	if (form->pronargs != CHUNK_SIZING_FUNC_NARGS || typearr[0] != INT4OID ||
		typearr[1] != INT8OID || typearr[2] != INT8OID || form->prorettype != INT8OID)
	{
		ReleaseSysCache(tuple);
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
				 errmsg("invalid function signature"),
				 errhint("A chunk sizing function's signature should be (int, bigint, bigint) -> "
						 "bigint")));
	}

	if (NULL != info)
	{
		info->func = func;
		namestrcpy(&info->func_schema, get_namespace_name(form->pronamespace));
		namestrcpy(&info->func_name, NameStr(form->proname));
	}

	ReleaseSysCache(tuple);
}