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
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetDesktopWindow () ; 
 int /*<<< orphan*/  SetForegroundWindow (scalar_t__) ; 
 int /*<<< orphan*/  SetForegroundWindowSeq ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  WmEmptySeq ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SetForegroundWindow(void)
{
    HWND hwnd;

    hwnd = CreateWindowExA(0, "TestWindowClass", "Test SetForegroundWindow",
                           WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                           100, 100, 200, 200, 0, 0, 0, NULL);
    ok (hwnd != 0, "Failed to create overlapped window\n");
    SetForegroundWindow( hwnd );
    flush_sequence();

    trace("SetForegroundWindow( 0 )\n");
    SetForegroundWindow( 0 );
    ok_sequence(WmEmptySeq, "SetForegroundWindow( 0 ) away from foreground top level window", FALSE);
    trace("SetForegroundWindow( GetDesktopWindow() )\n");
    SetForegroundWindow( GetDesktopWindow() );
    ok_sequence(SetForegroundWindowSeq, "SetForegroundWindow( desktop ) away from "
                                        "foreground top level window", FALSE);
    trace("done\n");

    DestroyWindow(hwnd);
}