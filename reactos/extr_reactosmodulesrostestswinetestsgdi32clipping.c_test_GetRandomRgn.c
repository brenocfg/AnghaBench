#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; scalar_t__ bottom; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int EqualRect (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (scalar_t__) ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int GetRandomRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetRgnBox (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int GetVersion () ; 
 int /*<<< orphan*/  HWND_TOPMOST ; 
 int /*<<< orphan*/  IntersectClipRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IntersectRect (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ ) ; 
 int SYSRGN ; 
 int /*<<< orphan*/  SetMetaRgn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int WS_POPUP ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void test_GetRandomRgn(void)
{
    HWND hwnd = CreateWindowExA(0,"BUTTON","test",WS_VISIBLE|WS_POPUP,0,0,100,100,GetDesktopWindow(),0,0,0);
    HDC hdc;
    HRGN hrgn = CreateRectRgn(0, 0, 0, 0);
    int ret;
    RECT rc, rc2;
    RECT ret_rc, window_rc;

    ok( hwnd != 0, "CreateWindow failed\n" );

    SetRect(&window_rc, 400, 300, 500, 400);
    SetWindowPos(hwnd, HWND_TOPMOST, window_rc.left, window_rc.top,
                 window_rc.right - window_rc.left, window_rc.bottom - window_rc.top, 0 );
    hdc = GetDC(hwnd);

    ret = GetRandomRgn(hdc, hrgn, 1);
    ok(ret == 0, "GetRandomRgn rets %d\n", ret);
    ret = GetRandomRgn(hdc, hrgn, 2);
    ok(ret == 0, "GetRandomRgn rets %d\n", ret);
    ret = GetRandomRgn(hdc, hrgn, 3);
    ok(ret == 0, "GetRandomRgn rets %d\n", ret);

    /* Set a clip region */
    SetRect(&rc, 20, 20, 80, 80);
    IntersectClipRect(hdc, rc.left, rc.top, rc.right, rc.bottom);

    ret = GetRandomRgn(hdc, hrgn, 1);
    ok(ret != 0, "GetRandomRgn rets %d\n", ret);
    GetRgnBox(hrgn, &ret_rc);
    ok(EqualRect(&rc, &ret_rc), "GetRandomRgn %s\n", wine_dbgstr_rect(&ret_rc));
 
    ret = GetRandomRgn(hdc, hrgn, 2);
    ok(ret == 0, "GetRandomRgn rets %d\n", ret);

    ret = GetRandomRgn(hdc, hrgn, 3);
    ok(ret != 0, "GetRandomRgn rets %d\n", ret);
    GetRgnBox(hrgn, &ret_rc);
    ok(EqualRect(&rc, &ret_rc), "GetRandomRgn %s\n", wine_dbgstr_rect(&ret_rc));

    /* Move the clip to the meta and clear the clip */
    SetMetaRgn(hdc);

    ret = GetRandomRgn(hdc, hrgn, 1);
    ok(ret == 0, "GetRandomRgn rets %d\n", ret);
    ret = GetRandomRgn(hdc, hrgn, 2);
    ok(ret != 0, "GetRandomRgn rets %d\n", ret);
    GetRgnBox(hrgn, &ret_rc);
    ok(EqualRect(&rc, &ret_rc), "GetRandomRgn %s\n", wine_dbgstr_rect(&ret_rc));

    ret = GetRandomRgn(hdc, hrgn, 3);
    ok(ret != 0, "GetRandomRgn rets %d\n", ret);
    GetRgnBox(hrgn, &ret_rc);
    ok(EqualRect(&rc, &ret_rc), "GetRandomRgn %s\n", wine_dbgstr_rect(&ret_rc));

    /* Set a new clip (still got the meta) */
    SetRect(&rc2, 10, 30, 70, 90);
    IntersectClipRect(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);

    ret = GetRandomRgn(hdc, hrgn, 1);
    ok(ret != 0, "GetRandomRgn rets %d\n", ret);
    GetRgnBox(hrgn, &ret_rc);
    ok(EqualRect(&rc2, &ret_rc), "GetRandomRgn %s\n", wine_dbgstr_rect(&ret_rc));

    ret = GetRandomRgn(hdc, hrgn, 2);
    ok(ret != 0, "GetRandomRgn rets %d\n", ret);
    GetRgnBox(hrgn, &ret_rc);
    ok(EqualRect(&rc, &ret_rc), "GetRandomRgn %s\n", wine_dbgstr_rect(&ret_rc));
 
    IntersectRect(&rc2, &rc, &rc2);

    ret = GetRandomRgn(hdc, hrgn, 3);
    ok(ret != 0, "GetRandomRgn rets %d\n", ret);
    GetRgnBox(hrgn, &ret_rc);
    ok(EqualRect(&rc2, &ret_rc), "GetRandomRgn %s\n", wine_dbgstr_rect(&ret_rc));


    ret = GetRandomRgn(hdc, hrgn, SYSRGN);
    ok(ret != 0, "GetRandomRgn rets %d\n", ret);
    GetRgnBox(hrgn, &ret_rc);
    if(GetVersion() & 0x80000000)
        OffsetRect(&window_rc, -window_rc.left, -window_rc.top);
    /* the window may be partially obscured so the region may be smaller */
    IntersectRect( &window_rc, &ret_rc, &ret_rc );
    ok(EqualRect(&window_rc, &ret_rc), "GetRandomRgn %s\n", wine_dbgstr_rect(&ret_rc));

    DeleteObject(hrgn);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}