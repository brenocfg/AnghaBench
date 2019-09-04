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

/* Variables and functions */
 int /*<<< orphan*/  ProcessUtility_hook ; 
 int /*<<< orphan*/  RegisterSubXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prev_ProcessUtility_hook ; 
 int /*<<< orphan*/  process_utility_subxact_abort ; 
 int /*<<< orphan*/  process_utility_xact_abort ; 
 int /*<<< orphan*/  timescaledb_ddl_command_start ; 

void
_process_utility_init(void)
{
	prev_ProcessUtility_hook = ProcessUtility_hook;
	ProcessUtility_hook = timescaledb_ddl_command_start;
	RegisterXactCallback(process_utility_xact_abort, NULL);
	RegisterSubXactCallback(process_utility_subxact_abort, NULL);
}