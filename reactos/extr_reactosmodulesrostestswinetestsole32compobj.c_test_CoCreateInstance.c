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
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  APTTYPEQUALIFIER_NONE ; 
 int /*<<< orphan*/  APTTYPE_CURRENT ; 
 int /*<<< orphan*/  CLSCTX_INPROC_HANDLER ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSCTX_REMOTE_SERVER ; 
 int /*<<< orphan*/  CLSID_InternetZoneManager ; 
 int /*<<< orphan*/  CLSID_non_existent ; 
 int /*<<< orphan*/ * CO_E_NOTINITIALIZED ; 
 int /*<<< orphan*/ * CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 int /*<<< orphan*/ * REGDB_E_CLASSNOTREG ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_apt_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_CoCreateInstance(void)
{
    HRESULT hr;
    IUnknown *pUnk;
    REFCLSID rclsid = &CLSID_InternetZoneManager;

    pUnk = (IUnknown *)0xdeadbeef;
    hr = CoCreateInstance(rclsid, NULL, CLSCTX_INPROC_SERVER, &IID_IUnknown, (void **)&pUnk);
    ok(hr == CO_E_NOTINITIALIZED, "CoCreateInstance should have returned CO_E_NOTINITIALIZED instead of 0x%08x\n", hr);
    ok(pUnk == NULL, "CoCreateInstance should have changed the passed in pointer to NULL, instead of %p\n", pUnk);

    OleInitialize(NULL);

    /* test errors returned for non-registered clsids */
    hr = CoCreateInstance(&CLSID_non_existent, NULL, CLSCTX_INPROC_SERVER, &IID_IUnknown, (void **)&pUnk);
    ok(hr == REGDB_E_CLASSNOTREG, "CoCreateInstance for non-registered inproc server should have returned REGDB_E_CLASSNOTREG instead of 0x%08x\n", hr);
    hr = CoCreateInstance(&CLSID_non_existent, NULL, CLSCTX_INPROC_HANDLER, &IID_IUnknown, (void **)&pUnk);
    ok(hr == REGDB_E_CLASSNOTREG, "CoCreateInstance for non-registered inproc handler should have returned REGDB_E_CLASSNOTREG instead of 0x%08x\n", hr);
    hr = CoCreateInstance(&CLSID_non_existent, NULL, CLSCTX_LOCAL_SERVER, &IID_IUnknown, (void **)&pUnk);
    ok(hr == REGDB_E_CLASSNOTREG, "CoCreateInstance for non-registered local server should have returned REGDB_E_CLASSNOTREG instead of 0x%08x\n", hr);
    hr = CoCreateInstance(&CLSID_non_existent, NULL, CLSCTX_REMOTE_SERVER, &IID_IUnknown, (void **)&pUnk);
    ok(hr == REGDB_E_CLASSNOTREG, "CoCreateInstance for non-registered remote server should have returned REGDB_E_CLASSNOTREG instead of 0x%08x\n", hr);

    hr = CoCreateInstance(rclsid, NULL, CLSCTX_INPROC_SERVER, &IID_IUnknown, (void **)&pUnk);
    if(hr == REGDB_E_CLASSNOTREG)
    {
        skip("IE not installed so can't test CoCreateInstance\n");
        OleUninitialize();
        return;
    }

    ok_ole_success(hr, "CoCreateInstance");
    if(pUnk) IUnknown_Release(pUnk);
    OleUninitialize();

    hr = CoCreateInstance(rclsid, NULL, CLSCTX_INPROC_SERVER, &IID_IUnknown, (void **)&pUnk);
    ok(hr == CO_E_NOTINITIALIZED, "CoCreateInstance should have returned CO_E_NOTINITIALIZED instead of 0x%08x\n", hr);

    test_apt_type(APTTYPE_CURRENT, APTTYPEQUALIFIER_NONE);
}