#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WNDPROC ;
struct TYPE_3__ {int x; int y; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  COMBINED_SEQ_INDEX ; 
 int /*<<< orphan*/ * CreateWindowA (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DispatchMessageA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  GWLP_WNDPROC ; 
 int /*<<< orphan*/  GetCursorPos (TYPE_1__*) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HWND_TOPMOST ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SetCursorPos (int,int) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ *) ; 
 scalar_t__ SetWindowLongPtrA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WC_EDITA ; 
 int WS_CHILD ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 scalar_t__ edit_subclass_proc ; 
 int /*<<< orphan*/  flush_sequences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  killfocus_combined_seq ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sequences ; 
 int /*<<< orphan*/  setfocus_combined_seq ; 

__attribute__((used)) static void test_change_focus(void)
{
    HWND hwnd, parent_wnd;
    WNDPROC oldproc;
    MSG msg;
    POINT orig_pos;

    GetCursorPos(&orig_pos);

    parent_wnd = CreateWindowA("ParentWnd", "", WS_OVERLAPPEDWINDOW,
            0, 0, 200, 200, NULL, NULL, GetModuleHandleA(NULL), NULL);
    ok(parent_wnd != NULL, "Failed to create control parent.\n");
    SetWindowPos(parent_wnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
    ShowWindow(parent_wnd, SW_SHOW);

    hwnd = CreateWindowExA(0, WC_EDITA, "Test", WS_CHILD | WS_VISIBLE, 0, 0, 100, 100,
            parent_wnd, (HMENU)1, GetModuleHandleA(NULL), NULL);
    ok(hwnd != NULL, "Failed to create Edit control.\n");

    oldproc = (WNDPROC)SetWindowLongPtrA(hwnd, GWLP_WNDPROC, (LONG_PTR)edit_subclass_proc);
    SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)oldproc);

    SetCursorPos(400, 400);

    SetFocus(parent_wnd);
    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    SetFocus(hwnd);
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) DispatchMessageA(&msg);
    ok_sequence(sequences, COMBINED_SEQ_INDEX, setfocus_combined_seq, "Set focus", TRUE);

    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    SetFocus(parent_wnd);
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) DispatchMessageA(&msg);
    ok_sequence(sequences, COMBINED_SEQ_INDEX, killfocus_combined_seq, "Kill focus", TRUE);

    SetCursorPos(orig_pos.x, orig_pos.y);

    DestroyWindow(hwnd);
}