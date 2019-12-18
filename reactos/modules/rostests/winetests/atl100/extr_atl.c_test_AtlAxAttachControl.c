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
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int HRESULT ;

/* Variables and functions */
 int AtlAxAttachControl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WebBrowser ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int E_INVALIDARG ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int GetWindowLongW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  SetWindowLongW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * create_container_window () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_AtlAxAttachControl(void)
{
    HWND hwnd;
    HRESULT hr;
    IUnknown *control, *container;
    LONG val;

    hr = AtlAxAttachControl(NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "Expected AtlAxAttachControl to return E_INVALIDARG, got 0x%08x\n", hr);

    container = (IUnknown *)0xdeadbeef;
    hr = AtlAxAttachControl(NULL, NULL, &container);
    ok(hr == E_INVALIDARG, "Expected AtlAxAttachControl to return E_INVALIDARG, got 0x%08x\n", hr);
    ok(container == (IUnknown *)0xdeadbeef,
       "Expected the output container pointer to be untouched, got %p\n", container);

    hwnd = create_container_window();
    hr = AtlAxAttachControl(NULL, hwnd, NULL);
    ok(hr == E_INVALIDARG, "Expected AtlAxAttachControl to return E_INVALIDARG, got 0x%08x\n", hr);
    DestroyWindow(hwnd);

    hwnd = create_container_window();
    container = (IUnknown *)0xdeadbeef;
    hr = AtlAxAttachControl(NULL, hwnd, &container);
    ok(hr == E_INVALIDARG, "Expected AtlAxAttachControl to return E_INVALIDARG, got 0x%08x\n", hr);
    ok(container == (IUnknown *)0xdeadbeef, "returned %p\n", container);
    DestroyWindow(hwnd);

    hr = CoCreateInstance(&CLSID_WebBrowser, NULL, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER,
                          &IID_IOleObject, (void **)&control);
    ok(hr == S_OK, "Expected CoCreateInstance to return S_OK, got 0x%08x\n", hr);

    if (FAILED(hr))
    {
        skip("Couldn't obtain a test IOleObject instance\n");
        return;
    }

    hr = AtlAxAttachControl(control, NULL, NULL);
    ok(hr == S_FALSE, "Expected AtlAxAttachControl to return S_FALSE, got 0x%08x\n", hr);

    container = NULL;
    hr = AtlAxAttachControl(control, NULL, &container);
    ok(hr == S_FALSE, "Expected AtlAxAttachControl to return S_FALSE, got 0x%08x\n", hr);
    ok(container != NULL, "got %p\n", container);
    IUnknown_Release(container);

    hwnd = create_container_window();
    SetWindowLongW(hwnd, GWLP_USERDATA, 0xdeadbeef);
    hr = AtlAxAttachControl(control, hwnd, NULL);
    ok(hr == S_OK, "Expected AtlAxAttachControl to return S_OK, got 0x%08x\n", hr);
    val = GetWindowLongW(hwnd, GWLP_USERDATA);
    ok(val == 0xdeadbeef, "returned %08x\n", val);
    DestroyWindow(hwnd);

    hwnd = create_container_window();
    SetWindowLongW(hwnd, GWLP_USERDATA, 0xdeadbeef);
    container = NULL;
    hr = AtlAxAttachControl(control, hwnd, &container);
    ok(hr == S_OK, "Expected AtlAxAttachControl to return S_OK, got 0x%08x\n", hr);
    ok(container != NULL, "Expected not NULL!\n");
    IUnknown_Release(container);
    val = GetWindowLongW(hwnd, GWLP_USERDATA);
    ok(val == 0xdeadbeef, "Expected unchanged, returned %08x\n", val);
    DestroyWindow(hwnd);

    IUnknown_Release(control);
}