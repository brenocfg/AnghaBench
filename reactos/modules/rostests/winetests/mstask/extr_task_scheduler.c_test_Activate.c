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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITask ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_CTaskScheduler ; 
 scalar_t__ COR_E_FILENOTFOUND ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_ITask ; 
 int /*<<< orphan*/  IID_ITaskScheduler ; 
 scalar_t__ ITaskScheduler_Activate (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITaskScheduler_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_task_scheduler ; 

__attribute__((used)) static void test_Activate(void)
{
    HRESULT hres;
    ITask *task = NULL;
    const WCHAR not_task_name[] =
            {'N', 'o', 'S', 'u', 'c', 'h', 'T', 'a', 's', 'k', 0};

    /* Create TaskScheduler */
    hres = CoCreateInstance(&CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER,
            &IID_ITaskScheduler, (void **) &test_task_scheduler);
    ok(hres == S_OK, "CTaskScheduler CoCreateInstance failed: %08x\n", hres);
    if (hres != S_OK)
    {
        skip("Failed to create task scheduler.  Skipping tests.\n");
        return;
    }

    /* Attempt to activate a nonexistent task */
    hres = ITaskScheduler_Activate(test_task_scheduler, not_task_name,
            &IID_ITask, (IUnknown**)&task);
    ok(hres == COR_E_FILENOTFOUND, "Expected COR_E_FILENOTFOUND: %08x\n", hres);

    ITaskScheduler_Release(test_task_scheduler);
    return;
}