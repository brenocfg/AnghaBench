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
typedef  int /*<<< orphan*/  ITaskScheduler ;
typedef  int /*<<< orphan*/  IEnumWorkItems ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_CTaskScheduler ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IEnumWorkItems_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_ITaskScheduler ; 
 scalar_t__ ITaskScheduler_Enum (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITaskScheduler_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_Enum(void)
{
    ITaskScheduler *scheduler;
    IEnumWorkItems *tasks;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER,
            &IID_ITaskScheduler, (void **)&scheduler);
    ok(hr == S_OK, "got 0x%08x\n", hr);

if (0) { /* crashes on win2k */
    hr = ITaskScheduler_Enum(scheduler, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
}

    hr = ITaskScheduler_Enum(scheduler, &tasks);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    IEnumWorkItems_Release(tasks);

    ITaskScheduler_Release(scheduler);
}