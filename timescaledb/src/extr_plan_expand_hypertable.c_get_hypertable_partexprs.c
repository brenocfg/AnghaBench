#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* partitioning; int /*<<< orphan*/  column_attno; } ;
struct TYPE_14__ {int /*<<< orphan*/  attcollation; int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  atttypid; } ;
struct TYPE_13__ {int /*<<< orphan*/  main_table_relid; TYPE_1__* space; } ;
struct TYPE_10__ {int /*<<< orphan*/  fn_expr; } ;
struct TYPE_11__ {TYPE_2__ func_fmgr; } ;
struct TYPE_12__ {TYPE_3__ partfunc; } ;
struct TYPE_9__ {int num_dimensions; TYPE_7__* dimensions; } ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_5__ Hypertable ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_6__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_7__ Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheAttNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ makeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** palloc0 (int) ; 

__attribute__((used)) static List **
get_hypertable_partexprs(Hypertable *ht, Query *parse, Index varno)
{
	int i;
	List **partexprs;

	Assert(NULL != ht->space);

	partexprs = palloc0(sizeof(List *) * ht->space->num_dimensions);

	for (i = 0; i < ht->space->num_dimensions; i++)
	{
		Dimension *dim = &ht->space->dimensions[i];
		Expr *expr;
		HeapTuple tuple = SearchSysCacheAttNum(ht->main_table_relid, dim->column_attno);
		Form_pg_attribute att;

		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for attribute");

		att = (Form_pg_attribute) GETSTRUCT(tuple);

		expr = (Expr *)
			makeVar(varno, dim->column_attno, att->atttypid, att->atttypmod, att->attcollation, 0);

		ReleaseSysCache(tuple);

		/* The expression on the partitioning key can be the raw key or the
		 * partitioning function on the key */
		if (NULL != dim->partitioning)
			partexprs[i] = list_make2(expr, dim->partitioning->partfunc.func_fmgr.fn_expr);
		else
			partexprs[i] = list_make1(expr);
	}

	return partexprs;
}