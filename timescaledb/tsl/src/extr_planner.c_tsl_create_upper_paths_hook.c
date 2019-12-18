#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UpperRelationKind ;
struct TYPE_7__ {int /*<<< orphan*/  pathlist; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CustomPath ; 
 scalar_t__ IsA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UPPERREL_GROUP_AGG ; 
 scalar_t__ UPPERREL_WINDOW ; 
 int /*<<< orphan*/  gapfill_adjust_window_targetlist (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plan_add_gapfill (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
tsl_create_upper_paths_hook(PlannerInfo *root, UpperRelationKind stage, RelOptInfo *input_rel,
							RelOptInfo *output_rel)
{
	if (UPPERREL_GROUP_AGG == stage)
		plan_add_gapfill(root, output_rel);
	if (UPPERREL_WINDOW == stage)
	{
		if (IsA(linitial(input_rel->pathlist), CustomPath))
			gapfill_adjust_window_targetlist(root, input_rel, output_rel);
	}
}