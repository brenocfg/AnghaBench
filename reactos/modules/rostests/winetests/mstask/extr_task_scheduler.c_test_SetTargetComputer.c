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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_CTaskScheduler ; 
 int /*<<< orphan*/  CharLowerW (char*) ; 
 int /*<<< orphan*/  CharUpperW (char*) ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 int /*<<< orphan*/  ERROR_BAD_NETPATH ; 
 scalar_t__ E_ACCESSDENIED ; 
 int /*<<< orphan*/  GetComputerNameW (char*,int*) ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_ITaskScheduler ; 
 scalar_t__ ITaskScheduler_GetTargetComputer (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ITaskScheduler_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ ITaskScheduler_SetTargetComputer (int /*<<< orphan*/ ,char*) ; 
 int MAX_COMPUTERNAME_LENGTH ; 
 scalar_t__ S_OK ; 
 char* does_not_existW ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_task_scheduler ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_SetTargetComputer(void)
{
    WCHAR buffer[MAX_COMPUTERNAME_LENGTH + 3];  /* extra space for two '\' and a zero */
    DWORD len = MAX_COMPUTERNAME_LENGTH + 1;    /* extra space for a zero */
    WCHAR *oldname = NULL;
    WCHAR *name = NULL;
    HRESULT hres;


    buffer[0] = '\\';
    buffer[1] = '\\';
    if (!GetComputerNameW(buffer + 2, &len))
        return;

    /* Create TaskScheduler */
    hres = CoCreateInstance(&CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER,
            &IID_ITaskScheduler, (void **) &test_task_scheduler);
    ok(hres == S_OK, "CTaskScheduler CoCreateInstance failed: %08x\n", hres);
    if (hres != S_OK)
    {
        skip("Failed to create task scheduler.  Skipping tests.\n");
        return;
    }

    hres = ITaskScheduler_GetTargetComputer(test_task_scheduler, &oldname);
    ok(hres == S_OK, "got 0x%x and %s (expected S_OK)\n", hres, wine_dbgstr_w(oldname));

    /* NULL is an alias for the local computer */
    hres = ITaskScheduler_SetTargetComputer(test_task_scheduler, NULL);
    ok(hres == S_OK, "got 0x%x (expected S_OK)\n", hres);
    hres = ITaskScheduler_GetTargetComputer(test_task_scheduler, &name);
    ok((hres == S_OK && !lstrcmpiW(name, buffer)),
        "got 0x%x with %s (expected S_OK and %s)\n",
        hres, wine_dbgstr_w(name), wine_dbgstr_w(buffer));
    CoTaskMemFree(name);

    /* The name must be valid */
    hres = ITaskScheduler_SetTargetComputer(test_task_scheduler, does_not_existW);
    ok(hres == HRESULT_FROM_WIN32(ERROR_BAD_NETPATH), "got 0x%x (expected 0x80070035)\n", hres);
    /* the name of the target computer is unchanged */
    hres = ITaskScheduler_GetTargetComputer(test_task_scheduler, &name);
    ok((hres == S_OK && !lstrcmpiW(name, buffer)),
        "got 0x%x with %s (expected S_OK and %s)\n",
        hres, wine_dbgstr_w(name), wine_dbgstr_w(buffer));
    CoTaskMemFree(name);

    /* the two backslashes are optional */
    hres = ITaskScheduler_SetTargetComputer(test_task_scheduler, oldname + 2);
    if (hres == E_ACCESSDENIED)
    {
        skip("SetTargetComputer failed with E_ACCESSDENIED (needs admin rights)\n");
        goto done;
    }
    ok(hres == S_OK, "got 0x%x (expected S_OK)\n", hres);

    /* the case is ignored */
    CharUpperW(buffer);
    hres = ITaskScheduler_SetTargetComputer(test_task_scheduler, buffer);
    ok(hres == S_OK, "got 0x%x (expected S_OK)\n", hres);
    CharLowerW(buffer);
    hres = ITaskScheduler_SetTargetComputer(test_task_scheduler, buffer);
    ok(hres == S_OK, "got 0x%x (expected S_OK)\n", hres);

    /* cleanup */
    hres = ITaskScheduler_SetTargetComputer(test_task_scheduler, oldname);
    ok(hres == S_OK, "got 0x%x (expected S_OK)\n", hres);

done:
    CoTaskMemFree(oldname);
    ITaskScheduler_Release(test_task_scheduler);
    return;
}