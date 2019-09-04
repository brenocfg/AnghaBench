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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/ * REFCLSID ;
typedef  int /*<<< orphan*/ * LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  APTTYPEQUALIFIER_NONE ; 
 int /*<<< orphan*/  APTTYPE_CURRENT ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_InProcFreeMarshaler ; 
 int /*<<< orphan*/  CLSID_InternetZoneManager ; 
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 int /*<<< orphan*/ * CO_E_NOTINITIALIZED ; 
 int /*<<< orphan*/ * CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RegCreateKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  actctx_manifest ; 
 int /*<<< orphan*/  activate_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pCoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pDeactivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pRegOverridePredefKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pReleaseActCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_apt_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_CoGetClassObject(void)
{
    HRESULT hr;
    HANDLE handle;
    ULONG_PTR cookie;
    IUnknown *pUnk;
    REFCLSID rclsid = &CLSID_InternetZoneManager;
    HKEY hkey;
    LONG res;

    hr = CoGetClassObject(rclsid, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void **)&pUnk);
    ok(hr == CO_E_NOTINITIALIZED, "CoGetClassObject should have returned CO_E_NOTINITIALIZED instead of 0x%08x\n", hr);
    ok(pUnk == NULL, "CoGetClassObject should have changed the passed in pointer to NULL, instead of %p\n", pUnk);

    hr = CoGetClassObject(rclsid, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, NULL);
    ok(hr == E_INVALIDARG ||
       broken(hr == CO_E_NOTINITIALIZED), /* win9x */
       "CoGetClassObject should have returned E_INVALIDARG instead of 0x%08x\n", hr);

    test_apt_type(APTTYPE_CURRENT, APTTYPEQUALIFIER_NONE);

    if (!pRegOverridePredefKey)
    {
        win_skip("RegOverridePredefKey not available\n");
        return;
    }

    pCoInitializeEx(NULL, COINIT_MULTITHREADED);

    hr = CoGetClassObject(rclsid, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void **)&pUnk);
    if (hr == S_OK)
    {
        IUnknown_Release(pUnk);

        res = RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Classes", 0, NULL, 0,
                             KEY_ALL_ACCESS, NULL, &hkey, NULL);
        ok(!res, "RegCreateKeyEx returned %d\n", res);

        res = pRegOverridePredefKey(HKEY_CLASSES_ROOT, hkey);
        ok(!res, "RegOverridePredefKey returned %d\n", res);

        hr = CoGetClassObject(rclsid, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void **)&pUnk);
        ok(hr == S_OK, "CoGetClassObject should have returned S_OK instead of 0x%08x\n", hr);

        res = pRegOverridePredefKey(HKEY_CLASSES_ROOT, NULL);
        ok(!res, "RegOverridePredefKey returned %d\n", res);

        if (hr == S_OK) IUnknown_Release(pUnk);
        RegCloseKey(hkey);
    }

    hr = CoGetClassObject(&CLSID_InProcFreeMarshaler, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void **)&pUnk);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    IUnknown_Release(pUnk);

    /* context redefines FreeMarshaler CLSID */
    if ((handle = activate_context(actctx_manifest, &cookie)))
    {
        hr = CoGetClassObject(&CLSID_InProcFreeMarshaler, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void **)&pUnk);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        IUnknown_Release(pUnk);

        pDeactivateActCtx(0, cookie);
        pReleaseActCtx(handle);
    }

    CoUninitialize();
}