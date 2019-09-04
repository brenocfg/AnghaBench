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
struct TYPE_3__ {int X; int Y; int Width; int Height; } ;
typedef  double REAL ;
typedef  double INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeIntersect ; 
 int /*<<< orphan*/  CombineModeReplace ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathEllipse (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  GdipCombineRegionPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsInfiniteRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipIsVisibleRegionRect (int /*<<< orphan*/ *,double,double,double,double,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipIsVisibleRegionRectI (int /*<<< orphan*/ *,double,double,double,double,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipTranslateWorldTransform (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_isvisiblerect(void)
{
    HDC hdc = GetDC(0);
    GpGraphics* graphics;
    GpRegion* region;
    GpPath* path;
    GpRectF rectf;
    GpStatus status;
    BOOL res;
    REAL x, y, w, h;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipCreateRegion(&region);
    expect(Ok, status);

    /* null parameters */
    status = GdipIsVisibleRegionRect(NULL, 0, 0, 0, 0, graphics, &res);
    expect(InvalidParameter, status);
    status = GdipIsVisibleRegionRectI(NULL, 0, 0, 0, 0, graphics, &res);
    expect(InvalidParameter, status);

    status = GdipIsVisibleRegionRect(region, 0, 0, 0, 0, NULL, &res);
    expect(Ok, status);
    status = GdipIsVisibleRegionRectI(region, 0, 0, 0, 0, NULL, &res);
    expect(Ok, status);

    status = GdipIsVisibleRegionRect(region, 0, 0, 0, 0, graphics, NULL);
    expect(InvalidParameter, status);
    status = GdipIsVisibleRegionRectI(region, 0, 0, 0, 0, graphics, NULL);
    expect(InvalidParameter, status);

    /* infinite region */
    status = GdipIsInfiniteRegion(region, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Region should be infinite\n");

    x = 10; w = 10;
    y = 10; h = 10;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);

    x = -10; w = 5;
    y = -10; h = 5;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);

    /* rectangular region */
    rectf.X = 10;
    rectf.Y = 20;
    rectf.Width = 30;
    rectf.Height = 40;

    status = GdipCombineRegionRect(region, &rectf, CombineModeIntersect);
    expect(Ok, status);

    /* entirely within the region */
    x = 11; w = 10;
    y = 12; h = 10;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);
    status = GdipIsVisibleRegionRectI(region, (INT)x, (INT)y, (INT)w, (INT)h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%d, %d, %d, %d) to be visible\n", (INT)x, (INT)y, (INT)w, (INT)h);

    /* entirely outside of the region */
    x = 0; w = 5;
    y = 0; h = 5;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, w, h);
    status = GdipIsVisibleRegionRectI(region, (INT)x, (INT)y, (INT)w, (INT)h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d, %d, %d) not to be visible\n", (INT)x, (INT)y, (INT)w, (INT)h);

    /* corner cases */
    x = 0; w = 10;
    y = 0; h = 20;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, w, h);

    x = 0; w = 10.25;
    y = 0; h = 20.25;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);

    x = 39; w = 10;
    y = 59; h = 10;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);

    x = 39.25; w = 10;
    y = 59.25; h = 10;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, w, h);

    /* corners outside, but some intersection */
    x = 0; w = 100;
    y = 0; h = 100;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);

    x = 0; w = 100;
    y = 0; h = 40;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);

    x = 0; w = 25;
    y = 0; h = 100;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);

    /* translate into the center of the rectangle */
    status = GdipTranslateWorldTransform(graphics, 25, 40, MatrixOrderAppend);
    expect(Ok, status);

    /* native ignores the world transform, so treat these as if
     * no transform exists */
    x = 0; w = 5;
    y = 0; h = 5;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, w, h);
    status = GdipIsVisibleRegionRectI(region, (INT)x, (INT)y, (INT)w, (INT)h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d, %d, %d) not to be visible\n", (INT)x, (INT)y, (INT)w, (INT)h);

    x = 11; w = 10;
    y = 12; h = 10;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);
    status = GdipIsVisibleRegionRectI(region, (INT)x, (INT)y, (INT)w, (INT)h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%d, %d, %d, %d) to be visible\n", (INT)x, (INT)y, (INT)w, (INT)h);

    /* translate back to origin */
    status = GdipTranslateWorldTransform(graphics, -25, -40, MatrixOrderAppend);
    expect(Ok, status);

    /* region from path */
    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);

    status = GdipAddPathEllipse(path, 10, 20, 30, 40);
    expect(Ok, status);

    status = GdipCombineRegionPath(region, path, CombineModeReplace);
    expect(Ok, status);

    x = 0; w = 12;
    y = 0; h = 22;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, w, h);
    status = GdipIsVisibleRegionRectI(region, (INT)x, (INT)y, (INT)w, (INT)h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d, %d, %d) not to be visible\n", (INT)x, (INT)y, (INT)w, (INT)h);

    x = 0; w = 25;
    y = 0; h = 40;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);
    status = GdipIsVisibleRegionRectI(region, (INT)x, (INT)y, (INT)w, (INT)h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%d, %d, %d, %d) to be visible\n", (INT)x, (INT)y, (INT)w, (INT)h);

    x = 38; w = 10;
    y = 55; h = 10;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, w, h);
    status = GdipIsVisibleRegionRectI(region, (INT)x, (INT)y, (INT)w, (INT)h, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d, %d, %d) not to be visible\n", (INT)x, (INT)y, (INT)w, (INT)h);

    x = 0; w = 100;
    y = 0; h = 100;
    status = GdipIsVisibleRegionRect(region, x, y, w, h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, w, h);
    status = GdipIsVisibleRegionRectI(region, (INT)x, (INT)y, (INT)w, (INT)h, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%d, %d, %d, %d) to be visible\n", (INT)x, (INT)y, (INT)w, (INT)h);

    GdipDeletePath(path);

    GdipDeleteRegion(region);
    GdipDeleteGraphics(graphics);
    ReleaseDC(0, hdc);
}