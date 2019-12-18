#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  (* set_rel_pathlist_dml ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  relid; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 scalar_t__ IS_DUMMY_REL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_parentoid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_append_child (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ is_append_parent (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int is_hypertable_chunk_dml (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  prev_set_rel_pathlist_hook (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timescaledb_set_rel_pathlist_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 TYPE_2__* ts_cm_functions ; 
 int /*<<< orphan*/  ts_extension_is_loaded () ; 
 int /*<<< orphan*/  ts_guc_optimize_non_hypertables ; 
 int /*<<< orphan*/ * ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 

__attribute__((used)) static void
timescaledb_set_rel_pathlist(PlannerInfo *root, RelOptInfo *rel, Index rti, RangeTblEntry *rte)
{
	Hypertable *ht;
	Cache *hcache;
	Oid ht_reloid = rte->relid;
	bool is_htdml;

	if (prev_set_rel_pathlist_hook != NULL)
		(*prev_set_rel_pathlist_hook)(root, rel, rti, rte);

	if (!ts_extension_is_loaded() || IS_DUMMY_REL(rel) || !OidIsValid(rte->relid))
		return;

	/* do we have a DML transformation here */
	is_htdml = is_hypertable_chunk_dml(root, rel, rti, rte);

	/* quick abort if only optimizing hypertables */
	if (!ts_guc_optimize_non_hypertables &&
		!(is_append_parent(rel, rte) || is_append_child(rel, rte) || is_htdml))
		return;

	hcache = ts_hypertable_cache_pin();

	/*
	 * if this is an append child or DML we use the parent relid to
	 * check if its a hypertable
	 */
	if (is_append_child(rel, rte) || is_htdml)
		ht_reloid = get_parentoid(root, rti);

	ht = ts_hypertable_cache_get_entry(hcache, ht_reloid);

	if (!is_htdml)
	{
		timescaledb_set_rel_pathlist_query(root, rel, rti, rte, ht);
	}
	else
	{
		if (ts_cm_functions->set_rel_pathlist_dml != NULL)
			ts_cm_functions->set_rel_pathlist_dml(root, rel, rti, rte, ht);
	}

	ts_cache_release(hcache);
}