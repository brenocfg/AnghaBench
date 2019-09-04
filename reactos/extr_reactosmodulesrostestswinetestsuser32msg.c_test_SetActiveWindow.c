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
typedef  scalar_t__ HWND ;

/* Variables and functions */
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SW_HIDE ; 
 scalar_t__ SetActiveWindow (scalar_t__) ; 
 int /*<<< orphan*/  SetActiveWindowSeq0 ; 
 int /*<<< orphan*/  SetActiveWindowSeq1 ; 
 int /*<<< orphan*/  SetActiveWindowSeq2 ; 
 int /*<<< orphan*/  SetActiveWindowSeq3 ; 
 int /*<<< orphan*/  SetActiveWindowSeq4 ; 
 int /*<<< orphan*/  SetForegroundWindow (scalar_t__) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_POPUP ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SetActiveWindow(void)
{
    HWND hwnd, popup, ret;

    hwnd = CreateWindowExA(0, "TestWindowClass", "Test SetActiveWindow",
                           WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                           100, 100, 200, 200, 0, 0, 0, NULL);

    popup = CreateWindowExA(0, "TestWindowClass", "Test SetActiveWindow",
                           WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_POPUP,
                           100, 100, 200, 200, hwnd, 0, 0, NULL);

    ok(hwnd != 0, "Failed to create overlapped window\n");
    ok(popup != 0, "Failed to create popup window\n");
    SetForegroundWindow( popup );
    flush_sequence();

    trace("SetActiveWindow(0)\n");
    ret = SetActiveWindow(0);
    ok( ret == popup, "Failed to SetActiveWindow(0)\n");
    ok_sequence(SetActiveWindowSeq0, "SetActiveWindow(0)", FALSE);
    flush_sequence();

    trace("SetActiveWindow(hwnd), hwnd visible\n");
    ret = SetActiveWindow(hwnd);
    if (ret == hwnd) ok_sequence(SetActiveWindowSeq1, "SetActiveWindow(hwnd), hwnd visible", TRUE);
    flush_sequence();

    trace("SetActiveWindow(popup), hwnd visible, popup visible\n");
    ret = SetActiveWindow(popup);
    ok( ret == hwnd, "Failed to SetActiveWindow(popup), popup visible\n");
    ok_sequence(SetActiveWindowSeq2, "SetActiveWindow(popup), hwnd visible, popup visible", FALSE);
    flush_sequence();

    ShowWindow(hwnd, SW_HIDE);
    ShowWindow(popup, SW_HIDE);
    flush_sequence();

    trace("SetActiveWindow(hwnd), hwnd not visible\n");
    ret = SetActiveWindow(hwnd);
    ok( ret == NULL, "SetActiveWindow(hwnd), hwnd not visible, previous is %p\n", ret );
    ok_sequence(SetActiveWindowSeq3, "SetActiveWindow(hwnd), hwnd not visible", TRUE);
    flush_sequence();

    trace("SetActiveWindow(popup), hwnd not visible, popup not visible\n");
    ret = SetActiveWindow(popup);
    ok( ret == hwnd, "Failed to SetActiveWindow(popup)\n");
    ok_sequence(SetActiveWindowSeq4, "SetActiveWindow(popup), hwnd not visible, popup not visible", TRUE);
    flush_sequence();

    trace("done\n");

    DestroyWindow(hwnd);
}