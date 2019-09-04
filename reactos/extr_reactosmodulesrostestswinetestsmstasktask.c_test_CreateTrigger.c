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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  ITaskTrigger ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ITaskTrigger_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITask_CreateTrigger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  cleanup_task () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  setup_task () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_task ; 

__attribute__((used)) static void test_CreateTrigger(void)
{
    BOOL setup;
    HRESULT hres;
    WORD trigger_index;
    ITaskTrigger *test_trigger;

    setup = setup_task();
    ok(setup, "Failed to setup test_task\n");
    if (!setup)
    {
        skip("Failed to create task.  Skipping tests.\n");
        return;
    }

    hres = ITask_CreateTrigger(test_task, &trigger_index, &test_trigger);
    ok(hres == S_OK, "Failed to create trigger: 0x%08x\n", hres);
    if (hres != S_OK)
    {
        cleanup_task();
        return;
    }

    ITaskTrigger_Release(test_trigger);
    cleanup_task();
    return;
}