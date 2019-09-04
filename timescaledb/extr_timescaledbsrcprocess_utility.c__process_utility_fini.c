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
 int /*<<< orphan*/  UnregisterSubXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnregisterXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prev_ProcessUtility_hook ; 
 int /*<<< orphan*/  process_utility_subxact_abort ; 
 int /*<<< orphan*/  process_utility_xact_abort ; 

void
_process_utility_fini(void)
{
	ProcessUtility_hook = prev_ProcessUtility_hook;
	UnregisterXactCallback(process_utility_xact_abort, NULL);
	UnregisterSubXactCallback(process_utility_subxact_abort, NULL);
}