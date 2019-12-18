#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ numOrderedAggs; scalar_t__ hasNonSerial; scalar_t__ hasNonPartial; } ;
struct TYPE_27__ {int /*<<< orphan*/  rows; } ;
struct TYPE_26__ {scalar_t__ processed_tlist; int /*<<< orphan*/ ** upper_targets; TYPE_2__* parse; } ;
struct TYPE_25__ {scalar_t__ groupClause; int /*<<< orphan*/ * havingQual; int /*<<< orphan*/  hasAggs; scalar_t__ groupingSets; } ;
struct TYPE_24__ {scalar_t__ partial_pathlist; int /*<<< orphan*/  consider_parallel; TYPE_4__* cheapest_total_path; } ;
typedef  int Size ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ Query ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  PathTarget ;
typedef  TYPE_4__ Path ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_5__ AggClauseCosts ;

/* Variables and functions */
 int /*<<< orphan*/  AGGSPLIT_SIMPLE ; 
 int /*<<< orphan*/  AGG_HASHED ; 
 int /*<<< orphan*/  IS_VALID_ESTIMATE (double) ; 
 int /*<<< orphan*/  MemSet (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NIL ; 
 int UINT64CONST (int) ; 
 size_t UPPERREL_GROUP_AGG ; 
 int /*<<< orphan*/  add_path (TYPE_1__*,TYPE_4__*) ; 
 scalar_t__ create_agg_path (TYPE_3__*,TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_5__*,double) ; 
 int /*<<< orphan*/  get_agg_clause_costs (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ grouping_is_hashable (scalar_t__) ; 
 int /*<<< orphan*/  plan_add_parallel_hashagg (TYPE_3__*,TYPE_1__*,TYPE_1__*,double) ; 
 double ts_estimate_group (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ts_estimate_hashagg_tablesize (TYPE_4__*,TYPE_5__*,double) ; 
 int work_mem ; 

void
ts_plan_add_hashagg(PlannerInfo *root, RelOptInfo *input_rel, RelOptInfo *output_rel)
{
	Query *parse = root->parse;
	Path *cheapest_path = input_rel->cheapest_total_path;
	AggClauseCosts agg_costs;
	bool can_hash;
	double d_num_groups;
	Size hashaggtablesize;
	PathTarget *target = root->upper_targets[UPPERREL_GROUP_AGG];
	bool try_parallel_aggregation;

	if (parse->groupingSets || !parse->hasAggs || parse->groupClause == NIL)
		return;

	MemSet(&agg_costs, 0, sizeof(AggClauseCosts));
	get_agg_clause_costs(root, (Node *) root->processed_tlist, AGGSPLIT_SIMPLE, &agg_costs);
	get_agg_clause_costs(root, parse->havingQual, AGGSPLIT_SIMPLE, &agg_costs);

	can_hash = (parse->groupClause != NIL && agg_costs.numOrderedAggs == 0 &&
				grouping_is_hashable(parse->groupClause));

	if (!can_hash)
		return;

	d_num_groups = ts_estimate_group(root, cheapest_path->rows);

	/* don't have any special estimate */
	if (!IS_VALID_ESTIMATE(d_num_groups))
		return;

	hashaggtablesize = ts_estimate_hashagg_tablesize(cheapest_path, &agg_costs, d_num_groups);

	if (hashaggtablesize >= work_mem * UINT64CONST(1024))
		return;

	if (!output_rel->consider_parallel)
	{
		/* Not even parallel-safe. */
		try_parallel_aggregation = false;
	}
	else if (output_rel->partial_pathlist == NIL)
	{
		/* Nothing to use as input for partial aggregate. */
		try_parallel_aggregation = false;
	}
	else if (agg_costs.hasNonPartial || agg_costs.hasNonSerial)
	{
		/* Insufficient support for partial mode. */
		try_parallel_aggregation = false;
	}
	else
	{
		/* Everything looks good. */
		try_parallel_aggregation = true;
	}

	if (try_parallel_aggregation)
		plan_add_parallel_hashagg(root, input_rel, output_rel, d_num_groups);

	/*
	 * We just need an Agg over the cheapest-total input path, since input
	 * order won't matter.
	 */
	add_path(output_rel,
			 (Path *) create_agg_path(root,
									  output_rel,
									  cheapest_path,
									  target,
									  AGG_HASHED,
									  AGGSPLIT_SIMPLE,
									  parse->groupClause,
									  (List *) parse->havingQual,
									  &agg_costs,
									  d_num_groups));
}