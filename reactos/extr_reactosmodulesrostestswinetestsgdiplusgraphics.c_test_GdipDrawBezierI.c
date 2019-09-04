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
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePen1 (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawBezierI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_GdipDrawBezierI(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpPen *pen = NULL;
    HDC hdc = GetDC( hwnd );

    /* make a graphics object and pen object */
    ok(hdc != NULL, "Expected HDC to be initialized\n");

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    status = GdipCreatePen1((ARGB)0xffff00ff, 10.0f, UnitPixel, &pen);
    expect(Ok, status);
    ok(pen != NULL, "Expected pen to be initialized\n");

    /* InvalidParameter cases: null graphics, null pen */
    status = GdipDrawBezierI(NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0);
    expect(InvalidParameter, status);

    status = GdipDrawBezierI(graphics, NULL, 0, 0, 0, 0, 0, 0, 0, 0);
    expect(InvalidParameter, status);

    status = GdipDrawBezierI(NULL, pen, 0, 0, 0, 0, 0, 0, 0, 0);
    expect(InvalidParameter, status);

    /* successful case */
    status = GdipDrawBezierI(graphics, pen, 0, 0, 0, 0, 0, 0, 0, 0);
    expect(Ok, status);

    GdipDeletePen(pen);
    GdipDeleteGraphics(graphics);

    ReleaseDC(hwnd, hdc);
}