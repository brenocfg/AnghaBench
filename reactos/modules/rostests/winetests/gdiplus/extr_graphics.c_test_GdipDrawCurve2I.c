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
struct TYPE_3__ {int X; int Y; } ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpPoint ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePen1 (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawCurve2I (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  OutOfMemory ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_GdipDrawCurve2I(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpPen *pen = NULL;
    HDC hdc = GetDC( hwnd );
    GpPoint points[3];

    points[0].X = 0;
    points[0].Y = 0;

    points[1].X = 40;
    points[1].Y = 20;

    points[2].X = 10;
    points[2].Y = 40;

    /* make a graphics object and pen object */
    ok(hdc != NULL, "Expected HDC to be initialized\n");

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    status = GdipCreatePen1((ARGB)0xffff00ff, 10.0f, UnitPixel, &pen);
    expect(Ok, status);
    ok(pen != NULL, "Expected pen to be initialized\n");

    /* InvalidParameter cases: null graphics, null pen */
    status = GdipDrawCurve2I(NULL, NULL, points, 3, 1);
    expect(InvalidParameter, status);

    status = GdipDrawCurve2I(graphics, NULL, points, 3, 1);
    expect(InvalidParameter, status);

    status = GdipDrawCurve2I(NULL, pen, points, 3, 1);
    expect(InvalidParameter, status);

    /* InvalidParameter cases: invalid count */
    status = GdipDrawCurve2I(graphics, pen, points, -1, 1);
    expect(OutOfMemory, status);

    status = GdipDrawCurve2I(graphics, pen, points, 0, 1);
    expect(InvalidParameter, status);

    status = GdipDrawCurve2I(graphics, pen, points, 1, 1);
    expect(InvalidParameter, status);

    /* Valid test cases */
    status = GdipDrawCurve2I(graphics, pen, points, 2, 1);
    expect(Ok, status);

    status = GdipDrawCurve2I(graphics, pen, points, 3, 2);
    expect(Ok, status);

    status = GdipDrawCurve2I(graphics, pen, points, 3, -2);
    expect(Ok, status);

    status = GdipDrawCurve2I(graphics, pen, points, 3, 0);
    expect(Ok, status);

    GdipDeletePen(pen);
    GdipDeleteGraphics(graphics);

    ReleaseDC(hwnd, hdc);
}