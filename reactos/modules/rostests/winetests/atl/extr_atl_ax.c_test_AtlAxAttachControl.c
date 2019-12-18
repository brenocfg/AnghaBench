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
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WebBrowser ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/ * CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * CreateWindowA (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 scalar_t__ FAILED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * S_FALSE ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pAtlAxAttachControl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_AtlAxAttachControl(void)
{
    HWND hwnd = CreateWindowA("WineAtlTestClass", "Wine ATL Test Window", 0,
                              CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                              CW_USEDEFAULT, NULL, NULL, NULL, NULL);
    HRESULT hr;
    IUnknown *pObj, *pContainer;

    hr = pAtlAxAttachControl(NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "Expected AtlAxAttachControl to return E_INVALIDARG, got 0x%08x\n", hr);

    pContainer = (IUnknown *)0xdeadbeef;
    hr = pAtlAxAttachControl(NULL, NULL, &pContainer);
    ok(hr == E_INVALIDARG, "Expected AtlAxAttachControl to return E_INVALIDARG, got 0x%08x\n", hr);
    ok(pContainer == (IUnknown *)0xdeadbeef,
       "Expected the output container pointer to be untouched, got %p\n", pContainer);

    hr = pAtlAxAttachControl(NULL, hwnd, NULL);
    ok(hr == E_INVALIDARG, "Expected AtlAxAttachControl to return E_INVALIDARG, got 0x%08x\n", hr);

    hr = CoCreateInstance(&CLSID_WebBrowser, NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER,
                          &IID_IOleObject, (void **)&pObj);
    ok(hr == S_OK, "Expected CoCreateInstance to return S_OK, got 0x%08x\n", hr);

    if (FAILED(hr))
    {
        skip("Couldn't obtain a test IOleObject instance\n");
        return;
    }

    hr = pAtlAxAttachControl(pObj, NULL, NULL);
    ok(hr == S_FALSE, "Expected AtlAxAttachControl to return S_FALSE, got 0x%08x\n", hr);

    pContainer = NULL;
    hr = pAtlAxAttachControl(pObj, NULL, &pContainer);
    ok(hr == S_FALSE, "Expected AtlAxAttachControl to return S_FALSE, got 0x%08x\n", hr);
    ok(pContainer != NULL, "got %p\n", pContainer);
    IUnknown_Release(pContainer);

    hr = pAtlAxAttachControl(pObj, hwnd, NULL);
    ok(hr == S_OK, "Expected AtlAxAttachControl to return S_OK, got 0x%08x\n", hr);

    IUnknown_Release(pObj);

    DestroyWindow(hwnd);
}