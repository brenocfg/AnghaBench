#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int X; int Y; } ;
struct TYPE_5__ {double X; double Y; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  TYPE_2__ GpPoint ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int CoordinateSpaceDevice ; 
 int CoordinateSpacePage ; 
 int CoordinateSpaceWorld ; 
 int GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int GdipSetPageScale (int /*<<< orphan*/ *,double) ; 
 int GdipSetPageUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GdipTransformPoints (int /*<<< orphan*/ *,int,int,TYPE_1__*,int) ; 
 int GdipTransformPointsI (int /*<<< orphan*/ *,int,int,TYPE_2__*,int) ; 
 int GdipTranslateWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,double) ; 
 int /*<<< orphan*/  hwnd ; 

__attribute__((used)) static void test_transformpoints(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC( hwnd );
    GpPointF ptf[2];
    GpPoint pt[2];

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    /* NULL arguments */
    status = GdipTransformPoints(NULL, CoordinateSpacePage, CoordinateSpaceWorld, NULL, 0);
    expect(InvalidParameter, status);
    status = GdipTransformPoints(graphics, CoordinateSpacePage, CoordinateSpaceWorld, NULL, 0);
    expect(InvalidParameter, status);
    status = GdipTransformPoints(graphics, CoordinateSpacePage, CoordinateSpaceWorld, ptf, 0);
    expect(InvalidParameter, status);
    status = GdipTransformPoints(graphics, CoordinateSpacePage, CoordinateSpaceWorld, ptf, -1);
    expect(InvalidParameter, status);

    status = GdipTransformPoints(graphics, CoordinateSpaceDevice+1, CoordinateSpaceWorld, ptf, 2);
    expect(InvalidParameter, status);
    status = GdipTransformPoints(graphics, -1, CoordinateSpaceWorld, ptf, 2);
    expect(InvalidParameter, status);
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceDevice+1, ptf, 2);
    expect(InvalidParameter, status);
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, -1, ptf, 2);
    expect(InvalidParameter, status);

    ptf[0].X = 1.0;
    ptf[0].Y = 0.0;
    ptf[1].X = 0.0;
    ptf[1].Y = 1.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, ptf, 2);
    expect(Ok, status);
    expectf(1.0, ptf[0].X);
    expectf(0.0, ptf[0].Y);
    expectf(0.0, ptf[1].X);
    expectf(1.0, ptf[1].Y);

    status = GdipTranslateWorldTransform(graphics, 5.0, 5.0, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipSetPageUnit(graphics, UnitPixel);
    expect(Ok, status);
    status = GdipSetPageScale(graphics, 3.0);
    expect(Ok, status);

    ptf[0].X = 1.0;
    ptf[0].Y = 0.0;
    ptf[1].X = 0.0;
    ptf[1].Y = 1.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, ptf, 2);
    expect(Ok, status);
    expectf(18.0, ptf[0].X);
    expectf(15.0, ptf[0].Y);
    expectf(15.0, ptf[1].X);
    expectf(18.0, ptf[1].Y);

    ptf[0].X = 1.0;
    ptf[0].Y = 0.0;
    ptf[1].X = 0.0;
    ptf[1].Y = 1.0;
    status = GdipTransformPoints(graphics, CoordinateSpacePage, CoordinateSpaceWorld, ptf, 2);
    expect(Ok, status);
    expectf(6.0, ptf[0].X);
    expectf(5.0, ptf[0].Y);
    expectf(5.0, ptf[1].X);
    expectf(6.0, ptf[1].Y);

    ptf[0].X = 1.0;
    ptf[0].Y = 0.0;
    ptf[1].X = 0.0;
    ptf[1].Y = 1.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpacePage, ptf, 2);
    expect(Ok, status);
    expectf(3.0, ptf[0].X);
    expectf(0.0, ptf[0].Y);
    expectf(0.0, ptf[1].X);
    expectf(3.0, ptf[1].Y);

    ptf[0].X = 18.0;
    ptf[0].Y = 15.0;
    ptf[1].X = 15.0;
    ptf[1].Y = 18.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    expectf(1.0, ptf[0].X);
    expectf(0.0, ptf[0].Y);
    expectf(0.0, ptf[1].X);
    expectf(1.0, ptf[1].Y);

    ptf[0].X = 6.0;
    ptf[0].Y = 5.0;
    ptf[1].X = 5.0;
    ptf[1].Y = 6.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpacePage, ptf, 2);
    expect(Ok, status);
    expectf(1.0, ptf[0].X);
    expectf(0.0, ptf[0].Y);
    expectf(0.0, ptf[1].X);
    expectf(1.0, ptf[1].Y);

    ptf[0].X = 3.0;
    ptf[0].Y = 0.0;
    ptf[1].X = 0.0;
    ptf[1].Y = 3.0;
    status = GdipTransformPoints(graphics, CoordinateSpacePage, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    expectf(1.0, ptf[0].X);
    expectf(0.0, ptf[0].Y);
    expectf(0.0, ptf[1].X);
    expectf(1.0, ptf[1].Y);

    pt[0].X = 1;
    pt[0].Y = 0;
    pt[1].X = 0;
    pt[1].Y = 1;
    status = GdipTransformPointsI(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, pt, 2);
    expect(Ok, status);
    expect(18, pt[0].X);
    expect(15, pt[0].Y);
    expect(15, pt[1].X);
    expect(18, pt[1].Y);

    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);
}