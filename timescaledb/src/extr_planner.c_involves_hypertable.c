#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int reloptkind; int /*<<< orphan*/  relids; int /*<<< orphan*/  relid; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
#define  RELOPT_BASEREL 130 
#define  RELOPT_JOINREL 129 
#define  RELOPT_OTHER_MEMBER_REL 128 
 int involves_hypertable_relid_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int involves_ts_hypertable_relid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_append_child (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_append_parent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * planner_rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
involves_hypertable(PlannerInfo *root, RelOptInfo *rel)
{
	RangeTblEntry *rte;

	switch (rel->reloptkind)
	{
		case RELOPT_BASEREL:
		case RELOPT_OTHER_MEMBER_REL:
			/* Optimization for a quick exit */
			rte = planner_rt_fetch(rel->relid, root);
			if (!(is_append_parent(rel, rte) || is_append_child(rel, rte)))
				return false;

			return involves_ts_hypertable_relid(root, rel->relid);
		case RELOPT_JOINREL:
			return involves_hypertable_relid_set(root, rel->relids);
		default:
			return false;
	}
}