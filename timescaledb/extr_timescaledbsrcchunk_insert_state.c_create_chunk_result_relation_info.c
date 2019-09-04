#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  oc_ProjTupdesc; int /*<<< orphan*/  oc_WhereClause; int /*<<< orphan*/  oc_ProjInfo; } ;
struct TYPE_13__ {TYPE_2__* hypertable_result_rel_info; TYPE_1__* estate; } ;
struct TYPE_12__ {TYPE_5__* ri_onConflict; int /*<<< orphan*/  ri_projectReturning; int /*<<< orphan*/  ri_junkFilter; int /*<<< orphan*/  ri_WithCheckOptionExprs; int /*<<< orphan*/  ri_WithCheckOptions; } ;
struct TYPE_11__ {int /*<<< orphan*/  es_instrument; } ;
typedef  TYPE_2__ ResultRelInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_3__ ChunkDispatch ;

/* Variables and functions */
 int /*<<< orphan*/  InitResultRelInfoCompat (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NodeSetTag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OnConflictSetState ; 
 int /*<<< orphan*/  T_ResultRelInfo ; 
 int /*<<< orphan*/  create_chunk_rri_constraint_expr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* makeNode (int /*<<< orphan*/ ) ; 
 TYPE_2__* palloc0 (int) ; 

__attribute__((used)) static inline ResultRelInfo *
create_chunk_result_relation_info(ChunkDispatch *dispatch, Relation rel, Index rti)
{
	ResultRelInfo *rri, *rri_orig;

	rri = palloc0(sizeof(ResultRelInfo));
	NodeSetTag(rri, T_ResultRelInfo);

	InitResultRelInfoCompat(rri, rel, rti, dispatch->estate->es_instrument);

	/* Copy options from the main table's (hypertable's) result relation info */
	rri_orig = dispatch->hypertable_result_rel_info;
	rri->ri_WithCheckOptions = rri_orig->ri_WithCheckOptions;
	rri->ri_WithCheckOptionExprs = rri_orig->ri_WithCheckOptionExprs;
	rri->ri_junkFilter = rri_orig->ri_junkFilter;
	rri->ri_projectReturning = rri_orig->ri_projectReturning;
#if PG96 || PG10
	ResultRelInfo_OnConflictProjInfoCompat(rri) = ResultRelInfo_OnConflictProjInfoCompat(rri_orig);
	ResultRelInfo_OnConflictWhereCompat(rri) = ResultRelInfo_OnConflictWhereCompat(rri_orig);
#else
	if (rri_orig->ri_onConflict != NULL)
	{
		rri->ri_onConflict = makeNode(OnConflictSetState);
		rri->ri_onConflict->oc_ProjInfo = rri_orig->ri_onConflict->oc_ProjInfo;
		rri->ri_onConflict->oc_WhereClause = rri_orig->ri_onConflict->oc_WhereClause;
		rri->ri_onConflict->oc_ProjTupdesc = rri_orig->ri_onConflict->oc_ProjTupdesc;
	}
	else
		rri->ri_onConflict = NULL;
#endif

	create_chunk_rri_constraint_expr(rri, rel);

	return rri;
}