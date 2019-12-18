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
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ CLASS_E_CLASSNOTAVAILABLE ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_CTask ; 
 int /*<<< orphan*/  CLSID_CTaskScheduler ; 
 int /*<<< orphan*/  CoCreateGuid (int /*<<< orphan*/ *) ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_ITask ; 
 int /*<<< orphan*/  IID_ITaskScheduler ; 
 scalar_t__ ITaskScheduler_NewWorkItem (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITaskScheduler_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITask_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_task_scheduler ; 

__attribute__((used)) static void test_NewWorkItem(void)
{
    HRESULT hres;
    ITask *task;
    const WCHAR task_name[] = {'T', 'e', 's', 't', 'i', 'n', 'g', 0};
    GUID GUID_BAD;

    /* Initialize a GUID that will not be a recognized CLSID or a IID */
    CoCreateGuid(&GUID_BAD);

    /* Create TaskScheduler */
    hres = CoCreateInstance(&CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER,
            &IID_ITaskScheduler, (void **) &test_task_scheduler);
    ok(hres == S_OK, "CTaskScheduler CoCreateInstance failed: %08x\n", hres);
    if (hres != S_OK)
    {
        skip("Failed to create task scheduler.  Skipping tests.\n");
        return;
    }

    /* Test basic task creation */
    hres = ITaskScheduler_NewWorkItem(test_task_scheduler, task_name,
            &CLSID_CTask, &IID_ITask, (IUnknown**)&task);
    ok(hres == S_OK, "NewNetworkItem failed: %08x\n", hres);
    if (hres == S_OK)
        ITask_Release(task);

    /* Task creation attempt using invalid work item class ID */
    hres = ITaskScheduler_NewWorkItem(test_task_scheduler, task_name,
            &GUID_BAD, &IID_ITask, (IUnknown**)&task);
    ok(hres == CLASS_E_CLASSNOTAVAILABLE,
            "Expected CLASS_E_CLASSNOTAVAILABLE: %08x\n", hres);

    /* Task creation attempt using invalid interface ID */
    hres = ITaskScheduler_NewWorkItem(test_task_scheduler, task_name,
            &CLSID_CTask, &GUID_BAD, (IUnknown**)&task);
    ok(hres == E_NOINTERFACE, "Expected E_NOINTERFACE: %08x\n", hres);

    /* Task creation attempt using invalid work item class and interface ID */
    hres = ITaskScheduler_NewWorkItem(test_task_scheduler, task_name,
            &GUID_BAD, &GUID_BAD, (IUnknown**)&task);
    ok(hres == CLASS_E_CLASSNOTAVAILABLE,
            "Expected CLASS_E_CLASSNOTAVAILABLE: %08x\n", hres);

    ITaskScheduler_Release(test_task_scheduler);
    return;
}