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
struct TYPE_3__ {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RECT ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int SW_ERASE ; 
 int SW_INVALIDATE ; 
 int SW_SCROLLCHILDREN ; 
 int /*<<< orphan*/  ScrollWindow (scalar_t__,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScrollWindowEx (scalar_t__,int,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ScrollWindowPaint1 ; 
 int /*<<< orphan*/  ScrollWindowPaint2 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 int WS_CAPTION ; 
 int WS_CHILD ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  WmEmptySeq ; 
 int /*<<< orphan*/  flush_events () ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_scrollwindowex(void)
{
    HWND hwnd, hchild;
    RECT rect={0,0,130,130};

    hwnd = CreateWindowExA(0, "TestWindowClass", "Test Scroll",
            WS_VISIBLE|WS_OVERLAPPEDWINDOW,
            100, 100, 200, 200, 0, 0, 0, NULL);
    ok (hwnd != 0, "Failed to create overlapped window\n");
    hchild = CreateWindowExA(0, "TestWindowClass", "Test child", 
            WS_VISIBLE|WS_CAPTION|WS_CHILD,
            10, 10, 150, 150, hwnd, 0, 0, NULL);
    ok (hchild != 0, "Failed to create child\n");
    UpdateWindow(hwnd);
    flush_events();
    flush_sequence();

    /* scroll without the child window */
    trace("start scroll\n");
    ScrollWindowEx( hwnd, 10, 10, &rect, NULL, NULL, NULL,
            SW_ERASE|SW_INVALIDATE);
    ok_sequence(WmEmptySeq, "ScrollWindowEx", FALSE);
    trace("end scroll\n");
    flush_sequence();
    flush_events();
    ok_sequence(ScrollWindowPaint1, "ScrollWindowEx", FALSE);
    flush_events();
    flush_sequence();

    /* Now without the SW_ERASE flag */
    trace("start scroll\n");
    ScrollWindowEx( hwnd, 10, 10, &rect, NULL, NULL, NULL, SW_INVALIDATE);
    ok_sequence(WmEmptySeq, "ScrollWindowEx", FALSE);
    trace("end scroll\n");
    flush_sequence();
    flush_events();
    ok_sequence(ScrollWindowPaint2, "ScrollWindowEx", FALSE);
    flush_events();
    flush_sequence();

    /* now scroll the child window as well */
    trace("start scroll\n");
    ScrollWindowEx( hwnd, 10, 10, &rect, NULL, NULL, NULL,
            SW_SCROLLCHILDREN|SW_ERASE|SW_INVALIDATE);
    /* wine sends WM_POSCHANGING, WM_POSCHANGED messages */
    /* windows sometimes a WM_MOVE */
    ok_sequence(WmEmptySeq, "ScrollWindowEx", TRUE);
    trace("end scroll\n");
    flush_sequence();
    flush_events();
    ok_sequence(ScrollWindowPaint1, "ScrollWindowEx", FALSE);
    flush_events();
    flush_sequence();

    /* now scroll with ScrollWindow() */
    trace("start scroll with ScrollWindow\n");
    ScrollWindow( hwnd, 5, 5, NULL, NULL);
    trace("end scroll\n");
    flush_sequence();
    flush_events();
    ok_sequence(ScrollWindowPaint1, "ScrollWindow", FALSE);

    ok(DestroyWindow(hchild), "failed to destroy window\n");
    ok(DestroyWindow(hwnd), "failed to destroy window\n");
    flush_sequence();
}