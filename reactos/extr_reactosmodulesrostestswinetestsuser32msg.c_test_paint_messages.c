#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ hwnd; scalar_t__ message; } ;
struct TYPE_17__ {int x; int y; } ;
struct TYPE_16__ {int right; int left; int bottom; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  TYPE_3__ MSG ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  DispatchMessageA (TYPE_3__*) ; 
 int ERROR_INVALID_WINDOW_HANDLE ; 
 int /*<<< orphan*/  EqualRect (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_1__*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetUpdateRect (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUpdateRgn (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetWindowLongA (scalar_t__,int /*<<< orphan*/ ) ; 
 int InvalidateRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindow (scalar_t__) ; 
 int /*<<< orphan*/  MapWindowPoints (scalar_t__,scalar_t__,TYPE_2__*,int) ; 
 int /*<<< orphan*/  MoveWindow (scalar_t__,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULLREGION ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageA (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RDW_ALLCHILDREN ; 
 int RDW_ERASE ; 
 int RDW_ERASENOW ; 
 int RDW_FRAME ; 
 int RDW_INTERNALPAINT ; 
 int RDW_INVALIDATE ; 
 int RDW_NOCHILDREN ; 
 int RDW_NOERASE ; 
 int RDW_NOFRAME ; 
 int RDW_UPDATENOW ; 
 int RDW_VALIDATE ; 
 int /*<<< orphan*/  RGN_DIFF ; 
 int /*<<< orphan*/  RGN_OR ; 
 int /*<<< orphan*/  RedrawWindow (scalar_t__,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int SWP_DEFERERASE ; 
 int SWP_FRAMECHANGED ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  SetRectRgn (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  SetWindowLongA (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 scalar_t__ ValidateRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ValidateRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ WM_PAINT ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_CLIPCHILDREN ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_POPUP ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  WmChildPaintNc ; 
 int /*<<< orphan*/  WmEmptySeq ; 
 int /*<<< orphan*/  WmErase ; 
 int /*<<< orphan*/  WmGetUpdateRect ; 
 int /*<<< orphan*/  WmInvalidateErase ; 
 int /*<<< orphan*/  WmInvalidateErasePaint ; 
 int /*<<< orphan*/  WmInvalidateErasePaint2 ; 
 int /*<<< orphan*/  WmInvalidateFull ; 
 int /*<<< orphan*/  WmInvalidatePaint ; 
 int /*<<< orphan*/  WmInvalidateParent ; 
 int /*<<< orphan*/  WmInvalidateParentChild ; 
 int /*<<< orphan*/  WmInvalidateParentChild2 ; 
 int /*<<< orphan*/  WmInvalidateRgn ; 
 int /*<<< orphan*/  WmPaint ; 
 int /*<<< orphan*/  WmParentErasePaint ; 
 int /*<<< orphan*/  WmParentOnlyNcPaint ; 
 int /*<<< orphan*/  WmParentOnlyPaint ; 
 int /*<<< orphan*/  WmParentPaint ; 
 int /*<<< orphan*/  WmParentPaintNc ; 
 int /*<<< orphan*/  WmSWP_FrameChangedDeferErase ; 
 int /*<<< orphan*/  WmSWP_FrameChanged_clip ; 
 int /*<<< orphan*/  WmSWP_FrameChanged_noclip ; 
 int /*<<< orphan*/  WmSetParentStyle ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  check_update_rgn (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_events () ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  log_all_parent_messages ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_paint_messages(void)
{
    BOOL ret;
    RECT rect, rect2;
    POINT pt;
    MSG msg;
    HWND hparent, hchild;
    HRGN hrgn = CreateRectRgn( 0, 0, 0, 0 );
    HRGN hrgn2 = CreateRectRgn( 0, 0, 0, 0 );
    HWND hwnd = CreateWindowExA(0, "TestWindowClass", "Test overlapped", WS_OVERLAPPEDWINDOW,
                                100, 100, 200, 200, 0, 0, 0, NULL);
    ok (hwnd != 0, "Failed to create overlapped window\n");

    ShowWindow( hwnd, SW_SHOW );
    UpdateWindow( hwnd );
    flush_events();
    flush_sequence();

    check_update_rgn( hwnd, 0 );
    SetRectRgn( hrgn, 10, 10, 20, 20 );
    ret = RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE );
    ok(ret, "RedrawWindow returned %d instead of TRUE\n", ret);
    check_update_rgn( hwnd, hrgn );
    SetRectRgn( hrgn2, 20, 20, 30, 30 );
    ret = RedrawWindow( hwnd, NULL, hrgn2, RDW_INVALIDATE );
    ok(ret, "RedrawWindow returned %d instead of TRUE\n", ret);
    CombineRgn( hrgn, hrgn, hrgn2, RGN_OR );
    check_update_rgn( hwnd, hrgn );
    /* validate everything */
    ret = RedrawWindow( hwnd, NULL, NULL, RDW_VALIDATE );
    ok(ret, "RedrawWindow returned %d instead of TRUE\n", ret);
    check_update_rgn( hwnd, 0 );

    /* test empty region */
    SetRectRgn( hrgn, 10, 10, 10, 15 );
    ret = RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE );
    ok(ret, "RedrawWindow returned %d instead of TRUE\n", ret);
    check_update_rgn( hwnd, 0 );
    /* test empty rect */
    SetRect( &rect, 10, 10, 10, 15 );
    ret = RedrawWindow( hwnd, &rect, NULL, RDW_INVALIDATE );
    ok(ret, "RedrawWindow returned %d instead of TRUE\n", ret);
    check_update_rgn( hwnd, 0 );

    /* flush pending messages */
    flush_events();
    flush_sequence();

    GetClientRect( hwnd, &rect );
    SetRectRgn( hrgn, 0, 0, rect.right - rect.left, rect.bottom - rect.top );
    /* MSDN: if hwnd parameter is NULL, InvalidateRect invalidates and redraws
     * all windows and sends WM_ERASEBKGND and WM_NCPAINT.
     */
    trace("testing InvalidateRect(0, NULL, FALSE)\n");
    SetRectEmpty( &rect );
    ok(InvalidateRect(0, &rect, FALSE), "InvalidateRect(0, &rc, FALSE) should fail\n");
    check_update_rgn( hwnd, hrgn );
    ok_sequence( WmInvalidateErase, "InvalidateErase", FALSE );
    flush_events();
    ok_sequence( WmPaint, "Paint", FALSE );
    RedrawWindow( hwnd, NULL, NULL, RDW_VALIDATE );
    check_update_rgn( hwnd, 0 );

    /* MSDN: if hwnd parameter is NULL, ValidateRect invalidates and redraws
     * all windows and sends WM_ERASEBKGND and WM_NCPAINT.
     */
    trace("testing ValidateRect(0, NULL)\n");
    SetRectEmpty( &rect );
    if (ValidateRect(0, &rect) && /* not supported on Win9x */
        GetUpdateRect(hwnd, NULL, FALSE))  /* or >= Win 8 */
    {
        check_update_rgn( hwnd, hrgn );
        ok_sequence( WmInvalidateErase, "InvalidateErase", FALSE );
        flush_events();
        ok_sequence( WmPaint, "Paint", FALSE );
        RedrawWindow( hwnd, NULL, NULL, RDW_VALIDATE );
        check_update_rgn( hwnd, 0 );
    }

    trace("testing InvalidateRgn(0, NULL, FALSE)\n");
    SetLastError(0xdeadbeef);
    ok(!InvalidateRgn(0, NULL, FALSE), "InvalidateRgn(0, NULL, FALSE) should fail\n");
    ok(GetLastError() == ERROR_INVALID_WINDOW_HANDLE || GetLastError() == 0xdeadbeef,
       "wrong error code %d\n", GetLastError());
    check_update_rgn( hwnd, 0 );
    flush_events();
    ok_sequence( WmEmptySeq, "WmEmptySeq", FALSE );

    trace("testing ValidateRgn(0, NULL)\n");
    SetLastError(0xdeadbeef);
    ok(!ValidateRgn(0, NULL), "ValidateRgn(0, NULL) should fail\n");
    ok(GetLastError() == ERROR_INVALID_WINDOW_HANDLE ||
       broken( GetLastError() == 0xdeadbeef ) /* win9x */,
       "wrong error code %d\n", GetLastError());
    check_update_rgn( hwnd, 0 );
    flush_events();
    ok_sequence( WmEmptySeq, "WmEmptySeq", FALSE );

    trace("testing UpdateWindow(NULL)\n");
    SetLastError(0xdeadbeef);
    ok(!UpdateWindow(NULL), "UpdateWindow(NULL) should fail\n");
    ok(GetLastError() == ERROR_INVALID_WINDOW_HANDLE ||
       broken( GetLastError() == 0xdeadbeef ) /* win9x */,
       "wrong error code %d\n", GetLastError());
    check_update_rgn( hwnd, 0 );
    flush_events();
    ok_sequence( WmEmptySeq, "WmEmptySeq", FALSE );

    /* now with frame */
    SetRectRgn( hrgn, -5, -5, 20, 20 );

    /* flush pending messages */
    flush_events();
    flush_sequence();
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE | RDW_FRAME );
    ok_sequence( WmEmptySeq, "EmptySeq", FALSE );

    SetRectRgn( hrgn, 0, 0, 20, 20 );  /* GetUpdateRgn clips to client area */
    check_update_rgn( hwnd, hrgn );

    flush_sequence();
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE | RDW_FRAME | RDW_ERASENOW );
    ok_sequence( WmInvalidateRgn, "InvalidateRgn", FALSE );

    flush_sequence();
    RedrawWindow( hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASENOW );
    ok_sequence( WmInvalidateFull, "InvalidateFull", FALSE );

    GetClientRect( hwnd, &rect );
    SetRectRgn( hrgn, rect.left, rect.top, rect.right, rect.bottom );
    check_update_rgn( hwnd, hrgn );

    flush_sequence();
    RedrawWindow( hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASE | RDW_ERASENOW );
    ok_sequence( WmInvalidateErase, "InvalidateErase", FALSE );

    flush_sequence();
    RedrawWindow( hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASENOW | RDW_UPDATENOW );
    ok_sequence( WmInvalidatePaint, "InvalidatePaint", FALSE );
    check_update_rgn( hwnd, 0 );

    flush_sequence();
    RedrawWindow( hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ERASE | RDW_UPDATENOW );
    ok_sequence( WmInvalidateErasePaint, "InvalidateErasePaint", FALSE );
    check_update_rgn( hwnd, 0 );

    flush_sequence();
    SetRectRgn( hrgn, 0, 0, 100, 100 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE );
    SetRectRgn( hrgn, 0, 0, 50, 100 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_VALIDATE );
    SetRectRgn( hrgn, 50, 0, 100, 100 );
    check_update_rgn( hwnd, hrgn );
    RedrawWindow( hwnd, NULL, hrgn, RDW_VALIDATE | RDW_ERASENOW );
    ok_sequence( WmEmptySeq, "EmptySeq", FALSE );  /* must not generate messages, everything is valid */
    check_update_rgn( hwnd, 0 );

    flush_sequence();
    SetRectRgn( hrgn, 0, 0, 100, 100 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE | RDW_ERASE );
    SetRectRgn( hrgn, 0, 0, 100, 50 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_VALIDATE | RDW_ERASENOW );
    ok_sequence( WmErase, "Erase", FALSE );
    SetRectRgn( hrgn, 0, 50, 100, 100 );
    check_update_rgn( hwnd, hrgn );

    flush_sequence();
    SetRectRgn( hrgn, 0, 0, 100, 100 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE | RDW_ERASE );
    SetRectRgn( hrgn, 0, 0, 50, 50 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_VALIDATE | RDW_NOERASE | RDW_UPDATENOW );
    ok_sequence( WmPaint, "Paint", FALSE );

    flush_sequence();
    SetRectRgn( hrgn, -4, -4, -2, -2 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE | RDW_FRAME );
    SetRectRgn( hrgn, -200, -200, -198, -198 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_VALIDATE | RDW_NOFRAME | RDW_ERASENOW );
    ok_sequence( WmEmptySeq, "EmptySeq", FALSE );

    flush_sequence();
    SetRectRgn( hrgn, -4, -4, -2, -2 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE | RDW_FRAME );
    SetRectRgn( hrgn, -4, -4, -3, -3 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_VALIDATE | RDW_NOFRAME );
    SetRectRgn( hrgn, 0, 0, 1, 1 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE | RDW_UPDATENOW );
    ok_sequence( WmPaint, "Paint", FALSE );

    flush_sequence();
    SetRectRgn( hrgn, -4, -4, -1, -1 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE | RDW_FRAME );
    RedrawWindow( hwnd, NULL, 0, RDW_ERASENOW );
    /* make sure no WM_PAINT was generated */
    flush_events();
    ok_sequence( WmInvalidateRgn, "InvalidateRgn", FALSE );

    flush_sequence();
    SetRectRgn( hrgn, -4, -4, -1, -1 );
    RedrawWindow( hwnd, NULL, hrgn, RDW_INVALIDATE | RDW_FRAME );
    while (PeekMessageA( &msg, 0, 0, 0, PM_REMOVE ))
    {
        if (msg.hwnd == hwnd && msg.message == WM_PAINT)
        {
            /* GetUpdateRgn must return empty region since only nonclient area is invalidated */
            INT ret = GetUpdateRgn( hwnd, hrgn, FALSE );
            ok( ret == NULLREGION, "Invalid GetUpdateRgn result %d\n", ret );
            ret = GetUpdateRect( hwnd, &rect, FALSE );
            ok( ret, "Invalid GetUpdateRect result %d\n", ret );
            /* this will send WM_NCPAINT and validate the non client area */
            ret = GetUpdateRect( hwnd, &rect, TRUE );
            ok( !ret, "Invalid GetUpdateRect result %d\n", ret );
        }
        DispatchMessageA( &msg );
    }
    ok_sequence( WmGetUpdateRect, "GetUpdateRect", FALSE );

    DestroyWindow( hwnd );

    /* now test with a child window */

    hparent = CreateWindowExA(0, "TestParentClass", "Test parent", WS_OVERLAPPEDWINDOW,
                              100, 100, 200, 200, 0, 0, 0, NULL);
    ok (hparent != 0, "Failed to create parent window\n");

    hchild = CreateWindowExA(0, "TestWindowClass", "Test child", WS_CHILD | WS_VISIBLE | WS_BORDER,
                           10, 10, 100, 100, hparent, 0, 0, NULL);
    ok (hchild != 0, "Failed to create child window\n");

    ShowWindow( hparent, SW_SHOW );
    UpdateWindow( hparent );
    UpdateWindow( hchild );
    flush_events();
    flush_sequence();
    log_all_parent_messages++;

    SetRect( &rect, 0, 0, 50, 50 );
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    RedrawWindow( hparent, NULL, 0, RDW_ERASENOW | RDW_ALLCHILDREN );
    ok_sequence( WmInvalidateParentChild, "InvalidateParentChild", FALSE );

    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    pt.x = pt.y = 0;
    MapWindowPoints( hchild, hparent, &pt, 1 );
    SetRectRgn( hrgn, 0, 0, 50 - pt.x, 50 - pt.y );
    check_update_rgn( hchild, hrgn );
    SetRectRgn( hrgn, 0, 0, 50, 50 );
    check_update_rgn( hparent, hrgn );
    RedrawWindow( hparent, NULL, 0, RDW_ERASENOW );
    ok_sequence( WmInvalidateParent, "InvalidateParent", FALSE );
    RedrawWindow( hchild, NULL, 0, RDW_ERASENOW );
    ok_sequence( WmEmptySeq, "EraseNow child", FALSE );

    flush_events();
    ok_sequence( WmParentPaintNc, "WmParentPaintNc", FALSE );

    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN );
    RedrawWindow( hparent, NULL, 0, RDW_ERASENOW );
    ok_sequence( WmInvalidateParent, "InvalidateParent2", FALSE );
    RedrawWindow( hchild, NULL, 0, RDW_ERASENOW );
    ok_sequence( WmEmptySeq, "EraseNow child", FALSE );

    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE );
    RedrawWindow( hparent, NULL, 0, RDW_ERASENOW | RDW_ALLCHILDREN );
    ok_sequence( WmInvalidateParentChild2, "InvalidateParentChild2", FALSE );

    SetWindowLongA( hparent, GWL_STYLE, GetWindowLongA(hparent,GWL_STYLE) | WS_CLIPCHILDREN );
    flush_sequence();
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN );
    RedrawWindow( hparent, NULL, 0, RDW_ERASENOW );
    ok_sequence( WmInvalidateParentChild, "InvalidateParentChild3", FALSE );

    /* flush all paint messages */
    flush_events();
    flush_sequence();

    /* RDW_UPDATENOW on child with WS_CLIPCHILDREN doesn't change corresponding parent area */
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN );
    SetRectRgn( hrgn, 0, 0, 50, 50 );
    check_update_rgn( hparent, hrgn );
    RedrawWindow( hchild, NULL, 0, RDW_UPDATENOW );
    ok_sequence( WmInvalidateErasePaint2, "WmInvalidateErasePaint2", FALSE );
    SetRectRgn( hrgn, 0, 0, 50, 50 );
    check_update_rgn( hparent, hrgn );

    /* flush all paint messages */
    flush_events();
    SetWindowLongA( hparent, GWL_STYLE, GetWindowLongA(hparent,GWL_STYLE) & ~WS_CLIPCHILDREN );
    flush_sequence();

    /* RDW_UPDATENOW on child without WS_CLIPCHILDREN will validate corresponding parent area */
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    SetRectRgn( hrgn, 0, 0, 50, 50 );
    check_update_rgn( hparent, hrgn );
    RedrawWindow( hchild, NULL, 0, RDW_UPDATENOW );
    ok_sequence( WmInvalidateErasePaint2, "WmInvalidateErasePaint2", FALSE );
    SetRectRgn( hrgn2, 10, 10, 50, 50 );
    CombineRgn( hrgn, hrgn, hrgn2, RGN_DIFF );
    check_update_rgn( hparent, hrgn );
    /* flush all paint messages */
    flush_events();
    flush_sequence();

    /* same as above but parent gets completely validated */
    SetRect( &rect, 20, 20, 30, 30 );
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    SetRectRgn( hrgn, 20, 20, 30, 30 );
    check_update_rgn( hparent, hrgn );
    RedrawWindow( hchild, NULL, 0, RDW_UPDATENOW );
    ok_sequence( WmInvalidateErasePaint2, "WmInvalidateErasePaint2", FALSE );
    check_update_rgn( hparent, 0 );  /* no update region */
    flush_events();
    ok_sequence( WmEmptySeq, "WmEmpty", FALSE );  /* and no paint messages */

    /* make sure RDW_VALIDATE on child doesn't have the same effect */
    flush_sequence();
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    SetRectRgn( hrgn, 20, 20, 30, 30 );
    check_update_rgn( hparent, hrgn );
    RedrawWindow( hchild, NULL, 0, RDW_VALIDATE | RDW_NOERASE );
    SetRectRgn( hrgn, 20, 20, 30, 30 );
    check_update_rgn( hparent, hrgn );

    /* same as above but normal WM_PAINT doesn't validate parent */
    flush_sequence();
    SetRect( &rect, 20, 20, 30, 30 );
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    SetRectRgn( hrgn, 20, 20, 30, 30 );
    check_update_rgn( hparent, hrgn );
    /* no WM_PAINT in child while parent still pending */
    while (PeekMessageA( &msg, hchild, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
    ok_sequence( WmEmptySeq, "No WM_PAINT", FALSE );
    while (PeekMessageA( &msg, hparent, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
    ok_sequence( WmParentErasePaint, "WmParentErasePaint", FALSE );

    flush_sequence();
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    /* no WM_PAINT in child while parent still pending */
    while (PeekMessageA( &msg, hchild, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
    ok_sequence( WmEmptySeq, "No WM_PAINT", FALSE );
    RedrawWindow( hparent, &rect, 0, RDW_VALIDATE | RDW_NOERASE | RDW_NOCHILDREN );
    /* now that parent is valid child should get WM_PAINT */
    while (PeekMessageA( &msg, hchild, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
    ok_sequence( WmInvalidateErasePaint2, "WmInvalidateErasePaint2", FALSE );
    while (PeekMessageA( &msg, 0, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
    ok_sequence( WmEmptySeq, "No other message", FALSE );

    /* same thing with WS_CLIPCHILDREN in parent */
    flush_sequence();
    SetWindowLongA( hparent, GWL_STYLE, GetWindowLongA(hparent,GWL_STYLE) | WS_CLIPCHILDREN );
    ok_sequence( WmSetParentStyle, "WmSetParentStyle", FALSE );
    /* changing style invalidates non client area, but we need to invalidate something else to see it */
    RedrawWindow( hparent, &rect, 0, RDW_UPDATENOW );
    ok_sequence( WmEmptySeq, "No message", FALSE );
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_UPDATENOW );
    ok_sequence( WmParentOnlyNcPaint, "WmParentOnlyNcPaint", FALSE );

    flush_sequence();
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN );
    SetRectRgn( hrgn, 20, 20, 30, 30 );
    check_update_rgn( hparent, hrgn );
    /* no WM_PAINT in child while parent still pending */
    while (PeekMessageA( &msg, hchild, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
    ok_sequence( WmEmptySeq, "No WM_PAINT", FALSE );
    /* WM_PAINT in parent first */
    while (PeekMessageA( &msg, 0, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
    ok_sequence( WmParentPaintNc, "WmParentPaintNc2", FALSE );

    /* no RDW_ERASE in parent still causes RDW_ERASE and RDW_FRAME in child */
    flush_sequence();
    SetRect( &rect, 0, 0, 30, 30 );
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ALLCHILDREN );
    SetRectRgn( hrgn, 0, 0, 30, 30 );
    check_update_rgn( hparent, hrgn );
    flush_events();
    ok_sequence( WmParentPaintNc, "WmParentPaintNc3", FALSE );

    /* validate doesn't cause RDW_NOERASE or RDW_NOFRAME in child */
    flush_sequence();
    SetRect( &rect, -10, 0, 30, 30 );
    RedrawWindow( hchild, &rect, 0, RDW_INVALIDATE | RDW_FRAME | RDW_ERASE );
    SetRect( &rect, 0, 0, 20, 20 );
    RedrawWindow( hparent, &rect, 0, RDW_VALIDATE | RDW_ALLCHILDREN );
    RedrawWindow( hparent, NULL, 0, RDW_UPDATENOW );
    ok_sequence( WmChildPaintNc, "WmChildPaintNc", FALSE );

    /* validate doesn't cause RDW_NOERASE or RDW_NOFRAME in child */
    flush_sequence();
    SetRect( &rect, -10, 0, 30, 30 );
    RedrawWindow( hchild, &rect, 0, RDW_INVALIDATE | RDW_FRAME | RDW_ERASE );
    SetRect( &rect, 0, 0, 100, 100 );
    RedrawWindow( hparent, &rect, 0, RDW_VALIDATE | RDW_ALLCHILDREN );
    RedrawWindow( hparent, NULL, 0, RDW_UPDATENOW );
    ok_sequence( WmEmptySeq, "WmChildPaintNc2", FALSE );
    RedrawWindow( hparent, NULL, 0, RDW_ERASENOW );
    ok_sequence( WmEmptySeq, "WmChildPaintNc3", FALSE );

    /* WS_CLIPCHILDREN doesn't exclude children from update region */
    flush_sequence();
    RedrawWindow( hparent, NULL, 0, RDW_INVALIDATE | RDW_ERASE | RDW_NOCHILDREN );
    GetClientRect( hparent, &rect );
    SetRectRgn( hrgn, rect.left, rect.top, rect.right, rect.bottom );
    check_update_rgn( hparent, hrgn );
    flush_events();

    RedrawWindow( hparent, NULL, 0, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN );
    GetClientRect( hparent, &rect );
    SetRectRgn( hrgn, rect.left, rect.top, rect.right, rect.bottom );
    check_update_rgn( hparent, hrgn );
    flush_events();

    /* test RDW_INTERNALPAINT behavior */

    flush_sequence();
    RedrawWindow( hparent, NULL, 0, RDW_INTERNALPAINT | RDW_NOCHILDREN );
    flush_events();
    ok_sequence( WmParentOnlyPaint, "WmParentOnlyPaint", FALSE );

    RedrawWindow( hparent, NULL, 0, RDW_INTERNALPAINT | RDW_ALLCHILDREN );
    flush_events();
    ok_sequence( WmParentPaint, "WmParentPaint", FALSE );

    RedrawWindow( hparent, NULL, 0, RDW_INTERNALPAINT );
    flush_events();
    ok_sequence( WmParentOnlyPaint, "WmParentOnlyPaint", FALSE );

    assert( GetWindowLongA(hparent, GWL_STYLE) & WS_CLIPCHILDREN );
    UpdateWindow( hparent );
    flush_events();
    flush_sequence();
    trace("testing SWP_FRAMECHANGED on parent with WS_CLIPCHILDREN\n");
    RedrawWindow( hchild, NULL, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    SetWindowPos( hparent, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE |
                  SWP_NOACTIVATE | SWP_NOZORDER | SWP_FRAMECHANGED );
    flush_events();
    ok_sequence(WmSWP_FrameChanged_clip, "SetWindowPos:FrameChanged_clip", FALSE );

    UpdateWindow( hparent );
    flush_events();
    flush_sequence();
    trace("testing SWP_FRAMECHANGED|SWP_DEFERERASE on parent with WS_CLIPCHILDREN\n");
    RedrawWindow( hchild, NULL, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    SetWindowPos( hparent, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_DEFERERASE |
                  SWP_NOACTIVATE | SWP_NOZORDER | SWP_FRAMECHANGED );
    flush_events();
    ok_sequence(WmSWP_FrameChangedDeferErase, "SetWindowPos:FrameChangedDeferErase", FALSE );

    SetWindowLongA( hparent, GWL_STYLE, GetWindowLongA(hparent,GWL_STYLE) & ~WS_CLIPCHILDREN );
    ok_sequence( WmSetParentStyle, "WmSetParentStyle", FALSE );
    RedrawWindow( hparent, NULL, 0, RDW_INTERNALPAINT );
    flush_events();
    ok_sequence( WmParentPaint, "WmParentPaint", FALSE );

    assert( !(GetWindowLongA(hparent, GWL_STYLE) & WS_CLIPCHILDREN) );
    UpdateWindow( hparent );
    flush_events();
    flush_sequence();
    trace("testing SWP_FRAMECHANGED on parent without WS_CLIPCHILDREN\n");
    RedrawWindow( hchild, NULL, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    SetWindowPos( hparent, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE |
                  SWP_NOACTIVATE | SWP_NOZORDER | SWP_FRAMECHANGED );
    flush_events();
    ok_sequence(WmSWP_FrameChanged_noclip, "SetWindowPos:FrameChanged_noclip", FALSE );

    UpdateWindow( hparent );
    flush_events();
    flush_sequence();
    trace("testing SWP_FRAMECHANGED|SWP_DEFERERASE on parent without WS_CLIPCHILDREN\n");
    RedrawWindow( hchild, NULL, 0, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME );
    SetWindowPos( hparent, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_DEFERERASE |
                  SWP_NOACTIVATE | SWP_NOZORDER | SWP_FRAMECHANGED );
    flush_events();
    ok_sequence(WmSWP_FrameChangedDeferErase, "SetWindowPos:FrameChangedDeferErase", FALSE );

    ok(GetWindowLongA( hparent, GWL_STYLE ) & WS_VISIBLE, "parent should be visible\n");
    ok(GetWindowLongA( hchild, GWL_STYLE ) & WS_VISIBLE, "child should be visible\n");

    UpdateWindow( hparent );
    flush_events();
    flush_sequence();
    trace("testing SetWindowPos(-10000, -10000) on child\n");
    SetWindowPos( hchild, 0, -10000, -10000, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER );
    check_update_rgn( hchild, 0 );
    flush_events();

#if 0 /* this one doesn't pass under Wine yet */
    UpdateWindow( hparent );
    flush_events();
    flush_sequence();
    trace("testing ShowWindow(SW_MINIMIZE) on child\n");
    ShowWindow( hchild, SW_MINIMIZE );
    check_update_rgn( hchild, 0 );
    flush_events();
#endif

    UpdateWindow( hparent );
    flush_events();
    flush_sequence();
    trace("testing SetWindowPos(-10000, -10000) on parent\n");
    SetWindowPos( hparent, 0, -10000, -10000, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER );
    check_update_rgn( hparent, 0 );
    flush_events();

    log_all_parent_messages--;
    DestroyWindow( hparent );
    ok(!IsWindow(hchild), "child must be destroyed with its parent\n");

    /* tests for moving windows off-screen (needs simple WS_POPUP windows) */

    hparent = CreateWindowExA(0, "TestParentClass", "Test parent", WS_POPUP | WS_VISIBLE,
                              100, 100, 200, 200, 0, 0, 0, NULL);
    ok (hparent != 0, "Failed to create parent window\n");

    hchild = CreateWindowExA(0, "TestWindowClass", "Test child", WS_CHILD | WS_VISIBLE,
                           10, 10, 100, 100, hparent, 0, 0, NULL);
    ok (hchild != 0, "Failed to create child window\n");

    ShowWindow( hparent, SW_SHOW );
    UpdateWindow( hparent );
    UpdateWindow( hchild );
    flush_events();
    flush_sequence();

    /* moving child outside of parent boundaries changes update region */
    SetRect( &rect, 0, 0, 40, 40 );
    RedrawWindow( hchild, &rect, 0, RDW_INVALIDATE | RDW_ERASE );
    SetRectRgn( hrgn, 0, 0, 40, 40 );
    check_update_rgn( hchild, hrgn );
    MoveWindow( hchild, -10, 10, 100, 100, FALSE );
    SetRectRgn( hrgn, 10, 0, 40, 40 );
    check_update_rgn( hchild, hrgn );
    MoveWindow( hchild, -10, -10, 100, 100, FALSE );
    SetRectRgn( hrgn, 10, 10, 40, 40 );
    check_update_rgn( hchild, hrgn );

    /* moving parent off-screen does too */
    SetRect( &rect, 0, 0, 100, 100 );
    RedrawWindow( hparent, &rect, 0, RDW_INVALIDATE | RDW_ERASE | RDW_NOCHILDREN );
    SetRectRgn( hrgn, 0, 0, 100, 100 );
    check_update_rgn( hparent, hrgn );
    SetRectRgn( hrgn, 10, 10, 40, 40 );
    check_update_rgn( hchild, hrgn );
    MoveWindow( hparent, -20, -20, 200, 200, FALSE );
    GetUpdateRect( hparent, &rect2, FALSE );
    if (!EqualRect( &rect2, &rect )) /* Win 8 and later don't crop update to screen */
    {
        rect.left += 20;
        rect.top += 20;
    }
    SetRectRgn( hrgn, rect.left, rect.top, rect.right, rect.bottom );
    check_update_rgn( hparent, hrgn );
    SetRectRgn( hrgn, rect.left + 10, rect.top + 10, 40, 40 );
    check_update_rgn( hchild, hrgn );

    /* invalidated region is cropped by the parent rects */
    SetRect( &rect, 0, 0, 50, 50 );
    RedrawWindow( hchild, &rect, 0, RDW_INVALIDATE | RDW_ERASE );
    SetRectRgn( hrgn, rect2.left + 10, rect2.top + 10, 50, 50 );
    check_update_rgn( hchild, hrgn );

    DestroyWindow( hparent );
    ok(!IsWindow(hchild), "child must be destroyed with its parent\n");
    flush_sequence();

    DeleteObject( hrgn );
    DeleteObject( hrgn2 );
}