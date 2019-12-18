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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ICorDebug ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ ICorDebug_Initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICorDebug_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ICorDebug_SetManagedHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_ICorDebug ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ManagedCallback ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  check_process_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCreateDebuggingInterfaceFromVersion (int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  v2_0 ; 

__attribute__((used)) static void test_createDebugger(void)
{
    HRESULT hr;
    IUnknown *pUnk;
    ICorDebug *pCorDebug;

    hr = pCreateDebuggingInterfaceFromVersion(0, v2_0, &pUnk);
    ok(hr == E_INVALIDARG, "CreateDebuggingInterfaceFromVersion returned %08x\n", hr);

    hr = pCreateDebuggingInterfaceFromVersion(1, v2_0, &pUnk);
    ok(hr == E_INVALIDARG, "CreateDebuggingInterfaceFromVersion returned %08x\n", hr);

    hr = pCreateDebuggingInterfaceFromVersion(2, v2_0, &pUnk);
    ok(hr == E_INVALIDARG, "CreateDebuggingInterfaceFromVersion returned %08x\n", hr);

    hr = pCreateDebuggingInterfaceFromVersion(4, v2_0, &pUnk);
    ok(hr == E_INVALIDARG, "CreateDebuggingInterfaceFromVersion returned %08x\n", hr);

    hr = pCreateDebuggingInterfaceFromVersion(3, v2_0, NULL);
    ok(hr == E_INVALIDARG, "CreateDebuggingInterfaceFromVersion returned %08x\n", hr);

    hr = pCreateDebuggingInterfaceFromVersion(3, v2_0, &pUnk);
    if(hr == S_OK)
    {
        hr = IUnknown_QueryInterface(pUnk, &IID_ICorDebug, (void**)&pCorDebug);
        ok(hr == S_OK, "expected S_OK got %08x\n", hr);
        if(hr == S_OK)
        {
            hr = ICorDebug_Initialize(pCorDebug);
            ok(hr == S_OK, "expected S_OK got %08x\n", hr);
            if(hr == S_OK)
            {
                hr = ICorDebug_SetManagedHandler(pCorDebug, NULL);
                ok(hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr);

                hr = ICorDebug_SetManagedHandler(pCorDebug, &ManagedCallback);
                ok(hr == S_OK, "expected S_OK got %08x\n", hr);

                /* We should have no processes */
                check_process_enum(pCorDebug, 0);
            }

            ICorDebug_Release(pCorDebug);
        }
        IUnknown_Release(pUnk);
    }
    else
    {
        skip(".NET 2.0 or mono not installed.\n");
    }
}