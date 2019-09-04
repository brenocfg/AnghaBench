#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  points ;
struct TYPE_9__ {double member_0; double member_1; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_8__ {double X; double Y; double Width; double Height; } ;
typedef  double REAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GraphicsContainer ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpPointF ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  CoordinateSpaceDevice ; 
 int /*<<< orphan*/  CoordinateSpaceWorld ; 
 int /*<<< orphan*/  GdipBeginContainer (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipEndContainer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipGetDpiX (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  GdipGetDpiY (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  GdipResetWorldTransform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipScaleWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetPageUnit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GdipTransformPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UnitDisplay ; 
 int UnitInch ; 
 int UnitMillimeter ; 
 int UnitPixel ; 
 int UnitWorld ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__ const*,int) ; 

__attribute__((used)) static void test_container_rects(void)
{
    GpStatus status;
    GpGraphics *graphics;
    HDC hdc = GetDC( hwnd );
    GpRectF dstrect, srcrect;
    GraphicsContainer state;
    static const GpPointF test_points[3] = {{0.0,0.0}, {1.0,0.0}, {0.0,1.0}};
    GpPointF points[3];
    REAL dpix, dpiy;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    dstrect.X = 0.0;
    dstrect.Y = 0.0;
    dstrect.Width = 1.0;
    dstrect.Height = 1.0;
    srcrect = dstrect;

    status = GdipGetDpiX(graphics, &dpix);
    expect(Ok, status);

    status = GdipGetDpiY(graphics, &dpiy);
    expect(Ok, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitWorld, &state);
    expect(InvalidParameter, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitDisplay, &state);
    expect(InvalidParameter, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitMillimeter+1, &state);
    expect(InvalidParameter, status);

    status = GdipBeginContainer(NULL, &dstrect, &srcrect, UnitPixel, &state);
    expect(InvalidParameter, status);

    status = GdipBeginContainer(graphics, NULL, &srcrect, UnitPixel, &state);
    expect(InvalidParameter, status);

    status = GdipBeginContainer(graphics, &dstrect, NULL, UnitPixel, &state);
    expect(InvalidParameter, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, -1, &state);
    expect(InvalidParameter, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitPixel, NULL);
    expect(InvalidParameter, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitPixel, &state);
    expect(Ok, status);

    memcpy(points, test_points, sizeof(points));
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, points, 3);
    expect(Ok, status);
    expectf(0.0, points[0].X);
    expectf(0.0, points[0].Y);
    expectf(1.0, points[1].X);
    expectf(0.0, points[1].Y);
    expectf(0.0, points[2].X);
    expectf(1.0, points[2].Y);

    status = GdipEndContainer(graphics, state);
    expect(Ok, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitInch, &state);
    expect(Ok, status);

    memcpy(points, test_points, sizeof(points));
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, points, 3);
    expect(Ok, status);
    expectf(0.0, points[0].X);
    expectf(0.0, points[0].Y);
    expectf(1.0/dpix, points[1].X);
    expectf(0.0, points[1].Y);
    expectf(0.0, points[2].X);
    expectf(1.0/dpiy, points[2].Y);

    status = GdipEndContainer(graphics, state);
    expect(Ok, status);

    status = GdipScaleWorldTransform(graphics, 2.0, 2.0, MatrixOrderPrepend);
    expect(Ok, status);

    dstrect.X = 1.0;
    dstrect.Height = 3.0;
    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitPixel, &state);
    expect(Ok, status);

    memcpy(points, test_points, sizeof(points));
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, points, 3);
    expect(Ok, status);
    expectf(2.0, points[0].X);
    expectf(0.0, points[0].Y);
    expectf(4.0, points[1].X);
    expectf(0.0, points[1].Y);
    expectf(2.0, points[2].X);
    expectf(6.0, points[2].Y);

    status = GdipEndContainer(graphics, state);
    expect(Ok, status);

    memcpy(points, test_points, sizeof(points));
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, points, 3);
    expect(Ok, status);
    expectf(0.0, points[0].X);
    expectf(0.0, points[0].Y);
    expectf(2.0, points[1].X);
    expectf(0.0, points[1].Y);
    expectf(0.0, points[2].X);
    expectf(2.0, points[2].Y);

    status = GdipResetWorldTransform(graphics);
    expect(Ok, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitInch, &state);
    expect(Ok, status);

    memcpy(points, test_points, sizeof(points));
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, points, 3);
    expect(Ok, status);
    expectf(1.0, points[0].X);
    expectf(0.0, points[0].Y);
    expectf((dpix+1.0)/dpix, points[1].X);
    expectf(0.0, points[1].Y);
    expectf(1.0, points[2].X);
    expectf(3.0/dpiy, points[2].Y);

    status = GdipEndContainer(graphics, state);
    expect(Ok, status);

    status = GdipSetPageUnit(graphics, UnitInch);
    expect(Ok, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitPixel, &state);
    expect(Ok, status);

    memcpy(points, test_points, sizeof(points));
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, points, 3);
    expect(Ok, status);
    expectf(dpix, points[0].X);
    expectf(0.0, points[0].Y);
    expectf(dpix*2, points[1].X);
    expectf(0.0, points[1].Y);
    expectf(dpix, points[2].X);
    expectf(dpiy*3, points[2].Y);

    status = GdipEndContainer(graphics, state);
    expect(Ok, status);

    status = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitInch, &state);
    expect(Ok, status);

    memcpy(points, test_points, sizeof(points));
    status = GdipTransformPoints(graphics, CoordinateSpaceDevice, CoordinateSpaceWorld, points, 3);
    expect(Ok, status);
    expectf(dpix, points[0].X);
    expectf(0.0, points[0].Y);
    expectf(dpix+1.0, points[1].X);
    expectf(0.0, points[1].Y);
    expectf(dpix, points[2].X);
    expectf(3.0, points[2].Y);

    status = GdipEndContainer(graphics, state);
    expect(Ok, status);

    GdipDeleteGraphics(graphics);

    ReleaseDC(hwnd, hdc);
}