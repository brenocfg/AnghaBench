#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ parent_reloid; } ;
struct TYPE_11__ {TYPE_1__* parse; } ;
struct TYPE_10__ {scalar_t__ relid; } ;
struct TYPE_9__ {scalar_t__ commandType; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  TYPE_3__ PlannerInfo ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  int /*<<< orphan*/  Cache ;
typedef  TYPE_4__ AppendRelInfo ;

/* Variables and functions */
 scalar_t__ CMD_DELETE ; 
 scalar_t__ CMD_UPDATE ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 TYPE_4__* ts_get_appendrelinfo (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 

__attribute__((used)) static bool
is_hypertable_chunk_dml(PlannerInfo *root, RelOptInfo *rel, Index rti, RangeTblEntry *rte)
{
	if (root->parse->commandType == CMD_UPDATE || root->parse->commandType == CMD_DELETE)
	{
		Oid parent_oid;
		AppendRelInfo *appinfo = ts_get_appendrelinfo(root, rti, true);
		if (!appinfo)
			return false;
		parent_oid = appinfo->parent_reloid;
		if (parent_oid != InvalidOid && rte->relid != parent_oid)
		{
			Cache *hcache = ts_hypertable_cache_pin();
			Hypertable *parent_ht = ts_hypertable_cache_get_entry(hcache, parent_oid);
			ts_cache_release(hcache);
			if (parent_ht)
				return true;
		}
	}
	return false;
}