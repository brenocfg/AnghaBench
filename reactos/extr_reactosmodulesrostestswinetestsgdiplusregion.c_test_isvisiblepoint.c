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
 int /*<<< orphan*/  GdipIsVisibleRegionPoint (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipIsVisibleRegionPointI (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipTranslateWorldTransform (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_isvisiblepoint(void)
{
    HDC hdc = GetDC(0);
    GpGraphics* graphics;
    GpRegion* region;
    GpPath* path;
    GpRectF rectf;
    GpStatus status;
    BOOL res;
    REAL x, y;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipCreateRegion(&region);
    expect(Ok, status);

    /* null parameters */
    status = GdipIsVisibleRegionPoint(NULL, 0, 0, graphics, &res);
    expect(InvalidParameter, status);
    status = GdipIsVisibleRegionPointI(NULL, 0, 0, graphics, &res);
    expect(InvalidParameter, status);

    status = GdipIsVisibleRegionPoint(region, 0, 0, NULL, &res);
    expect(Ok, status);
    status = GdipIsVisibleRegionPointI(region, 0, 0, NULL, &res);
    expect(Ok, status);

    status = GdipIsVisibleRegionPoint(region, 0, 0, graphics, NULL);
    expect(InvalidParameter, status);
    status = GdipIsVisibleRegionPointI(region, 0, 0, graphics, NULL);
    expect(InvalidParameter, status);

    /* infinite region */
    status = GdipIsInfiniteRegion(region, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Region should be infinite\n");

    x = 10;
    y = 10;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%d, %d) to be visible\n", (INT)x, (INT)y);

    x = -10;
    y = -10;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%d, %d) to be visible\n", (INT)x, (INT)y);

    /* rectangular region */
    rectf.X = 10;
    rectf.Y = 20;
    rectf.Width = 30;
    rectf.Height = 40;

    status = GdipCombineRegionRect(region, &rectf, CombineModeReplace);
    expect(Ok, status);

    x = 0;
    y = 0;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f) not to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d) not to be visible\n", (INT)x, (INT)y);

    x = 9;
    y = 19;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f) to be visible\n", x, y);

    x = 9.25;
    y = 19.25;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f) to be visible\n", x, y);

    x = 9.5;
    y = 19.5;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);

    x = 9.75;
    y = 19.75;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);

    x = 10;
    y = 20;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);

    x = 25;
    y = 40;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%d, %d) to be visible\n", (INT)x, (INT)y);

    x = 40;
    y = 60;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f) not to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d) not to be visible\n", (INT)x, (INT)y);

    /* translate into the center of the rectangle */
    status = GdipTranslateWorldTransform(graphics, 25, 40, MatrixOrderAppend);
    expect(Ok, status);

    /* native ignores the world transform, so treat these as if
     * no transform exists */
    x = -20;
    y = -30;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f) not to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d) not to be visible\n", (INT)x, (INT)y);

    x = 0;
    y = 0;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f) not to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d) not to be visible\n", (INT)x, (INT)y);

    x = 25;
    y = 40;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%d, %d) to be visible\n", (INT)x, (INT)y);

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

    x = 11;
    y = 21;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f) not to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d) not to be visible\n", (INT)x, (INT)y);

    x = 25;
    y = 40;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == TRUE, "Expected (%d, %d) to be visible\n", (INT)x, (INT)y);

    x = 40;
    y = 60;
    status = GdipIsVisibleRegionPoint(region, x, y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%.2f, %.2f) not to be visible\n", x, y);
    status = GdipIsVisibleRegionPointI(region, (INT)x, (INT)y, graphics, &res);
    expect(Ok, status);
    ok(res == FALSE, "Expected (%d, %d) not to be visible\n", (INT)x, (INT)y);

    GdipDeletePath(path);

    GdipDeleteRegion(region);
    GdipDeleteGraphics(graphics);
    ReleaseDC(0, hdc);
}