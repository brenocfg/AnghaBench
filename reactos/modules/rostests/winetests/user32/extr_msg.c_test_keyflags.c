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
typedef  int SHORT ;
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DispatchMessageA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetAsyncKeyState (int) ; 
 int GetKeyState (int) ; 
 int /*<<< orphan*/  GetKeyboardState (int*) ; 
 int /*<<< orphan*/  KEYEVENTF_KEYUP ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetKeyboardState (int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_KEYFIRST ; 
 int /*<<< orphan*/  WM_KEYLAST ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  WmKeyPressNormal ; 
 int /*<<< orphan*/  WmKeyPressRepeat ; 
 int /*<<< orphan*/  WmKeyReleaseNormal ; 
 int /*<<< orphan*/  WmKeyReleaseOnly ; 
 int /*<<< orphan*/  flush_events () ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  keybd_event (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_keyflags(void)
{
    HWND test_window;
    SHORT key_state;
    BYTE keyboard_state[256];
    MSG msg;

    test_window = CreateWindowExA(0, "TestWindowClass", NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                           100, 100, 200, 200, 0, 0, 0, NULL);

    flush_events();
    flush_sequence();

    /* keyup without a keydown */
    keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
    while (PeekMessageA(&msg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE))
        DispatchMessageA(&msg);
    ok_sequence(WmKeyReleaseOnly, "key release only", TRUE);

    key_state = GetAsyncKeyState(0x41);
    ok((key_state & 0x8000) == 0, "unexpected key state %x\n", key_state);

    key_state = GetKeyState(0x41);
    ok((key_state & 0x8000) == 0, "unexpected key state %x\n", key_state);

    /* keydown */
    keybd_event(0x41, 0, 0, 0);
    while (PeekMessageA(&msg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE))
        DispatchMessageA(&msg);
    ok_sequence(WmKeyPressNormal, "key press only", FALSE);

    key_state = GetAsyncKeyState(0x41);
    ok((key_state & 0x8000) == 0x8000, "unexpected key state %x\n", key_state);

    key_state = GetKeyState(0x41);
    ok((key_state & 0x8000) == 0x8000, "unexpected key state %x\n", key_state);

    /* keydown repeat */
    keybd_event(0x41, 0, 0, 0);
    while (PeekMessageA(&msg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE))
        DispatchMessageA(&msg);
    ok_sequence(WmKeyPressRepeat, "key press repeat", FALSE);

    key_state = GetAsyncKeyState(0x41);
    ok((key_state & 0x8000) == 0x8000, "unexpected key state %x\n", key_state);

    key_state = GetKeyState(0x41);
    ok((key_state & 0x8000) == 0x8000, "unexpected key state %x\n", key_state);

    /* keyup */
    keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
    while (PeekMessageA(&msg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE))
        DispatchMessageA(&msg);
    ok_sequence(WmKeyReleaseNormal, "key release repeat", FALSE);

    key_state = GetAsyncKeyState(0x41);
    ok((key_state & 0x8000) == 0, "unexpected key state %x\n", key_state);

    key_state = GetKeyState(0x41);
    ok((key_state & 0x8000) == 0, "unexpected key state %x\n", key_state);

    /* set the key state in this thread */
    GetKeyboardState(keyboard_state);
    keyboard_state[0x41] = 0x80;
    SetKeyboardState(keyboard_state);

    key_state = GetAsyncKeyState(0x41);
    ok((key_state & 0x8000) == 0, "unexpected key state %x\n", key_state);

    /* keydown */
    keybd_event(0x41, 0, 0, 0);
    while (PeekMessageA(&msg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE))
        DispatchMessageA(&msg);
    ok_sequence(WmKeyPressRepeat, "key press after setkeyboardstate", TRUE);

    key_state = GetAsyncKeyState(0x41);
    ok((key_state & 0x8000) == 0x8000, "unexpected key state %x\n", key_state);

    key_state = GetKeyState(0x41);
    ok((key_state & 0x8000) == 0x8000, "unexpected key state %x\n", key_state);

    /* clear the key state in this thread */
    GetKeyboardState(keyboard_state);
    keyboard_state[0x41] = 0;
    SetKeyboardState(keyboard_state);

    key_state = GetAsyncKeyState(0x41);
    ok((key_state & 0x8000) == 0x8000, "unexpected key state %x\n", key_state);

    /* keyup */
    keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
    while (PeekMessageA(&msg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE))
        DispatchMessageA(&msg);
    ok_sequence(WmKeyReleaseOnly, "key release after setkeyboardstate", TRUE);

    key_state = GetAsyncKeyState(0x41);
    ok((key_state & 0x8000) == 0, "unexpected key state %x\n", key_state);

    key_state = GetKeyState(0x41);
    ok((key_state & 0x8000) == 0, "unexpected key state %x\n", key_state);

    DestroyWindow(test_window);
    flush_sequence();
}