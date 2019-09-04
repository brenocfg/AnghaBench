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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_CTask ; 
 int /*<<< orphan*/  CLSID_CTaskScheduler ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_ITask ; 
 int /*<<< orphan*/  IID_ITaskScheduler ; 
 scalar_t__ ITaskScheduler_NewWorkItem (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITaskScheduler_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  test_task ; 
 int /*<<< orphan*/  test_task_scheduler ; 

__attribute__((used)) static BOOL setup_task(void)
{
    HRESULT hres;
    const WCHAR task_name[] = {'T','e','s','t','i','n','g', 0};

    hres = CoCreateInstance(&CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER,
            &IID_ITaskScheduler, (void **) &test_task_scheduler);
    if(hres != S_OK)
        return FALSE;
    hres = ITaskScheduler_NewWorkItem(test_task_scheduler, task_name, &CLSID_CTask,
            &IID_ITask, (IUnknown**)&test_task);
    if(hres != S_OK)
    {
        ITaskScheduler_Release(test_task_scheduler);
        return FALSE;
    }
    return TRUE;
}