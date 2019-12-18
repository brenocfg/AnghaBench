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
 int /*<<< orphan*/  ITaskScheduler_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITaskTrigger_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITask_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_task ; 
 int /*<<< orphan*/  test_task_scheduler ; 
 int /*<<< orphan*/  test_trigger ; 

__attribute__((used)) static void cleanup_trigger(void)
{
    ITaskTrigger_Release(test_trigger);
    ITask_Release(test_task);
    ITaskScheduler_Release(test_task_scheduler);
}