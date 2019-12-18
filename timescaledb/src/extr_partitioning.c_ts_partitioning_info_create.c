#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Var ;
struct TYPE_8__ {scalar_t__ hash_proc; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_11__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_10__ {TYPE_7__ func_fmgr; int /*<<< orphan*/  rettype; int /*<<< orphan*/  schema; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {scalar_t__ column_attnum; TYPE_4__ partfunc; int /*<<< orphan*/  dimtype; int /*<<< orphan*/  column; } ;
typedef  TYPE_2__ PartitioningInfo ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  FuncExpr ;
typedef  int /*<<< orphan*/  DimensionType ;

/* Variables and functions */
 int /*<<< orphan*/  COERCE_EXPLICIT_CALL ; 
 int /*<<< orphan*/  DIMENSION_TYPE_CLOSED ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidAttrNumber ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  StrNCpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPECACHE_HASH_FLAGS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  fmgr_info_set_expr (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ get_attnum (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ get_atttype (scalar_t__,scalar_t__) ; 
 scalar_t__ get_typcollation (scalar_t__) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* lookup_type_cache (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeFuncExpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeVar (int,scalar_t__,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* palloc0 (int) ; 
 int /*<<< orphan*/  partitioning_func_set_func_fmgr (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_partitioning_func_is_closed_default (char const*,char const*) ; 

PartitioningInfo *
ts_partitioning_info_create(const char *schema, const char *partfunc, const char *partcol,
							DimensionType dimtype, Oid relid)
{
	PartitioningInfo *pinfo;
	Oid columntype, varcollid, funccollid = InvalidOid;
	Var *var;
	FuncExpr *expr;

	if (schema == NULL || partfunc == NULL || partcol == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
				 errmsg("partitioning function information cannot be null")));

	pinfo = palloc0(sizeof(PartitioningInfo));
	StrNCpy(pinfo->partfunc.name, partfunc, NAMEDATALEN);
	StrNCpy(pinfo->column, partcol, NAMEDATALEN);
	pinfo->column_attnum = get_attnum(relid, pinfo->column);
	pinfo->dimtype = dimtype;

	/* handle the case that the attribute has been dropped */
	if (pinfo->column_attnum == InvalidAttrNumber)
		return NULL;

	StrNCpy(pinfo->partfunc.schema, schema, NAMEDATALEN);

	/* Lookup the type cache entry to access the hash function for the type */
	columntype = get_atttype(relid, pinfo->column_attnum);

	if (dimtype == DIMENSION_TYPE_CLOSED)
	{
		TypeCacheEntry *tce = lookup_type_cache(columntype, TYPECACHE_HASH_FLAGS);

		if (tce->hash_proc == InvalidOid &&
			ts_partitioning_func_is_closed_default(schema, partfunc))
			elog(ERROR, "could not find hash function for type %s", format_type_be(columntype));
	}

	partitioning_func_set_func_fmgr(&pinfo->partfunc, columntype, dimtype);

	/*
	 * Prepare a function expression for this function. The partition hash
	 * function needs this to be able to resolve the type of the value to be
	 * hashed.
	 */
	varcollid = get_typcollation(columntype);

	var = makeVar(1, pinfo->column_attnum, columntype, -1, varcollid, 0);

	expr = makeFuncExpr(pinfo->partfunc.func_fmgr.fn_oid,
						pinfo->partfunc.rettype,
						list_make1(var),
						funccollid,
						varcollid,
						COERCE_EXPLICIT_CALL);

	fmgr_info_set_expr((Node *) expr, &pinfo->partfunc.func_fmgr);

	return pinfo;
}