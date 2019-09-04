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
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int INFINITE ; 
 int ITask_GetMaxRunTime (int /*<<< orphan*/ ,int*) ; 
 int ITask_SetMaxRunTime (int /*<<< orphan*/ ,int) ; 
 int S_OK ; 
 int /*<<< orphan*/  cleanup_task () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  setup_task () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_task ; 

__attribute__((used)) static void test_SetMaxRunTime_GetMaxRunTime(void)
{
    BOOL setup;
    HRESULT hres;
    DWORD max_run_time;

    setup = setup_task();
    ok(setup, "Failed to setup test_task\n");
    if (!setup)
    {
        skip("Failed to create task.  Skipping tests.\n");
        return;
    }

    /* Default time is 3 days:
     * 3 days * 24 hours * 60 minutes * 60 seconds * 1000 ms = 259200000 */
    max_run_time = 0;
    hres = ITask_GetMaxRunTime(test_task, &max_run_time);
    ok(hres == S_OK, "Failed to get max runtime: 0x%08x\n", hres);
    ok(max_run_time == 259200000, "Expected 259200000: %d\n", max_run_time);

    /* Basic set test */
    max_run_time = 0;
    hres = ITask_SetMaxRunTime(test_task, 1234);
    ok(hres == S_OK, "Failed to set max runtime: 0x%08x\n", hres);
    hres = ITask_GetMaxRunTime(test_task, &max_run_time);
    ok(hres == S_OK, "Failed to get max runtime: 0x%08x\n", hres);
    ok(max_run_time == 1234, "Expected 1234: %d\n", max_run_time);

    /* Verify that time can be set to zero */
    max_run_time = 1;
    hres = ITask_SetMaxRunTime(test_task, 0);
    ok(hres == S_OK, "Failed to set max runtime: 0x%08x\n", hres);
    hres = ITask_GetMaxRunTime(test_task, &max_run_time);
    ok(hres == S_OK, "Failed to get max runtime: 0x%08x\n", hres);
    ok(max_run_time == 0, "Expected 0: %d\n", max_run_time);

    /* Check resolution by setting time to one */
    max_run_time = 0;
    hres = ITask_SetMaxRunTime(test_task, 1);
    ok(hres == S_OK, "Failed to set max runtime: 0x%08x\n", hres);
    hres = ITask_GetMaxRunTime(test_task, &max_run_time);
    ok(hres == S_OK, "Failed to get max runtime: 0x%08x\n", hres);
    ok(max_run_time == 1, "Expected 1: %d\n", max_run_time);

    /* Verify that time can be set to INFINITE */
    max_run_time = 0;
    hres = ITask_SetMaxRunTime(test_task, INFINITE);
    ok(hres == S_OK, "Failed to set max runtime: 0x%08x\n", hres);
    hres = ITask_GetMaxRunTime(test_task, &max_run_time);
    ok(hres == S_OK, "Failed to get max runtime: 0x%08x\n", hres);
    ok(max_run_time == INFINITE, "Expected INFINITE: %d\n", max_run_time);

    cleanup_task();
    return;
}