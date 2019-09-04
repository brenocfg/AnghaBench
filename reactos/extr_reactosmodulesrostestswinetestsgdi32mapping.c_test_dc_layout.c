#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {double eM11; double eM12; double eM21; double eM22; double eDx; double eDy; } ;
typedef  TYPE_1__ XFORM ;
struct TYPE_11__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_10__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
typedef  TYPE_2__ SIZE ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_3__ POINT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int EqualRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExtSelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClipBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDCOrgEx (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetMapMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetRgnBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetViewportOrgEx (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GetWindowExtEx (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetWindowOrgEx (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  HORZRES ; 
 int /*<<< orphan*/  HORZSIZE ; 
 int /*<<< orphan*/  IntersectClipRect (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  LAYOUT_LTR ; 
 int /*<<< orphan*/  LAYOUT_RTL ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int MM_ANISOTROPIC ; 
 int MM_LOMETRIC ; 
 int MM_TEXT ; 
 int MulDiv (int,int,int) ; 
 int /*<<< orphan*/  OffsetClipRgn (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OffsetRect (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RGN_OR ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMapMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  SetRectRgn (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  VERTRES ; 
 int /*<<< orphan*/  VERTSIZE ; 
 int /*<<< orphan*/  expect_LPtoDP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  expect_viewport_ext (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  expect_window_ext (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  expect_world_transform (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetLayout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pGetRandomRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pGetTransform (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  pSetLayout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rough_match (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_rect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_dc_layout(void)
{
    INT ret, size_cx, size_cy, res_x, res_y, dpi_x, dpi_y;
    SIZE size;
    POINT pt;
    HBITMAP bitmap;
    RECT rc, ret_rc;
    HDC hdc;
    HRGN hrgn;

    if (!pGetLayout || !pSetLayout)
    {
        win_skip( "Don't have SetLayout\n" );
        return;
    }

    hdc = CreateCompatibleDC(0);
    bitmap = CreateCompatibleBitmap( hdc, 100, 100 );
    SelectObject( hdc, bitmap );

    size_cx = GetDeviceCaps(hdc, HORZSIZE);
    size_cy = GetDeviceCaps(hdc, VERTSIZE);
    res_x = GetDeviceCaps(hdc, HORZRES);
    res_y = GetDeviceCaps(hdc, VERTRES);
    dpi_x = GetDeviceCaps(hdc, LOGPIXELSX);
    dpi_y = GetDeviceCaps(hdc, LOGPIXELSY);

    ret = GetMapMode( hdc );
    ok(ret == MM_TEXT, "expected MM_TEXT, got %d\n", ret);
    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 1.0, 1.0);
    expect_LPtoDP(hdc, 1000, 1000);

    pSetLayout( hdc, LAYOUT_RTL );
    if (!pGetLayout( hdc ))
    {
        win_skip( "SetLayout not supported\n" );
        DeleteDC(hdc);
        return;
    }

    ret = GetMapMode( hdc );
    ok(ret == MM_ANISOTROPIC, "expected MM_ANISOTROPIC, got %d\n", ret);
    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 1.0, 1.0);
    expect_LPtoDP(hdc, -1000 + 99, 1000);
    GetViewportOrgEx( hdc, &pt );
    ok( pt.x == 0 && pt.y == 0, "wrong origin %d,%d\n", pt.x, pt.y );
    GetWindowOrgEx( hdc, &pt );
    ok( pt.x == 0 && pt.y == 0, "wrong origin %d,%d\n", pt.x, pt.y );
    GetDCOrgEx( hdc, &pt );
    ok( pt.x == 0 && pt.y == 0, "wrong origin %d,%d\n", pt.x, pt.y );
    if (pGetTransform)
    {
        XFORM xform;
        BOOL ret = pGetTransform( hdc, 0x204, &xform ); /* World -> Device */
        ok( ret, "got %d\n", ret );
        ok( xform.eM11 == -1.0, "got %f\n", xform.eM11 );
        ok( xform.eM12 == 0.0, "got %f\n", xform.eM12 );
        ok( xform.eM21 == 0.0, "got %f\n", xform.eM21 );
        ok( xform.eM22 == 1.0, "got %f\n", xform.eM22 );
        ok( xform.eDx == 99.0, "got %f\n", xform.eDx );
        ok( xform.eDy == 0.0, "got %f\n", xform.eDy );
    }

    SetRect( &rc, 10, 10, 20, 20 );
    IntersectClipRect( hdc, 10, 10, 20, 20 );
    hrgn = CreateRectRgn( 0, 0, 0, 0 );
    GetClipRgn( hdc, hrgn );
    GetRgnBox( hrgn, &ret_rc );
    ok( EqualRect( &rc, &ret_rc ), "wrong clip box %s\n", wine_dbgstr_rect( &ret_rc ));
    pSetLayout( hdc, LAYOUT_LTR );
    SetRect( &rc, 80, 10, 90, 20 );
    GetClipRgn( hdc, hrgn );
    GetRgnBox( hrgn, &ret_rc );
    ok( EqualRect( &rc, &ret_rc ), "wrong clip box %s\n", wine_dbgstr_rect( &ret_rc ));
    GetClipBox( hdc, &ret_rc );
    ok( EqualRect( &rc, &ret_rc ), "wrong clip box %s\n", wine_dbgstr_rect( &ret_rc ));
    IntersectClipRect( hdc, 80, 10, 85, 20 );
    pSetLayout( hdc, LAYOUT_RTL );
    SetRect( &rc, 15, 10, 20, 20 );
    GetClipRgn( hdc, hrgn );
    GetRgnBox( hrgn, &ret_rc );
    ok( EqualRect( &rc, &ret_rc ), "wrong clip box %s\n", wine_dbgstr_rect( &ret_rc ));
    GetClipBox( hdc, &ret_rc );
    ok( EqualRect( &rc, &ret_rc ), "wrong clip box %s\n", wine_dbgstr_rect( &ret_rc ));
    SetRectRgn( hrgn, 60, 10, 80, 20 );
    pSetLayout( hdc, LAYOUT_LTR );
    ExtSelectClipRgn( hdc, hrgn, RGN_OR );
    pSetLayout( hdc, LAYOUT_RTL );
    SetRect( &rc, 15, 10, 40, 20 );
    GetClipRgn( hdc, hrgn );
    GetRgnBox( hrgn, &ret_rc );
    ok( EqualRect( &rc, &ret_rc ), "wrong clip box %s\n", wine_dbgstr_rect( &ret_rc ));
    GetClipBox( hdc, &ret_rc );
    ok( EqualRect( &rc, &ret_rc ), "wrong clip box %s\n", wine_dbgstr_rect( &ret_rc ));

    /* OffsetClipRgn mirrors too */
    OffsetClipRgn( hdc, 5, 5 );
    OffsetRect( &rc, 5, 5 );
    GetClipRgn( hdc, hrgn );
    GetRgnBox( hrgn, &ret_rc );
    ok( EqualRect( &rc, &ret_rc ), "wrong clip box %s\n", wine_dbgstr_rect( &ret_rc ));

    /* GetRandomRgn returns the raw region */
    if (pGetRandomRgn)
    {
        SetRect( &rc, 55, 15, 80, 25 );
        pGetRandomRgn( hdc, hrgn, 1 );
        GetRgnBox( hrgn, &ret_rc );
        ok( EqualRect( &rc, &ret_rc ), "wrong clip box %s\n", wine_dbgstr_rect( &ret_rc ));
    }

    SetMapMode(hdc, MM_LOMETRIC);
    ret = GetMapMode( hdc );
    ok(ret == MM_ANISOTROPIC, "expected MM_ANISOTROPIC, got %d\n", ret);

    expect_viewport_ext(hdc, res_x, -res_y);
    ok( GetWindowExtEx( hdc, &size ), "GetWindowExtEx failed\n" );
    ok( rough_match( size.cx, size_cx * 10 ) ||
        rough_match( size.cx, MulDiv( res_x, 254, dpi_x )),  /* Vista uses a more precise method */
        "expected cx %d or %d, got %d\n", size_cx * 10, MulDiv( res_x, 254, dpi_x ), size.cx );
    ok( rough_match( size.cy, size_cy * 10 ) ||
        rough_match( size.cy, MulDiv( res_y, 254, dpi_y )),  /* Vista uses a more precise method */
        "expected cy %d or %d, got %d\n", size_cy * 10, MulDiv( res_y, 254, dpi_y ), size.cy );
    expect_world_transform(hdc, 1.0, 1.0);
    expect_LPtoDP(hdc, -MulDiv(1000 / 10, res_x, size_cx) + 99, -MulDiv(1000 / 10, res_y, size_cy));

    SetMapMode(hdc, MM_TEXT);
    ret = GetMapMode( hdc );
    ok(ret == MM_ANISOTROPIC, "expected MM_ANISOTROPIC, got %d\n", ret);
    pSetLayout( hdc, LAYOUT_LTR );
    ret = GetMapMode( hdc );
    ok(ret == MM_ANISOTROPIC, "expected MM_ANISOTROPIC, got %d\n", ret);
    SetMapMode(hdc, MM_TEXT);
    ret = GetMapMode( hdc );
    ok(ret == MM_TEXT, "expected MM_TEXT, got %d\n", ret);

    DeleteDC(hdc);
    DeleteObject( bitmap );
}