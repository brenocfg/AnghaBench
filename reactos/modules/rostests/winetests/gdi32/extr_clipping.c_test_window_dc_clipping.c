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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int COMPLEXREGION ; 
 int /*<<< orphan*/  CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EqualRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ExtSelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetRgnBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGN_COPY ; 
 int /*<<< orphan*/  RGN_DIFF ; 
 int RectVisible (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SIMPLEREGION ; 
 int /*<<< orphan*/  SM_CMONITORS ; 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CXVIRTUALSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 int /*<<< orphan*/  SM_CYVIRTUALSCREEN ; 
 int /*<<< orphan*/  SM_XVIRTUALSCREEN ; 
 int /*<<< orphan*/  SM_YVIRTUALSCREEN ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  WS_POPUP ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  trace (char*,int,int) ; 
 int wine_dbgstr_rect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_window_dc_clipping(void)
{
    HDC hdc;
    HRGN hrgn, hrgn_empty;
    HWND hwnd;
    RECT rc, virtual_rect;
    int ret, screen_width, screen_height;

    /* Windows versions earlier than Win2k do not support the virtual screen metrics,
     * so we fall back to the primary screen metrics. */
    screen_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    if(!screen_width) screen_width = GetSystemMetrics(SM_CXSCREEN);
    screen_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    if(!screen_height) screen_height = GetSystemMetrics(SM_CYSCREEN);
    SetRect(&virtual_rect, GetSystemMetrics(SM_XVIRTUALSCREEN), GetSystemMetrics(SM_YVIRTUALSCREEN),
            GetSystemMetrics(SM_XVIRTUALSCREEN) + screen_width, GetSystemMetrics(SM_YVIRTUALSCREEN) + screen_height);

    trace("screen resolution %d x %d\n", screen_width, screen_height);

    hwnd = CreateWindowExA(0, "static", NULL, WS_POPUP,
                           -100, -100, screen_width * 2, screen_height * 2, 0, 0, 0, NULL);
    hdc = GetWindowDC(0);
    hrgn_empty = CreateRectRgn(0, 0, 0, 0);
    hrgn = CreateRectRgn(0, 0, 0, 0);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = ExtSelectClipRgn(hdc, 0, RGN_DIFF);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = ExtSelectClipRgn(hdc, hrgn_empty, RGN_DIFF);
    ok(ret == SIMPLEREGION || (ret == COMPLEXREGION && GetSystemMetrics(SM_CMONITORS) > 1),
       "expected SIMPLEREGION, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 1, "expected 1, got %d\n", ret);

    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(EqualRect(&rc, &virtual_rect), "expected %s, got %s\n", wine_dbgstr_rect(&virtual_rect),
       wine_dbgstr_rect(&rc));

    SetRect( &rc, 10, 10, 20, 20 );
    ret = RectVisible( hdc, &rc );
    ok( ret, "RectVisible failed for %s\n", wine_dbgstr_rect(&rc));

    SetRect( &rc, 20, 20, 10, 10 );
    ret = RectVisible( hdc, &rc );
    ok( ret, "RectVisible failed for %s\n", wine_dbgstr_rect(&rc));

    ret = ExtSelectClipRgn(hdc, 0, RGN_DIFF);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 1, "expected 1, got %d\n", ret);

    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(EqualRect(&rc, &virtual_rect), "expected %s, got %s\n", wine_dbgstr_rect(&virtual_rect),
       wine_dbgstr_rect(&rc));

    ret = ExtSelectClipRgn(hdc, 0, RGN_COPY);
    ok(ret == SIMPLEREGION || (ret == COMPLEXREGION && GetSystemMetrics(SM_CMONITORS) > 1),
       "expected SIMPLEREGION, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 0, "expected 0, got %d\n", ret);

    DeleteDC(hdc);
    DeleteObject(hrgn);
    DeleteObject(hrgn_empty);
    DestroyWindow(hwnd);
}