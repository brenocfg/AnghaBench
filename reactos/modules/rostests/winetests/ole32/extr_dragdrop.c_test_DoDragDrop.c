#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ set_param; } ;
struct TYPE_6__ {scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__**) ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DataObject ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ DoDragDrop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  DoDragDrop_effect_out ; 
 int /*<<< orphan*/  DoDragDrop_ret ; 
 int /*<<< orphan*/  DropSource ; 
 int /*<<< orphan*/  DropTarget ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ OleInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 scalar_t__ RegisterDragDrop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SW_SHOW ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetCursorPos (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WS_EX_TOPMOST ; 
 TYPE_2__** call_lists ; 
 TYPE_2__* call_ptr ; 
 int /*<<< orphan*/  check_expect (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_DoDragDrop(void)
{
    DWORD effect;
    HRESULT hr;
    HWND hwnd;
    RECT rect;
    int seq;

    hwnd = CreateWindowExA(WS_EX_TOPMOST, "WineOleTestClass", "Test", 0,
        CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, NULL,
        NULL, NULL, NULL);
    ok(IsWindow(hwnd), "failed to create window\n");

    hr = OleInitialize(NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = RegisterDragDrop(hwnd, &DropTarget);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    /* incomplete arguments set */
    hr = DoDragDrop(NULL, NULL, 0, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = DoDragDrop(NULL, &DropSource, 0, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = DoDragDrop(&DataObject, NULL, 0, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = DoDragDrop(NULL, NULL, 0, &effect);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = DoDragDrop(&DataObject, &DropSource, 0, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = DoDragDrop(NULL, &DropSource, 0, &effect);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = DoDragDrop(&DataObject, NULL, 0, &effect);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    ShowWindow(hwnd, SW_SHOW);
    GetWindowRect(hwnd, &rect);
    ok(SetCursorPos(rect.left+50, rect.top+50), "SetCursorPos failed\n");

    for (seq = 0; seq < ARRAY_SIZE(call_lists); seq++)
    {
        DWORD effect_in;
        trace("%d\n", seq);
        call_ptr = call_lists[seq];
        effect_in = call_ptr->set_param;
        call_ptr++;

        hr = DoDragDrop(&DataObject, &DropSource, effect_in, &effect);
        check_expect(DoDragDrop_ret, hr, NULL);
        check_expect(DoDragDrop_effect_out, effect, NULL);
    }

    OleUninitialize();

    DestroyWindow(hwnd);
}