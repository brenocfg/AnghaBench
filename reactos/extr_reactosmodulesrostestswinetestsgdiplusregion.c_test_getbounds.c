#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double X; double Y; double Height; double Width; } ;
typedef  double REAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  double GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 double GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 double GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 double GdipCreateRegion (int /*<<< orphan*/ **) ; 
 double GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 double GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 double GdipGetRegionBounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 double GdipScaleWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 double GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetPageScale (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  GdipSetPageUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 double InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 double Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnitInch ; 
 int /*<<< orphan*/  ok (int,char*,double,...) ; 

__attribute__((used)) static void test_getbounds(void)
{
    GpRegion *region;
    GpGraphics *graphics;
    GpStatus status;
    GpRectF rectf;
    HDC hdc = GetDC(0);

    status = GdipCreateFromHDC(hdc, &graphics);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCreateRegion(&region);
    ok(status == Ok, "status %08x\n", status);

    /* NULL */
    status = GdipGetRegionBounds(NULL, NULL, NULL);
    ok(status == InvalidParameter, "status %08x\n", status);
    status = GdipGetRegionBounds(region, NULL, NULL);
    ok(status == InvalidParameter, "status %08x\n", status);
    status = GdipGetRegionBounds(region, graphics, NULL);
    ok(status == InvalidParameter, "status %08x\n", status);
    /* infinite */
    rectf.X = rectf.Y = 0.0;
    rectf.Height = rectf.Width = 100.0;
    status = GdipGetRegionBounds(region, graphics, &rectf);
    ok(status == Ok, "status %08x\n", status);
    ok(rectf.X == -(REAL)(1 << 22), "Expected X = %.2f, got %.2f\n", -(REAL)(1 << 22), rectf.X);
    ok(rectf.Y == -(REAL)(1 << 22), "Expected Y = %.2f, got %.2f\n", -(REAL)(1 << 22), rectf.Y);
    ok(rectf.Width  == (REAL)(1 << 23), "Expected width = %.2f, got %.2f\n", (REAL)(1 << 23), rectf.Width);
    ok(rectf.Height == (REAL)(1 << 23), "Expected height = %.2f, got %.2f\n",(REAL)(1 << 23), rectf.Height);
    /* empty */
    rectf.X = rectf.Y = 0.0;
    rectf.Height = rectf.Width = 100.0;
    status = GdipSetEmpty(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionBounds(region, graphics, &rectf);
    ok(status == Ok, "status %08x\n", status);
    ok(rectf.X == 0.0, "Expected X = 0.0, got %.2f\n", rectf.X);
    ok(rectf.Y == 0.0, "Expected Y = 0.0, got %.2f\n", rectf.Y);
    ok(rectf.Width  == 0.0, "Expected width = 0.0, got %.2f\n", rectf.Width);
    ok(rectf.Height == 0.0, "Expected height = 0.0, got %.2f\n", rectf.Height);
    /* rect */
    rectf.X = 10.0; rectf.Y = 0.0;
    rectf.Width = rectf.Height = 100.0;
    status = GdipCombineRegionRect(region, &rectf, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    rectf.X = rectf.Y = 0.0;
    rectf.Height = rectf.Width = 0.0;
    status = GdipGetRegionBounds(region, graphics, &rectf);
    ok(status == Ok, "status %08x\n", status);
    ok(rectf.X == 10.0, "Expected X = 0.0, got %.2f\n", rectf.X);
    ok(rectf.Y == 0.0, "Expected Y = 0.0, got %.2f\n", rectf.Y);
    ok(rectf.Width  == 100.0, "Expected width = 0.0, got %.2f\n", rectf.Width);
    ok(rectf.Height == 100.0, "Expected height = 0.0, got %.2f\n", rectf.Height);

    /* the world and page transforms are ignored */
    status = GdipScaleWorldTransform(graphics, 2.0, 2.0, MatrixOrderPrepend);
    ok(status == Ok, "status %08x\n", status);
    GdipSetPageUnit(graphics, UnitInch);
    GdipSetPageScale(graphics, 2.0);
    status = GdipGetRegionBounds(region, graphics, &rectf);
    ok(status == Ok, "status %08x\n", status);
    ok(rectf.X == 10.0, "Expected X = 0.0, got %.2f\n", rectf.X);
    ok(rectf.Y == 0.0, "Expected Y = 0.0, got %.2f\n", rectf.Y);
    ok(rectf.Width  == 100.0, "Expected width = 0.0, got %.2f\n", rectf.Width);

    rectf.X = 10.0; rectf.Y = 0.0;
    rectf.Width = rectf.Height = 100.0;
    status = GdipCombineRegionRect(region, &rectf, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    rectf.X = rectf.Y = 0.0;
    rectf.Height = rectf.Width = 0.0;
    status = GdipGetRegionBounds(region, graphics, &rectf);
    ok(status == Ok, "status %08x\n", status);
    ok(rectf.X == 10.0, "Expected X = 0.0, got %.2f\n", rectf.X);
    ok(rectf.Y == 0.0, "Expected Y = 0.0, got %.2f\n", rectf.Y);
    ok(rectf.Width  == 100.0, "Expected width = 0.0, got %.2f\n", rectf.Width);
    ok(rectf.Height == 100.0, "Expected height = 0.0, got %.2f\n", rectf.Height);

    status = GdipDeleteRegion(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeleteGraphics(graphics);
    ok(status == Ok, "status %08x\n", status);
    ReleaseDC(0, hdc);
}