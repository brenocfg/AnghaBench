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
struct TYPE_3__ {int /*<<< orphan*/ ** append_rel_array; } ;
typedef  TYPE_1__ PlannerInfo ;
typedef  size_t Index ;
typedef  int /*<<< orphan*/  AppendRelInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,size_t) ; 
 int /*<<< orphan*/  pg_unreachable () ; 

__attribute__((used)) static AppendRelInfo *
get_appendrelinfo(PlannerInfo *root, Index rti)
{
#if PG96 || PG10
	ListCell *lc;
	foreach (lc, root->append_rel_list)
	{
		AppendRelInfo *appinfo = lfirst(lc);
		if (appinfo->child_relid == rti)
			return appinfo;
	}
#else
	if (root->append_rel_array[rti])
		return root->append_rel_array[rti];
#endif
	ereport(ERROR,
			(errcode(ERRCODE_INTERNAL_ERROR), errmsg("no appendrelinfo found for index %d", rti)));
	pg_unreachable();
}