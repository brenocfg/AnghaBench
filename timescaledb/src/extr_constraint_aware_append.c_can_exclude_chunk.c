#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  es_range_table; } ;
struct TYPE_6__ {scalar_t__ rtekind; scalar_t__ relkind; int /*<<< orphan*/  inh; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_2__ EState ;

/* Variables and functions */
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RTE_RELATION ; 
 scalar_t__ excluded_by_constraint (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
can_exclude_chunk(PlannerInfo *root, EState *estate, Index rt_index, List *restrictinfos)
{
	RangeTblEntry *rte = rt_fetch(rt_index, estate->es_range_table);

	return rte->rtekind == RTE_RELATION && rte->relkind == RELKIND_RELATION && !rte->inh &&
		   excluded_by_constraint(root, rte, rt_index, restrictinfos);
}