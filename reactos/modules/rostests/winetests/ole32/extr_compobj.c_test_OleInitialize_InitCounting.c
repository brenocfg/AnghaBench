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
typedef  int /*<<< orphan*/ * REFCLSID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_InternetZoneManager ; 
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 scalar_t__ CO_E_NOTINITIALIZED ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ OleInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 scalar_t__ RPC_E_CHANGED_MODE ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pCoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_OleInitialize_InitCounting(void)
{
    HRESULT hr;
    IUnknown *pUnk;
    REFCLSID rclsid = &CLSID_InternetZoneManager;

    /* 1. OleInitialize fails but OleUninitialize is still called: apartment stays initialized */
    hr = pCoInitializeEx(NULL, COINIT_MULTITHREADED);
    ok(hr == S_OK, "CoInitializeEx(COINIT_MULTITHREADED) failed with error 0x%08x\n", hr);

    hr = OleInitialize(NULL);
    ok(hr == RPC_E_CHANGED_MODE, "OleInitialize should have returned 0x%08x instead of 0x%08x\n", RPC_E_CHANGED_MODE, hr);
    OleUninitialize();

    pUnk = (IUnknown *)0xdeadbeef;
    hr = CoCreateInstance(rclsid, NULL, 0x17, &IID_IUnknown, (void **)&pUnk);
    ok(hr == S_OK, "CoCreateInstance should have returned 0x%08x instead of 0x%08x\n", S_OK, hr);
    if (pUnk) IUnknown_Release(pUnk);

    CoUninitialize();

    /* 2. Extra multiple OleUninitialize: apartment stays initialized until CoUninitialize */
    hr = CoInitialize(NULL);
    ok(hr == S_OK, "CoInitialize() failed with error 0x%08x\n", hr);

    hr = OleInitialize(NULL);
    ok(hr == S_OK, "OleInitialize should have returned 0x%08x instead of 0x%08x\n", S_OK, hr);
    OleUninitialize();
    OleUninitialize();
    OleUninitialize();

    pUnk = (IUnknown *)0xdeadbeef;
    hr = CoCreateInstance(rclsid, NULL, 0x17, &IID_IUnknown, (void **)&pUnk);
    ok(hr == S_OK, "CoCreateInstance should have returned 0x%08x instead of 0x%08x\n", S_OK, hr);
    if (pUnk) IUnknown_Release(pUnk);

    CoUninitialize();

    pUnk = (IUnknown *)0xdeadbeef;
    hr = CoCreateInstance(rclsid, NULL, 0x17, &IID_IUnknown, (void **)&pUnk);
    ok(hr == CO_E_NOTINITIALIZED, "CoCreateInstance should have returned 0x%08x instead of 0x%08x\n", CO_E_NOTINITIALIZED, hr);
    if (pUnk) IUnknown_Release(pUnk);

    /* 3. CoUninitialize does not formally deinit Ole */
    hr = CoInitialize(NULL);
    ok(hr == S_OK, "CoInitialize() failed with error 0x%08x\n", hr);

    hr = OleInitialize(NULL);
    ok(hr == S_OK, "OleInitialize should have returned 0x%08x instead of 0x%08x\n", S_OK, hr);

    CoUninitialize();
    CoUninitialize();

    pUnk = (IUnknown *)0xdeadbeef;
    hr = CoCreateInstance(rclsid, NULL, 0x17, &IID_IUnknown, (void **)&pUnk);
    ok(hr == CO_E_NOTINITIALIZED, "CoCreateInstance should have returned 0x%08x instead of 0x%08x\n", CO_E_NOTINITIALIZED, hr);
      /* COM is not initialized anymore */
    if (pUnk) IUnknown_Release(pUnk);

    hr = OleInitialize(NULL);
    ok(hr == S_FALSE, "OleInitialize should have returned 0x%08x instead of 0x%08x\n", S_FALSE, hr);
      /* ... but native OleInit returns S_FALSE as if Ole is considered initialized */

    OleUninitialize();

}