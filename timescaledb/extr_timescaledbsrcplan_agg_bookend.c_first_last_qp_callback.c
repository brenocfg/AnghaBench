#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sort_pathkeys; int /*<<< orphan*/  query_pathkeys; TYPE_1__* parse; void* distinct_pathkeys; void* window_pathkeys; void* group_pathkeys; } ;
struct TYPE_5__ {int /*<<< orphan*/  targetList; int /*<<< orphan*/  sortClause; } ;
typedef  TYPE_2__ PlannerInfo ;

/* Variables and functions */
 void* NIL ; 
 int /*<<< orphan*/  make_pathkeys_for_sortclauses (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
first_last_qp_callback(PlannerInfo *root, void *extra)
{
	root->group_pathkeys = NIL;
	root->window_pathkeys = NIL;
	root->distinct_pathkeys = NIL;

	root->sort_pathkeys =
		make_pathkeys_for_sortclauses(root, root->parse->sortClause, root->parse->targetList);

	root->query_pathkeys = root->sort_pathkeys;
}