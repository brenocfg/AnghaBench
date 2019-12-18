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
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HRGN ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int COMPLEXREGION ; 
 scalar_t__ CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int EqualRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetClipBox (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetClipRgn (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * GetDC (scalar_t__) ; 
 int GetRgnBox (scalar_t__,int /*<<< orphan*/ *) ; 
 int IntersectClipRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int NULLREGION ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ *) ; 
 int RestoreDC (int /*<<< orphan*/ *,int) ; 
 int SIMPLEREGION ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int SaveDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 int /*<<< orphan*/  WS_POPUP ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  dump_region (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,int) ; 
 int wine_dbgstr_rect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_savedc_2(void)
{
    HWND hwnd;
    HDC hdc;
    HRGN hrgn;
    RECT rc, rc_clip;
    int ret;

    hwnd = CreateWindowExA(0, "static", "", WS_POPUP, 0,0,100,100,
                           0, 0, 0, NULL);
    assert(hwnd != 0);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    hrgn = CreateRectRgn(0, 0, 0, 0);
    assert(hrgn != 0);

    hdc = GetDC(hwnd);
    ok(hdc != NULL, "GetDC failed\n");

    ret = GetClipBox(hdc, &rc_clip);
    ok(ret == SIMPLEREGION || broken(ret == COMPLEXREGION), "GetClipBox returned %d instead of SIMPLEREGION\n", ret);
    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 0, "GetClipRgn returned %d instead of 0\n", ret);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == NULLREGION, "GetRgnBox returned %d %s instead of NULLREGION\n",
       ret, wine_dbgstr_rect(&rc));
    /*dump_region(hrgn);*/
    SetRect(&rc, 0, 0, 100, 100);
    ok(EqualRect(&rc, &rc_clip), "rects are not equal: %s - %s\n", wine_dbgstr_rect(&rc),
       wine_dbgstr_rect(&rc_clip));

    ret = SaveDC(hdc);
    ok(ret == 1, "ret = %d\n", ret);

    ret = IntersectClipRect(hdc, 0, 0, 50, 50);
    if (ret == COMPLEXREGION)
    {
        /* XP returns COMPLEXREGION although dump_region reports only 1 rect */
        trace("Windows BUG: IntersectClipRect returned %d instead of SIMPLEREGION\n", ret);
        /* let's make sure that it's a simple region */
        ret = GetClipRgn(hdc, hrgn);
        ok(ret == 1, "GetClipRgn returned %d instead of 1\n", ret);
        dump_region(hrgn);
    }
    else
        ok(ret == SIMPLEREGION, "IntersectClipRect returned %d instead of SIMPLEREGION\n", ret);

    ret = GetClipBox(hdc, &rc_clip);
    ok(ret == SIMPLEREGION || broken(ret == COMPLEXREGION), "GetClipBox returned %d instead of SIMPLEREGION\n", ret);
    SetRect(&rc, 0, 0, 50, 50);
    ok(EqualRect(&rc, &rc_clip), "rects are not equal: %s - %s\n", wine_dbgstr_rect(&rc),
       wine_dbgstr_rect(&rc_clip));

    ret = RestoreDC(hdc, 1);
    ok(ret, "ret = %d\n", ret);

    ret = GetClipBox(hdc, &rc_clip);
    ok(ret == SIMPLEREGION || broken(ret == COMPLEXREGION), "GetClipBox returned %d instead of SIMPLEREGION\n", ret);
    SetRect(&rc, 0, 0, 100, 100);
    ok(EqualRect(&rc, &rc_clip), "rects are not equal: %s - %s\n", wine_dbgstr_rect(&rc),
       wine_dbgstr_rect(&rc_clip));

    DeleteObject(hrgn);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}