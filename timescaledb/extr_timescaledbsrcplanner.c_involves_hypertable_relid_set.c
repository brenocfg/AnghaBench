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
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int bms_next_member (int /*<<< orphan*/ ,int) ; 
 scalar_t__ involves_ts_hypertable_relid (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
involves_hypertable_relid_set(PlannerInfo *root, Relids relid_set)
{
	int relid = -1;

	while ((relid = bms_next_member(relid_set, relid)) >= 0)
	{
		if (involves_ts_hypertable_relid(root, relid))
			return true;
	}
	return false;
}