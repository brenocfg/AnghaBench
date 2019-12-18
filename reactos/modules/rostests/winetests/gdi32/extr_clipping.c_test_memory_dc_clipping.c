#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ left; scalar_t__ top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int ExtSelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetRgnBox (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RGN_COPY ; 
 int /*<<< orphan*/  RGN_DIFF ; 
 int RectVisible (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int SIMPLEREGION ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void test_memory_dc_clipping(void)
{
    HDC hdc;
    HRGN hrgn, hrgn_empty;
    HBITMAP hbmp;
    RECT rc;
    int ret;

    hdc = CreateCompatibleDC(0);
    hrgn_empty = CreateRectRgn(0, 0, 0, 0);
    hrgn = CreateRectRgn(0, 0, 0, 0);
    hbmp = CreateCompatibleBitmap(hdc, 100, 100);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = ExtSelectClipRgn(hdc, hrgn_empty, RGN_DIFF);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 1, "expected 1, got %d\n", ret);

    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 0 && rc.top == 0 && rc.right == 1 && rc.bottom == 1,
       "expected 0,0-1,1, got %s\n", wine_dbgstr_rect(&rc));

    ret = ExtSelectClipRgn(hdc, 0, RGN_COPY);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = ExtSelectClipRgn(hdc, 0, RGN_DIFF);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 0, "expected 0, got %d\n", ret);

    SelectObject(hdc, hbmp);

    ret = ExtSelectClipRgn(hdc, hrgn_empty, RGN_DIFF);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 1, "expected 1, got %d\n", ret);

    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 0 && rc.top == 0 && rc.right == 100 && rc.bottom == 100,
       "expected 0,0-100,100, got %s\n", wine_dbgstr_rect(&rc));

    SetRect( &rc, 10, 10, 20, 20 );
    ret = RectVisible( hdc, &rc );
    ok(ret, "RectVisible failed for %s\n", wine_dbgstr_rect(&rc));

    SetRect( &rc, 20, 20, 10, 10 );
    ret = RectVisible( hdc, &rc );
    ok(ret, "RectVisible failed for %s\n", wine_dbgstr_rect(&rc));

    ret = ExtSelectClipRgn(hdc, 0, RGN_DIFF);
    ok(ret == 0, "expected 0, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn);
    ok(ret == 1, "expected 1, got %d\n", ret);

    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 0 && rc.top == 0 && rc.right == 100 && rc.bottom == 100,
       "expected 0,0-100,100, got %s\n", wine_dbgstr_rect(&rc));

    DeleteDC(hdc);
    DeleteObject(hrgn);
    DeleteObject(hrgn_empty);
    DeleteObject(hbmp);
}