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
struct TYPE_6__ {scalar_t__ rowMarks; scalar_t__ resultRelation; } ;
struct TYPE_5__ {int inh; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Hypertable ;

/* Variables and functions */
 scalar_t__ NIL ; 

bool
ts_plan_expand_hypertable_valid_hypertable(Hypertable *ht, Query *parse, Index rti,
										   RangeTblEntry *rte)
{
	if (ht == NULL ||
		/* inheritance enabled */
		rte->inh == false ||
		/* row locks not necessary */
		parse->rowMarks != NIL ||
		/* not update and/or delete */
		0 != parse->resultRelation)
		return false;

	return true;
}