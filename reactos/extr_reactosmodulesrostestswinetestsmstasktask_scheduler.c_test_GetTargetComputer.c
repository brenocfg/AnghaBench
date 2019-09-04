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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_CTaskScheduler ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IID_ITaskScheduler ; 
 scalar_t__ ITaskScheduler_GetTargetComputer (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ITaskScheduler_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_task_scheduler ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_GetTargetComputer(void)
{
    HRESULT hres;
    WCHAR *oldname;

    /* Create TaskScheduler */
    hres = CoCreateInstance(&CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER,
            &IID_ITaskScheduler, (void **) &test_task_scheduler);
    ok(hres == S_OK, "CTaskScheduler CoCreateInstance failed: %08x\n", hres);
    if (hres != S_OK)
    {
        skip("Failed to create task scheduler.\n");
        return;
    }

    if (0)
    {
        /* This crashes on w2k */
        hres = ITaskScheduler_GetTargetComputer(test_task_scheduler, NULL);
        ok(hres == E_INVALIDARG, "got 0x%x (expected E_INVALIDARG)\n", hres);
    }

    hres = ITaskScheduler_GetTargetComputer(test_task_scheduler, &oldname);
    ok((hres == S_OK) && oldname && oldname[0] == '\\' && oldname[1] == '\\' && oldname[2],
        "got 0x%x and %s (expected S_OK and an unc name)\n", hres, wine_dbgstr_w(oldname));

    CoTaskMemFree(oldname);

    ITaskScheduler_Release(test_task_scheduler);
    return;
}