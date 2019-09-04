#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UpperRelationKind ;
struct TYPE_28__ {int /*<<< orphan*/  (* create_upper_paths_hook ) (TYPE_3__*,scalar_t__,TYPE_1__*,TYPE_1__*) ;} ;
struct TYPE_27__ {int /*<<< orphan*/  processed_tlist; TYPE_2__* parse; } ;
struct TYPE_26__ {scalar_t__ hasAggs; } ;
struct TYPE_25__ {scalar_t__ pathlist; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ Query ;
typedef  TYPE_3__ PlannerInfo ;

/* Variables and functions */
 scalar_t__ IS_DUMMY_REL (TYPE_1__*) ; 
 scalar_t__ NIL ; 
 scalar_t__ UPPERREL_GROUP_AGG ; 
 int /*<<< orphan*/  involves_hypertable (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  plan_process_partialize_agg (TYPE_3__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  prev_create_upper_paths_hook (TYPE_3__*,scalar_t__,TYPE_1__*,TYPE_1__*,void*) ; 
 scalar_t__ replace_hypertable_insert_paths (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,scalar_t__,TYPE_1__*,TYPE_1__*) ; 
 TYPE_8__* ts_cm_functions ; 
 int /*<<< orphan*/  ts_extension_is_loaded () ; 
 scalar_t__ ts_guc_disable_optimizations ; 
 int /*<<< orphan*/  ts_guc_optimize_non_hypertables ; 
 int /*<<< orphan*/  ts_plan_add_hashagg (TYPE_3__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ts_preprocess_first_last_aggregates (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
#if PG96 || PG10
timescale_create_upper_paths_hook(PlannerInfo *root, UpperRelationKind stage, RelOptInfo *input_rel,
								  RelOptInfo *output_rel)
{
	Query *parse = root->parse;

	if (prev_create_upper_paths_hook != NULL)
		prev_create_upper_paths_hook(root, stage, input_rel, output_rel);
#else
timescale_create_upper_paths_hook(PlannerInfo *root, UpperRelationKind stage, RelOptInfo *input_rel,
								  RelOptInfo *output_rel, void *extra)
{
	Query *parse = root->parse;

	if (prev_create_upper_paths_hook != NULL)
		prev_create_upper_paths_hook(root, stage, input_rel, output_rel, extra);
#endif

	if (!ts_extension_is_loaded())
		return;

	if (ts_cm_functions->create_upper_paths_hook != NULL)
		ts_cm_functions->create_upper_paths_hook(root, stage, input_rel, output_rel);

	if (output_rel != NULL)
	{
		/* Modify for INSERTs on a hypertable */
		if (output_rel->pathlist != NIL)
			output_rel->pathlist = replace_hypertable_insert_paths(root, output_rel->pathlist);

		/* modify aggregates that need to be partialized */
		plan_process_partialize_agg(root, input_rel, output_rel);
	}

	if (ts_guc_disable_optimizations || input_rel == NULL || IS_DUMMY_REL(input_rel))
		return;

	if (!ts_guc_optimize_non_hypertables && !involves_hypertable(root, input_rel))
		return;

	if (UPPERREL_GROUP_AGG == stage && output_rel != NULL)
	{
		ts_plan_add_hashagg(root, input_rel, output_rel);
		if (parse->hasAggs)
			ts_preprocess_first_last_aggregates(root, root->processed_tlist);
	}
}