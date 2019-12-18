#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int compressed; } ;
typedef  TYPE_3__ TimescaleDBPrivate ;
struct TYPE_22__ {scalar_t__ compressed_chunk_id; } ;
struct TYPE_27__ {TYPE_2__ fd; } ;
struct TYPE_26__ {TYPE_1__* parse; } ;
struct TYPE_25__ {int /*<<< orphan*/  relid; int /*<<< orphan*/  inh; } ;
struct TYPE_24__ {int /*<<< orphan*/  indexlist; int /*<<< orphan*/ * fdw_private; int /*<<< orphan*/  relid; } ;
struct TYPE_21__ {int /*<<< orphan*/  rtable; } ;
typedef  TYPE_4__ RelOptInfo ;
typedef  TYPE_5__ RangeTblEntry ;
typedef  TYPE_6__ PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_7__ Chunk ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 scalar_t__ TS_HYPERTABLE_HAS_COMPRESSION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_parentoid (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_append_child (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ is_rte_hypertable (TYPE_5__*) ; 
 void* palloc0 (int) ; 
 int /*<<< orphan*/  prev_get_relation_info_hook (TYPE_6__*,int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 TYPE_5__* rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_append_rel_array (TYPE_6__*) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 TYPE_7__* ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_extension_is_loaded () ; 
 int /*<<< orphan*/  ts_guc_enable_constraint_exclusion ; 
 scalar_t__ ts_guc_enable_transparent_decompression ; 
 int /*<<< orphan*/ * ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 int /*<<< orphan*/  ts_plan_expand_hypertable_chunks (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int,TYPE_4__*) ; 

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

		Assert(rel->fdw_private == NULL);
		rel->fdw_private = palloc0(sizeof(TimescaleDBPrivate));

		ts_plan_expand_hypertable_chunks(ht, root, relation_objectid, inhparent, rel);
#if PG11_GE
		setup_append_rel_array(root);
#endif

		ts_cache_release(hcache);
	}

	if (ts_guc_enable_transparent_decompression && is_append_child(rel, rte))
	{
		Oid ht_oid = get_parentoid(root, rel->relid);
		Cache *hcache = ts_hypertable_cache_pin();
		Hypertable *ht = ts_hypertable_cache_get_entry(hcache, ht_oid);

		if (ht != NULL && TS_HYPERTABLE_HAS_COMPRESSION(ht))
		{
			Chunk *chunk = ts_chunk_get_by_relid(rte->relid, 0, true);

			if (chunk->fd.compressed_chunk_id > 0)
			{
				Assert(rel->fdw_private == NULL);
				rel->fdw_private = palloc0(sizeof(TimescaleDBPrivate));
				((TimescaleDBPrivate *) rel->fdw_private)->compressed = true;

				/* Planning indexes are expensive, and if this is a compressed chunk, we
				 * know we'll never need to us indexes on the uncompressed version, since all
				 * the data is in the compressed chunk anyway. Therefore, it is much faster if
				 * we simply trash the indexlist here and never plan any useless IndexPaths
				 *  at all
				 */
				rel->indexlist = NIL;
			}
		}
		ts_cache_release(hcache);
	}
}