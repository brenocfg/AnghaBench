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
struct TYPE_3__ {int /*<<< orphan*/ * ctename; } ;
typedef  TYPE_1__ RangeTblEntry ;

/* Variables and functions */
 int /*<<< orphan*/  CTE_NAME_HYPERTABLES ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_rte_hypertable(RangeTblEntry *rte)
{
	return rte->ctename != NULL && strcmp(rte->ctename, CTE_NAME_HYPERTABLES) == 0;
}