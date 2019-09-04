#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ message; } ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_6__ {int left; int right; int top; int bottom; } ;
typedef  int SHORT ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HACCEL ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DestroyAcceleratorTable (scalar_t__) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  GetCursorPos (TYPE_2__*) ; 
 int GetFocus () ; 
 int GetKeyState (char) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEYEVENTF_KEYUP ; 
 scalar_t__ LoadAcceleratorsA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEA (int) ; 
 int /*<<< orphan*/  MOUSEEVENTF_LEFTDOWN ; 
 int /*<<< orphan*/  MOUSEEVENTF_LEFTUP ; 
 int /*<<< orphan*/  MapWindowPoints (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetActiveWindow (scalar_t__) ; 
 int /*<<< orphan*/  SetCursorPos (int,int) ; 
 int /*<<< orphan*/  SetFocus (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 char VK_APPS ; 
 char VK_CAPITAL ; 
 char VK_CONTROL ; 
 char VK_ESCAPE ; 
 char VK_F1 ; 
 char VK_F10 ; 
 char VK_MENU ; 
 char VK_SHIFT ; 
 scalar_t__ WM_LBUTTONDOWN ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  WmAltPressRelease ; 
 int /*<<< orphan*/  WmAltVkN ; 
 int /*<<< orphan*/  WmAltVkN_2 ; 
 int /*<<< orphan*/  WmCtrlAltShiftVkN ; 
 int /*<<< orphan*/  WmCtrlAltVkN ; 
 int /*<<< orphan*/  WmCtrlShiftVkN ; 
 int /*<<< orphan*/  WmCtrlVkN ; 
 int /*<<< orphan*/  WmCtrlVkN_2 ; 
 int /*<<< orphan*/  WmF1Seq ; 
 int /*<<< orphan*/  WmShiftF10Seq ; 
 int /*<<< orphan*/  WmShiftMouseButton ; 
 int /*<<< orphan*/  WmShiftVkN ; 
 int /*<<< orphan*/  WmVkAppsSeq ; 
 int /*<<< orphan*/  WmVkF10Seq ; 
 int /*<<< orphan*/  WmVkN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  flush_events () ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  keybd_event (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mouse_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pump_msg_loop (scalar_t__,scalar_t__) ; 
 TYPE_3__* sequence ; 
 int sequence_cnt ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_accelerators(void)
{
    RECT rc;
    POINT pt;
    SHORT state;
    HACCEL hAccel;
    HWND hwnd = CreateWindowExA(0, "TestWindowClass", NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                100, 100, 200, 200, 0, 0, 0, NULL);
    BOOL ret;

    assert(hwnd != 0);
    UpdateWindow(hwnd);
    flush_events();
    flush_sequence();

    SetFocus(hwnd);
    ok(GetFocus() == hwnd, "wrong focus window %p\n", GetFocus());

    state = GetKeyState(VK_SHIFT);
    ok(!(state & 0x8000), "wrong Shift state %04x\n", state);
    state = GetKeyState(VK_CAPITAL);
    ok(state == 0, "wrong CapsLock state %04x\n", state);

    hAccel = LoadAcceleratorsA(GetModuleHandleA(NULL), MAKEINTRESOURCEA(1));
    assert(hAccel != 0);

    flush_events();
    pump_msg_loop(hwnd, 0);
    flush_sequence();

    trace("testing VK_N press/release\n");
    flush_sequence();
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    if (!sequence_cnt)  /* we didn't get any message */
    {
        skip( "queuing key events not supported\n" );
        goto done;
    }
    ok_sequence(WmVkN, "VK_N press/release", FALSE);

    trace("testing Shift+VK_N press/release\n");
    flush_sequence();
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmShiftVkN, "Shift+VK_N press/release", FALSE);

    trace("testing Ctrl+VK_N press/release\n");
    flush_sequence();
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmCtrlVkN, "Ctrl+VK_N press/release", FALSE);

    trace("testing Alt+VK_N press/release\n");
    flush_sequence();
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmAltVkN, "Alt+VK_N press/release", FALSE);

    trace("testing Ctrl+Alt+VK_N press/release 1\n");
    flush_sequence();
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmCtrlAltVkN, "Ctrl+Alt+VK_N press/release 1", FALSE);

    ret = DestroyAcceleratorTable(hAccel);
    ok( ret, "DestroyAcceleratorTable error %d\n", GetLastError());

    hAccel = LoadAcceleratorsA(GetModuleHandleA(NULL), MAKEINTRESOURCEA(2));
    assert(hAccel != 0);

    trace("testing VK_N press/release\n");
    flush_sequence();
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmVkN, "VK_N press/release", FALSE);

    trace("testing Shift+VK_N press/release\n");
    flush_sequence();
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmShiftVkN, "Shift+VK_N press/release", FALSE);

    trace("testing Ctrl+VK_N press/release 2\n");
    flush_sequence();
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmCtrlVkN_2, "Ctrl+VK_N press/release 2", FALSE);

    trace("testing Alt+VK_N press/release 2\n");
    flush_sequence();
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmAltVkN_2, "Alt+VK_N press/release 2", FALSE);

    trace("testing Ctrl+Alt+VK_N press/release 2\n");
    flush_sequence();
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmCtrlAltVkN, "Ctrl+Alt+VK_N press/release 2", FALSE);

    trace("testing Ctrl+Shift+VK_N press/release\n");
    flush_sequence();
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmCtrlShiftVkN, "Ctrl+Shift+VK_N press/release", FALSE);

    trace("testing Ctrl+Alt+Shift+VK_N press/release\n");
    flush_sequence();
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event('N', 0, 0, 0);
    keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, hAccel);
    ok_sequence(WmCtrlAltShiftVkN, "Ctrl+Alt+Shift+VK_N press/release", FALSE);

    ret = DestroyAcceleratorTable(hAccel);
    ok( ret, "DestroyAcceleratorTable error %d\n", GetLastError());
    hAccel = 0;

    trace("testing Alt press/release\n");
    flush_sequence();
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, 0);
    /* this test doesn't pass in Wine for managed windows */
    ok_sequence(WmAltPressRelease, "Alt press/release", TRUE);

    trace("testing VK_F1 press/release\n");
    keybd_event(VK_F1, 0, 0, 0);
    keybd_event(VK_F1, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, 0);
    ok_sequence(WmF1Seq, "F1 press/release", FALSE);

    trace("testing VK_APPS press/release\n");
    keybd_event(VK_APPS, 0, 0, 0);
    keybd_event(VK_APPS, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, 0);
    ok_sequence(WmVkAppsSeq, "VK_APPS press/release", FALSE);

    trace("testing VK_F10 press/release\n");
    keybd_event(VK_F10, 0, 0, 0);
    keybd_event(VK_F10, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_F10, 0, 0, 0);
    keybd_event(VK_F10, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, 0);
    ok_sequence(WmVkF10Seq, "VK_F10 press/release", TRUE);

    trace("testing SHIFT+F10 press/release\n");
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event(VK_F10, 0, 0, 0);
    keybd_event(VK_F10, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_ESCAPE, 0, 0, 0);
    keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
    pump_msg_loop(hwnd, 0);
    ok_sequence(WmShiftF10Seq, "SHIFT+F10 press/release", TRUE);

    trace("testing Shift+MouseButton press/release\n");
    /* first, move mouse pointer inside of the window client area */
    GetClientRect(hwnd, &rc);
    MapWindowPoints(hwnd, 0, (LPPOINT)&rc, 2);
    rc.left += (rc.right - rc.left)/2;
    rc.top += (rc.bottom - rc.top)/2;
    SetCursorPos(rc.left, rc.top);
    SetActiveWindow(hwnd);

    flush_events();
    flush_sequence();
    GetCursorPos(&pt);
    if (pt.x == rc.left && pt.y == rc.top)
    {
        int i;
        keybd_event(VK_SHIFT, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
        pump_msg_loop(hwnd, 0);
        for (i = 0; i < sequence_cnt; i++) if (sequence[i].message == WM_LBUTTONDOWN) break;
        if (i < sequence_cnt)
            ok_sequence(WmShiftMouseButton, "Shift+MouseButton press/release", FALSE);
        else
            skip( "Shift+MouseButton event didn't get to the window\n" );
    }

done:
    if (hAccel) DestroyAcceleratorTable(hAccel);
    DestroyWindow(hwnd);
}