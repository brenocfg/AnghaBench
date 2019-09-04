#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float eM11; float eM12; float eM21; float eM22; float eDx; float eDy; } ;
typedef  TYPE_1__ XFORM ;
struct TYPE_7__ {int cx; int cy; } ;
typedef  TYPE_2__ SIZE ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int GM_ADVANCED ; 
 int GM_COMPATIBLE ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetGraphicsMode (int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetWindowExtEx (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  HORZRES ; 
 int /*<<< orphan*/  HORZSIZE ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int MM_ANISOTROPIC ; 
 int MM_LOMETRIC ; 
 int MM_TEXT ; 
 int MulDiv (int,int,int) ; 
 int SetGraphicsMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SetMapMode (int /*<<< orphan*/ ,int) ; 
 int SetViewportExtEx (int /*<<< orphan*/ ,int,int,TYPE_2__*) ; 
 int SetWorldTransform (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VERTRES ; 
 int /*<<< orphan*/  VERTSIZE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  expect_LPtoDP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  expect_viewport_ext (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  expect_window_ext (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  expect_world_transform (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ rough_match (int,int) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,int,int,int,int,int,int) ; 

__attribute__((used)) static void test_world_transform(void)
{
    HDC hdc;
    INT ret, size_cx, size_cy, res_x, res_y, dpi_x, dpi_y;
    XFORM xform;
    SIZE size;

    hdc = CreateCompatibleDC(0);

    xform.eM11 = 1.0f;
    xform.eM12 = 0.0f;
    xform.eM21 = 0.0f;
    xform.eM22 = 1.0f;
    xform.eDx = 0.0f;
    xform.eDy = 0.0f;
    ret = SetWorldTransform(hdc, &xform);
    ok(!ret, "SetWorldTransform should fail in GM_COMPATIBLE mode\n");

    size_cx = GetDeviceCaps(hdc, HORZSIZE);
    size_cy = GetDeviceCaps(hdc, VERTSIZE);
    res_x = GetDeviceCaps(hdc, HORZRES);
    res_y = GetDeviceCaps(hdc, VERTRES);
    dpi_x = GetDeviceCaps(hdc, LOGPIXELSX);
    dpi_y = GetDeviceCaps(hdc, LOGPIXELSY);
    trace("dc size %d x %d, resolution %d x %d dpi %d x %d\n",
          size_cx, size_cy, res_x, res_y, dpi_x, dpi_y );

    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 1.0, 1.0);
    expect_LPtoDP(hdc, 1000, 1000);

    SetLastError(0xdeadbeef);
    ret = SetMapMode(hdc, MM_LOMETRIC);
    ok(ret == MM_TEXT, "expected MM_TEXT, got %d\n", ret);

    expect_viewport_ext(hdc, res_x, -res_y);
    ok( GetWindowExtEx( hdc, &size ), "GetWindowExtEx failed\n" );
    ok( rough_match( size.cx, size_cx * 10 ) ||
        rough_match( size.cx, MulDiv( res_x, 254, dpi_x )),  /* Vista uses a more precise method */
        "expected cx %d or %d, got %d\n", size_cx * 10, MulDiv( res_x, 254, dpi_x ), size.cx );
    ok( rough_match( size.cy, size_cy * 10 ) ||
        rough_match( size.cy, MulDiv( res_y, 254, dpi_y )),  /* Vista uses a more precise method */
        "expected cy %d or %d, got %d\n", size_cy * 10, MulDiv( res_y, 254, dpi_y ), size.cy );
    expect_world_transform(hdc, 1.0, 1.0);
    expect_LPtoDP(hdc, MulDiv(1000 / 10, res_x, size_cx), -MulDiv(1000 / 10, res_y, size_cy));

    SetLastError(0xdeadbeef);
    ret = SetMapMode(hdc, MM_TEXT);
    ok(ret == MM_LOMETRIC, "expected MM_LOMETRIC, got %d\n", ret);

    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 1.0, 1.0);
    expect_LPtoDP(hdc, 1000, 1000);

    ret = SetGraphicsMode(hdc, GM_ADVANCED);
    if (!ret)
    {
        DeleteDC(hdc);
        skip("GM_ADVANCED is not supported on this platform\n");
        return;
    }

    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 1.0, 1.0);
    expect_LPtoDP(hdc, 1000, 1000);

    /* The transform must conform to (eM11 * eM22 != eM12 * eM21) requirement */
    xform.eM11 = 1.0f;
    xform.eM12 = 2.0f;
    xform.eM21 = 1.0f;
    xform.eM22 = 2.0f;
    xform.eDx = 0.0f;
    xform.eDy = 0.0f;
    ret = SetWorldTransform(hdc, &xform);
    ok(!ret ||
       broken(ret), /* NT4 */
       "SetWorldTransform should fail with an invalid xform\n");

    xform.eM11 = 20.0f;
    xform.eM12 = 0.0f;
    xform.eM21 = 0.0f;
    xform.eM22 = 20.0f;
    xform.eDx = 0.0f;
    xform.eDy = 0.0f;
    SetLastError(0xdeadbeef);
    ret = SetWorldTransform(hdc, &xform);
    ok(ret, "SetWorldTransform error %u\n", GetLastError());

    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 20.0, 20.0);
    expect_LPtoDP(hdc, 20000, 20000);

    SetLastError(0xdeadbeef);
    ret = SetMapMode(hdc, MM_LOMETRIC);
    ok(ret == MM_TEXT, "expected MM_TEXT, got %d\n", ret);

    expect_viewport_ext(hdc, res_x, -res_y);
    ok( GetWindowExtEx( hdc, &size ), "GetWindowExtEx failed\n" );
    ok( rough_match( size.cx, size_cx * 10 ) ||
        rough_match( size.cx, MulDiv( res_x, 254, dpi_x )),  /* Vista uses a more precise method */
        "expected cx %d or %d, got %d\n", size_cx * 10, MulDiv( res_x, 254, dpi_x ), size.cx );
    ok( rough_match( size.cy, size_cy * 10 ) ||
        rough_match( size.cy, MulDiv( res_y, 254, dpi_y )),  /* Vista uses a more precise method */
        "expected cy %d or %d, got %d\n", size_cy * 10, MulDiv( res_y, 254, dpi_y ), size.cy );
    expect_world_transform(hdc, 20.0, 20.0);
    expect_LPtoDP(hdc, MulDiv(20000, res_x, size.cx), -MulDiv(20000, res_y, size.cy));

    SetLastError(0xdeadbeef);
    ret = SetMapMode(hdc, MM_TEXT);
    ok(ret == MM_LOMETRIC, "expected MM_LOMETRIC, got %d\n", ret);

    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 20.0, 20.0);
    expect_LPtoDP(hdc, 20000, 20000);

    size.cx = 0xdeadbeef;
    size.cy = 0xdeadbeef;
    ret = SetViewportExtEx(hdc, -1, -1, &size);
    ok(ret, "SetViewportExtEx(-1, -1) failed\n");
    ok(size.cx == 1 && size.cy == 1, "expected 1,1 got %d,%d\n", size.cx, size.cy);
    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 20.0, 20.0);
    expect_LPtoDP(hdc, 20000, 20000);

    ret = SetMapMode(hdc, MM_ANISOTROPIC);
    ok(ret == MM_TEXT, "expected MM_TEXT, got %d\n", ret);

    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 20.0, 20.0);
    expect_LPtoDP(hdc, 20000, 20000);

    size.cx = 0xdeadbeef;
    size.cy = 0xdeadbeef;
    ret = SetViewportExtEx(hdc, -1, -1, &size);
    ok(ret, "SetViewportExtEx(-1, -1) failed\n");
    ok(size.cx == 1 && size.cy == 1, "expected 1,1 got %d,%d\n", size.cx, size.cy);
    expect_viewport_ext(hdc, -1, -1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 20.0, 20.0);
    expect_LPtoDP(hdc, -20000, -20000);

    ret = SetGraphicsMode(hdc, GM_COMPATIBLE);
    ok(ret, "SetGraphicsMode(GM_COMPATIBLE) should not fail if DC has't an identity transform\n");
    ret = GetGraphicsMode(hdc);
    ok(ret == GM_COMPATIBLE, "expected GM_COMPATIBLE, got %d\n", ret);

    expect_viewport_ext(hdc, -1, -1);
    expect_window_ext(hdc, 1, 1);
    expect_world_transform(hdc, 20.0, 20.0);
    expect_LPtoDP(hdc, -20000, -20000);

    DeleteDC(hdc);
}