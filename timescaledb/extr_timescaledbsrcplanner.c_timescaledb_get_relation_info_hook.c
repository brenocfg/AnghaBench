#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TimescaleDBPrivate ;
struct TYPE_17__ {TYPE_1__* parse; } ;
struct TYPE_16__ {int /*<<< orphan*/  relid; int /*<<< orphan*/  inh; } ;
struct TYPE_15__ {int /*<<< orphan*/  fdw_private; int /*<<< orphan*/  relid; } ;
struct TYPE_14__ {int /*<<< orphan*/  rtable; } ;
typedef  TYPE_2__ RelOptInfo ;
typedef  TYPE_3__ RangeTblEntry ;
typedef  TYPE_4__ PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ is_rte_hypertable (TYPE_3__*) ; 
 int /*<<< orphan*/  palloc0 (int) ; 
 int /*<<< orphan*/  prev_get_relation_info_hook (TYPE_4__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 TYPE_3__* rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_append_rel_array (TYPE_4__*) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_extension_is_loaded () ; 
 int /*<<< orphan*/  ts_guc_enable_constraint_exclusion ; 
 int /*<<< orphan*/ * ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 int /*<<< orphan*/  ts_plan_expand_hypertable_chunks (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static void
timescaledb_get_relation_info_hook(PlannerInfo *root, Oid relation_objectid, bool inhparent,
								   RelOptInfo *rel)
{
	RangeTblEntry *rte;

	if (prev_get_relation_info_hook != NULL)
		prev_get_relation_info_hook(root, relation_objectid, inhparent, rel);

	if (!ts_extension_is_loaded() || !ts_guc_enable_constraint_exclusion)
		return;

	rte = rt_fetch(rel->relid, root->parse->rtable);

	/*
	 * We expand the hypertable chunks into an append relation. Previously, in
	 * `turn_off_inheritance_walker` we suppressed this expansion. This hook
	 * is really the first one that's called after the initial planner setup
	 * and so it's convenient to do the expansion here. Note that this is
	 * after the usual expansion happens in `expand_inherited_tables` (called
	 * in `subquery_planner`). Note also that `get_relation_info` (the
	 * function that calls this hook at the end) is the expensive function to
	 * run on many chunks so the expansion really cannot be called before this
	 * hook.
	 */
	if (!rte->inh && is_rte_hypertable(rte))
	{
		Cache *hcache = ts_hypertable_cache_pin();
		Hypertable *ht = ts_hypertable_cache_get_entry(hcache, rte->relid);

		Assert(ht != NULL);

		rel->fdw_private = palloc0(sizeof(TimescaleDBPrivate));

		ts_plan_expand_hypertable_chunks(ht, root, relation_objectid, inhparent, rel);
#if !PG96 && !PG10
		setup_append_rel_array(root);
#endif

		ts_cache_release(hcache);
	}
}