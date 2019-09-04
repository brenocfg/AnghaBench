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
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateSolidFill (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFillClosedCurve2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_GdipFillClosedCurve2(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpSolidFill *brush = NULL;
    HDC hdc = GetDC( hwnd );
    GpPointF points[3];

    points[0].X = 0;
    points[0].Y = 0;

    points[1].X = 40;
    points[1].Y = 20;

    points[2].X = 10;
    points[2].Y = 40;

    /* make a graphics object and brush object */
    ok(hdc != NULL, "Expected HDC to be initialized\n");

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    GdipCreateSolidFill((ARGB)0xdeadbeef, &brush);

    /* InvalidParameter cases: null graphics, null brush, null points */
    status = GdipFillClosedCurve2(NULL, NULL, NULL, 3, 0.5, FillModeAlternate);
    expect(InvalidParameter, status);

    status = GdipFillClosedCurve2(graphics, NULL, NULL, 3, 0.5, FillModeAlternate);
    expect(InvalidParameter, status);

    status = GdipFillClosedCurve2(NULL, (GpBrush*)brush, NULL, 3, 0.5, FillModeAlternate);
    expect(InvalidParameter, status);

    status = GdipFillClosedCurve2(NULL, NULL, points, 3, 0.5, FillModeAlternate);
    expect(InvalidParameter, status);

    status = GdipFillClosedCurve2(graphics, (GpBrush*)brush, NULL, 3, 0.5, FillModeAlternate);
    expect(InvalidParameter, status);

    status = GdipFillClosedCurve2(graphics, NULL, points, 3, 0.5, FillModeAlternate);
    expect(InvalidParameter, status);

    status = GdipFillClosedCurve2(NULL, (GpBrush*)brush, points, 3, 0.5, FillModeAlternate);
    expect(InvalidParameter, status);

    /* InvalidParameter cases: invalid count */
    status = GdipFillClosedCurve2(graphics, (GpBrush*)brush, points, -1, 0.5, FillModeAlternate);
    expect(InvalidParameter, status);

    status = GdipFillClosedCurve2(graphics, (GpBrush*)brush, points, 0, 0.5, FillModeAlternate);
    expect(InvalidParameter, status);

    /* Valid test cases */
    status = GdipFillClosedCurve2(graphics, (GpBrush*)brush, points, 1, 0.5, FillModeAlternate);
    expect(Ok, status);

    status = GdipFillClosedCurve2(graphics, (GpBrush*)brush, points, 2, 0.5, FillModeAlternate);
    expect(Ok, status);

    status = GdipFillClosedCurve2(graphics, (GpBrush*)brush, points, 3, 0.5, FillModeAlternate);
    expect(Ok, status);

    GdipDeleteGraphics(graphics);
    GdipDeleteBrush((GpBrush*)brush);

    ReleaseDC(hwnd, hdc);
}