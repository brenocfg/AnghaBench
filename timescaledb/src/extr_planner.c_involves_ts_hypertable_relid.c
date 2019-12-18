#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  scalar_t__ Index ;

/* Variables and functions */
 int is_rte_hypertable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  planner_rt_fetch (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
involves_ts_hypertable_relid(PlannerInfo *root, Index relid)
{
	if (relid == 0)
		return false;

	return is_rte_hypertable(planner_rt_fetch(relid, root));
}