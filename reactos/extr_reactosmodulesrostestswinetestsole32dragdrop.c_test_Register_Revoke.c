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
typedef  int /*<<< orphan*/ * HWND ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int CO_E_NOTINITIALIZED ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/ * CreateWindowA (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DRAGDROP_E_ALREADYREGISTERED ; 
 int DRAGDROP_E_INVALIDHWND ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DropTarget ; 
 int E_INVALIDARG ; 
 int E_OUTOFMEMORY ; 
 int /*<<< orphan*/ * GetPropA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OleInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 int RegisterDragDrop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RevokeDragDrop (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 scalar_t__ broken (int) ; 
 int droptarget_refs ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ole_success (int,char*) ; 

__attribute__((used)) static void test_Register_Revoke(void)
{
    HANDLE prop;
    HRESULT hr;
    HWND hwnd;

    hwnd = CreateWindowA("WineOleTestClass", "Test", 0,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
        NULL, NULL, NULL);

    hr = RegisterDragDrop(hwnd, &DropTarget);
    ok(hr == E_OUTOFMEMORY ||
        broken(hr == CO_E_NOTINITIALIZED), /* NT4 */
        "RegisterDragDrop without OLE initialized should have returned E_OUTOFMEMORY instead of 0x%08x\n", hr);

    OleInitialize(NULL);

    hr = RegisterDragDrop(hwnd, NULL);
    ok(hr == E_INVALIDARG, "RegisterDragDrop with NULL IDropTarget * should return E_INVALIDARG instead of 0x%08x\n", hr);

    hr = RegisterDragDrop(NULL, &DropTarget);
    ok(hr == DRAGDROP_E_INVALIDHWND, "RegisterDragDrop with NULL hwnd should return DRAGDROP_E_INVALIDHWND instead of 0x%08x\n", hr);

    hr = RegisterDragDrop((HWND)0xdeadbeef, &DropTarget);
    ok(hr == DRAGDROP_E_INVALIDHWND, "RegisterDragDrop with garbage hwnd should return DRAGDROP_E_INVALIDHWND instead of 0x%08x\n", hr);

    ok(droptarget_refs == 0, "DropTarget refs should be zero not %d\n", droptarget_refs);
    hr = RegisterDragDrop(hwnd, &DropTarget);
    ok_ole_success(hr, "RegisterDragDrop");
    ok(droptarget_refs >= 1, "DropTarget refs should be at least one\n");

    prop = GetPropA(hwnd, "OleDropTargetInterface");
    ok(prop == &DropTarget, "expected IDropTarget pointer %p, got %p\n", &DropTarget, prop);

    hr = RegisterDragDrop(hwnd, &DropTarget);
    ok(hr == DRAGDROP_E_ALREADYREGISTERED, "RegisterDragDrop with already registered hwnd should return DRAGDROP_E_ALREADYREGISTERED instead of 0x%08x\n", hr);

    ok(droptarget_refs >= 1, "DropTarget refs should be at least one\n");
    OleUninitialize();

    /* Win 8 releases the ref in OleUninitialize() */
    if (droptarget_refs >= 1)
    {
        hr = RevokeDragDrop(hwnd);
        ok_ole_success(hr, "RevokeDragDrop");
        ok(droptarget_refs == 0 ||
           broken(droptarget_refs == 1), /* NT4 */
           "DropTarget refs should be zero not %d\n", droptarget_refs);
    }

    hr = RevokeDragDrop(NULL);
    ok(hr == DRAGDROP_E_INVALIDHWND, "RevokeDragDrop with NULL hwnd should return DRAGDROP_E_INVALIDHWND instead of 0x%08x\n", hr);

    DestroyWindow(hwnd);

    /* try to revoke with already destroyed window */
    OleInitialize(NULL);

    hwnd = CreateWindowA("WineOleTestClass", "Test", 0,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
        NULL, NULL, NULL);

    hr = RegisterDragDrop(hwnd, &DropTarget);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    DestroyWindow(hwnd);

    hr = RevokeDragDrop(hwnd);
    ok(hr == DRAGDROP_E_INVALIDHWND, "got 0x%08x\n", hr);

    OleUninitialize();
}