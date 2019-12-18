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
typedef  int /*<<< orphan*/  HRGN ;

/* Variables and functions */
 int /*<<< orphan*/  CreateRectRgn (int,int,int,int) ; 
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SetWindowRgn (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  WmSetWindowRgn ; 
 int /*<<< orphan*/  WmSetWindowRgn_clear ; 
 int /*<<< orphan*/  WmSetWindowRgn_no_redraw ; 
 int /*<<< orphan*/  flush_events () ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SetWindowRgn(void)
{
    HRGN hrgn;
    HWND hwnd = CreateWindowExA(0, "TestWindowClass", "Test overlapped", WS_OVERLAPPEDWINDOW,
                                100, 100, 200, 200, 0, 0, 0, NULL);
    ok( hwnd != 0, "Failed to create overlapped window\n" );

    ShowWindow( hwnd, SW_SHOW );
    UpdateWindow( hwnd );
    flush_events();
    flush_sequence();

    trace("testing SetWindowRgn\n");
    hrgn = CreateRectRgn( 0, 0, 150, 150 );
    SetWindowRgn( hwnd, hrgn, TRUE );
    ok_sequence( WmSetWindowRgn, "WmSetWindowRgn", FALSE );

    hrgn = CreateRectRgn( 30, 30, 160, 160 );
    SetWindowRgn( hwnd, hrgn, FALSE );
    ok_sequence( WmSetWindowRgn_no_redraw, "WmSetWindowRgn_no_redraw", FALSE );

    hrgn = CreateRectRgn( 0, 0, 180, 180 );
    SetWindowRgn( hwnd, hrgn, TRUE );
    ok_sequence( WmSetWindowRgn, "WmSetWindowRgn2", FALSE );

    SetWindowRgn( hwnd, 0, TRUE );
    ok_sequence( WmSetWindowRgn_clear, "WmSetWindowRgn_clear", FALSE );

    DestroyWindow( hwnd );
}