#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * baserestrictinfo; int /*<<< orphan*/  reloptkind; int /*<<< orphan*/  relid; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  RELOPT_OTHER_MEMBER_REL ; 
 int /*<<< orphan*/  T_RelOptInfo ; 
 int relation_excluded_by_constraints (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
excluded_by_constraint(PlannerInfo *root, RangeTblEntry *rte, Index rt_index, List *restrictinfos)
{
	RelOptInfo rel = {
		.type = T_RelOptInfo,
		.relid = rt_index,
		.reloptkind = RELOPT_OTHER_MEMBER_REL,
		.baserestrictinfo = restrictinfos,
	};

	return relation_excluded_by_constraints(root, &rel, rte);
}