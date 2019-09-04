#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {scalar_t__ lt_opr; scalar_t__ gt_opr; } ;
typedef  TYPE_6__ TypeCacheEntry ;
struct TYPE_30__ {int /*<<< orphan*/  expr; } ;
typedef  TYPE_7__ TargetEntry ;
struct TYPE_32__ {size_t relid; } ;
struct TYPE_31__ {scalar_t__ sortop; int /*<<< orphan*/  tleSortGroupRef; } ;
struct TYPE_28__ {int num_dimensions; scalar_t__ main_table_relid; TYPE_4__* dimensions; } ;
struct TYPE_26__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_27__ {TYPE_3__ fd; } ;
struct TYPE_25__ {int /*<<< orphan*/  colnames; } ;
struct TYPE_24__ {scalar_t__ sortClause; int /*<<< orphan*/  targetList; } ;
struct TYPE_23__ {size_t varno; int /*<<< orphan*/  vartype; int /*<<< orphan*/  varattno; } ;
struct TYPE_22__ {TYPE_5__* space; } ;
struct TYPE_21__ {size_t simple_rel_array_size; TYPE_10__** simple_rte_array; TYPE_1__* parse; } ;
struct TYPE_20__ {scalar_t__ relid; TYPE_2__* eref; } ;
typedef  TYPE_8__ SortGroupClause ;
typedef  TYPE_9__ RelOptInfo ;
typedef  TYPE_10__ RangeTblEntry ;
typedef  TYPE_11__ PlannerInfo ;
typedef  TYPE_12__ Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 int TYPECACHE_GT_OPR ; 
 int TYPECACHE_LT_OPR ; 
 int /*<<< orphan*/  Var ; 
 TYPE_19__* castNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* get_sortgroupref_tle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* linitial (scalar_t__) ; 
 int /*<<< orphan*/  list_nth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* lookup_type_cache (int /*<<< orphan*/ ,int) ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ *,char*) ; 
 char* strVal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_guc_disable_optimizations ; 
 scalar_t__ ts_guc_enable_ordered_append ; 

bool
ts_ordered_append_should_optimize(PlannerInfo *root, RelOptInfo *rel, Hypertable *ht, bool *reverse)
{
	SortGroupClause *sort = linitial(root->parse->sortClause);
	TargetEntry *tle = get_sortgroupref_tle(sort->tleSortGroupRef, root->parse->targetList);
	RangeTblEntry *rte = root->simple_rte_array[rel->relid];
	TypeCacheEntry *tce;
	char *column;

	/* these are checked in caller so we only Assert */
	Assert(!ts_guc_disable_optimizations && ts_guc_enable_ordered_append);

	/*
	 * only do this optimization for hypertables with 1 dimension and queries
	 * with an ORDER BY clause, caller checked this, so only asserting
	 */
	Assert(ht->space->num_dimensions == 1 || root->parse->sortClause != NIL);

	/*
	 * check that the first element of the ORDER BY clause actually matches
	 * the first dimension of the hypertable
	 */

	/* doublecheck rel actually refers to our hypertable */
	Assert(ht->space->main_table_relid == rte->relid);

	/*
	 * we only support direct column references for now
	 */
	if (!IsA(tle->expr, Var))
		return false;

	/*
	 * check Var points to a rel
	 */
	if (castNode(Var, tle->expr)->varno >= root->simple_rel_array_size)
		return false;

	/*
	 * check the ORDER BY column actually belongs to our hypertable
	 */
	if (root->simple_rte_array[castNode(Var, tle->expr)->varno] != rte)
		return false;

	/* check dimension column is our ORDER BY column */
	column = strVal(
		list_nth(rte->eref->colnames, AttrNumberGetAttrOffset(castNode(Var, tle->expr)->varattno)));
	if (namestrcmp(&ht->space->dimensions[0].fd.column_name, column) != 0)
		return false;

	/*
	 * check sort operation is either less than or greater than
	 */
	tce = lookup_type_cache(castNode(Var, tle->expr)->vartype, TYPECACHE_LT_OPR | TYPECACHE_GT_OPR);
	if (sort->sortop != tce->lt_opr && sort->sortop != tce->gt_opr)
		return false;

	if (reverse != NULL)
		*reverse = sort->sortop == tce->lt_opr ? false : true;

	return true;
}