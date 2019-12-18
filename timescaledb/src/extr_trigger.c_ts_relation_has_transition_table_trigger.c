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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  check_for_transition_table ; 
 int /*<<< orphan*/  for_each_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

bool
ts_relation_has_transition_table_trigger(Oid relid)
{
	bool found = false;

#if PG10_GE
	for_each_trigger(relid, check_for_transition_table, &found);
#endif

	return found;
}