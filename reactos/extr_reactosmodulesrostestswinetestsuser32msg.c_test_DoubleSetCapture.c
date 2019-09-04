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
 int /*<<< orphan*/  DoubleSetCaptureSeq ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SetCapture (scalar_t__) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  flush_events () ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_DoubleSetCapture(void)
{
    HWND hwnd;

    hwnd = CreateWindowExA(0, "TestWindowClass", "Test DoubleSetCapture",
                           WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                           100, 100, 200, 200, 0, 0, 0, NULL);
    ok (hwnd != 0, "Failed to create overlapped window\n");

    ShowWindow( hwnd, SW_SHOW );
    UpdateWindow( hwnd );
    flush_events();
    flush_sequence();

    SetCapture( hwnd );
    SetCapture( hwnd );
    ok_sequence(DoubleSetCaptureSeq, "SetCapture( hwnd ) twice", FALSE);

    DestroyWindow(hwnd);
}