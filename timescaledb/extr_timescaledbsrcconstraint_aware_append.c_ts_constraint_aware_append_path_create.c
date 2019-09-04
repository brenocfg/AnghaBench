#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int parallel_aware; int /*<<< orphan*/  parallel_workers; int /*<<< orphan*/  parallel_safe; int /*<<< orphan*/  pathtarget; int /*<<< orphan*/  param_info; int /*<<< orphan*/  pathkeys; int /*<<< orphan*/  parent; int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; int /*<<< orphan*/  rows; int /*<<< orphan*/  pathtype; } ;
struct TYPE_8__ {TYPE_2__ path; int /*<<< orphan*/ * methods; int /*<<< orphan*/  custom_paths; scalar_t__ flags; } ;
struct TYPE_10__ {TYPE_1__ cpath; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_2__ Path ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_3__ ConstraintAwareAppendPath ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  T_AppendPath 129 
 int /*<<< orphan*/  T_CustomPath ; 
 int /*<<< orphan*/  T_CustomScan ; 
#define  T_MergeAppendPath 128 
 int /*<<< orphan*/  constraint_aware_append_path_methods ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  list_make1 (TYPE_2__*) ; 
 scalar_t__ newNode (int,int /*<<< orphan*/ ) ; 
 int nodeTag (TYPE_2__*) ; 

Path *
ts_constraint_aware_append_path_create(PlannerInfo *root, Hypertable *ht, Path *subpath)
{
	ConstraintAwareAppendPath *path;

	path = (ConstraintAwareAppendPath *) newNode(sizeof(ConstraintAwareAppendPath), T_CustomPath);
	path->cpath.path.pathtype = T_CustomScan;
	path->cpath.path.rows = subpath->rows;
	path->cpath.path.startup_cost = subpath->startup_cost;
	path->cpath.path.total_cost = subpath->total_cost;
	path->cpath.path.parent = subpath->parent;
	path->cpath.path.pathkeys = subpath->pathkeys;
	path->cpath.path.param_info = subpath->param_info;
	path->cpath.path.pathtarget = subpath->pathtarget;

	path->cpath.path.parallel_aware = false;
	path->cpath.path.parallel_safe = subpath->parallel_safe;
	path->cpath.path.parallel_workers = subpath->parallel_workers;

	/*
	 * Set flags. We can set CUSTOMPATH_SUPPORT_BACKWARD_SCAN and
	 * CUSTOMPATH_SUPPORT_MARK_RESTORE. The only interesting flag is the first
	 * one (backward scan), but since we are not scanning a real relation we
	 * need not indicate that we support backward scans. Lower-level index
	 * scanning nodes will scan backward if necessary, so once tuples get to
	 * this node they will be in a given order already.
	 */
	path->cpath.flags = 0;
	path->cpath.custom_paths = list_make1(subpath);
	path->cpath.methods = &constraint_aware_append_path_methods;

	/*
	 * Make sure our subpath is either an Append or MergeAppend node
	 */
	switch (nodeTag(subpath))
	{
		case T_AppendPath:
		case T_MergeAppendPath:
			break;
		default:
			elog(ERROR, "invalid child of constraint-aware append: %u", nodeTag(subpath));
			break;
	}

	return &path->cpath.path;
}