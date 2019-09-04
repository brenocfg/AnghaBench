#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__** append_rel_array; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent_reloid; } ;
typedef  TYPE_2__ PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  size_t Index ;

/* Variables and functions */

__attribute__((used)) static Oid
get_parentoid(PlannerInfo *root, Index rti)
{
#if PG96 || PG10
	ListCell *lc;
	foreach (lc, root->append_rel_list)
	{
		AppendRelInfo *appinfo = lfirst(lc);
		if (appinfo->child_relid == rti)
			return appinfo->parent_reloid;
	}
#else
	if (root->append_rel_array[rti])
		return root->append_rel_array[rti]->parent_reloid;
#endif
	return 0;
}