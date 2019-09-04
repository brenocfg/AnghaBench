#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {double X; double Y; } ;
struct TYPE_9__ {double X; double Y; double Width; double Height; } ;
struct TYPE_8__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpUnit ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_2__ GpRectF ;
typedef  TYPE_3__ GpPointF ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int COMPLEXREGION ; 
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  CombineModeUnion ; 
 int /*<<< orphan*/  CoordinateSpaceDevice ; 
 int /*<<< orphan*/  CoordinateSpaceWorld ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetClip (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPageUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetRegionHRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipRotateMatrix (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipScaleMatrix (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetPageScale (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  GdipSetPageUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTransformPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipTranslateMatrix (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int GetRgnBox (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int /*<<< orphan*/  Ok ; 
 int SIMPLEREGION ; 
 int /*<<< orphan*/  UnitDisplay ; 
 int /*<<< orphan*/  UnitInch ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  UnitPoint ; 
 int broken (int) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,double) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void test_clipping_2(void)
{

    HDC hdc;
    GpStatus status;
    GpGraphics *graphics;
    GpRegion *region;
    GpMatrix *matrix;
    GpRectF rect;
    GpPointF ptf[4];
    GpUnit unit;
    HRGN hrgn;
    int ret;
    RECT rc;

    hdc = CreateCompatibleDC(0);
    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipGetPageUnit(graphics, &unit);
    expect(Ok, status);
    expect(UnitDisplay, unit);

    GdipSetPageUnit(graphics, UnitInch);

    status = GdipCreateRegion(&region);
    expect(Ok, status);
    status = GdipSetEmpty(region);
    expect(Ok, status);
    rect.X = rect.Y = 100.0;
    rect.Width = rect.Height = 100.0;
    status = GdipCombineRegionRect(region, &rect, CombineModeUnion);
    expect(Ok, status);
    status = GdipSetClipRegion(graphics, region, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);
    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 9600 && rc.top == 9600 && rc.right == 19200 && rc.bottom == 19200,
       "expected 9600,9600-19200,19200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 9600.0;
    ptf[0].Y = 9600.0;
    ptf[1].X = 19200.0;
    ptf[1].Y = 19200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    expectf(100.0, ptf[0].X);
    expectf(100.0, ptf[0].Y);
    expectf(200.0, ptf[1].X);
    expectf(200.0, ptf[1].X);

    GdipSetPageUnit(graphics, UnitPoint);

    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 7200 && rc.top == 7200 && rc.right == 14400 && rc.bottom == 14400) ||
       broken(rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200) /* before Win7 */,
       "expected 7200,7200-14400,14400, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);
    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 9600 && rc.top == 9600 && rc.right == 19200 && rc.bottom == 19200) ||
       broken(rc.left == 134 && rc.top == 134 && rc.right == 267 && rc.bottom == 267) /* before Win7 */,
       "expected 9600,9600-19200,19200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 9600.0;
    ptf[0].Y = 9600.0;
    ptf[1].X = 19200.0;
    ptf[1].Y = 19200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    if (fabs(ptf[0].X - 7200.0) < 0.001)
        ok(ptf[0].X == 7200.0 && ptf[0].Y == 7200.0 && ptf[1].X == 14400.0 && ptf[1].Y == 14400.0,
           "expected 7200.0,7200.0-14400.0,14400.0, got %f,%f-%f,%f\n", ptf[0].X, ptf[0].Y, ptf[1].X, ptf[1].Y);
    else /* before Win7 */
    {
        ok(broken(fabs(ptf[0].X - 100.0) < 0.001), "expected 100.0, got %f\n", ptf[0].X);
        ok(broken(fabs(ptf[0].Y - 100.0) < 0.001), "expected 100.0, got %f\n", ptf[0].Y);
        ok(broken(fabs(ptf[1].X - 200.0) < 0.001), "expected 200.0, got %f\n", ptf[1].X);
        ok(broken(fabs(ptf[1].Y - 200.0) < 0.001), "expected 200.0, got %f\n", ptf[1].Y);
    }

    GdipDeleteRegion(region);

    GdipSetPageUnit(graphics, UnitPixel);

    status = GdipCreateRegion(&region);
    expect(Ok, status);
    status = GdipSetEmpty(region);
    expect(Ok, status);
    rect.X = rect.Y = 100.0;
    rect.Width = rect.Height = 100.0;
    status = GdipCombineRegionRect(region, &rect, CombineModeUnion);
    expect(Ok, status);
    status = GdipSetClipRegion(graphics, region, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200) ||
       broken(rc.left == 2 && rc.top == 2 && rc.right == 3 && rc.bottom == 3) /* before Win7 */,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);
    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200) ||
       broken(rc.left == 2 && rc.top == 2 && rc.right == 3 && rc.bottom == 3) /* before Win7 */,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 100.0;
    ptf[0].Y = 100.0;
    ptf[1].X = 200.0;
    ptf[1].Y = 200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    if (fabs(ptf[0].X - 100.0) < 0.001)
        ok(ptf[0].X == 100.0 && ptf[0].Y == 100.0 && ptf[1].X == 200.0 && ptf[1].Y == 200.0,
           "expected 100.0,100.0-200.0,200.0, got %f,%f-%f,%f\n", ptf[0].X, ptf[0].Y, ptf[1].X, ptf[1].Y);
    else /* before Win7 */
    {
        ok(broken(fabs(ptf[0].X - 1.041667) < 0.001), "expected 1.041667, got %f\n", ptf[0].X);
        ok(broken(fabs(ptf[0].Y - 1.041667) < 0.001), "expected 1.041667, got %f\n", ptf[0].Y);
        ok(broken(fabs(ptf[1].X - 2.083333) < 0.001), "expected 2.083333, got %f\n", ptf[1].X);
        ok(broken(fabs(ptf[1].Y - 2.083333) < 0.001), "expected 2.083333, got %f\n", ptf[1].Y);
    }

    GdipSetPageUnit(graphics, UnitPoint);

    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 75 && rc.top == 75 && rc.right == 150 && rc.bottom == 150) ||
       broken(rc.left == 2 && rc.top == 2 && rc.right == 3 && rc.bottom == 3) /* before Win7 */,
       "expected 75,75-150,150, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);
    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200) ||
       broken(rc.left == 2 && rc.top == 2 && rc.right == 3 && rc.bottom == 3) /* before Win7 */,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 100.0;
    ptf[0].Y = 100.0;
    ptf[1].X = 200.0;
    ptf[1].Y = 200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    if (fabs(ptf[0].X - 75.0) < 0.001)
        ok(ptf[0].X == 75.0 && ptf[0].Y == 75.0 && ptf[1].X == 150.0 && ptf[1].Y == 150.0,
           "expected 75.0,75.0-150.0,150.0, got %f,%f-%f,%f\n", ptf[0].X, ptf[0].Y, ptf[1].X, ptf[1].Y);
    else /* before Win7 */
    {
        ok(broken(fabs(ptf[0].X - 1.041667) < 0.001), "expected 1.041667, got %f\n", ptf[0].X);
        ok(broken(fabs(ptf[0].Y - 1.041667) < 0.001), "expected 1.041667, got %f\n", ptf[0].Y);
        ok(broken(fabs(ptf[1].X - 2.083333) < 0.001), "expected 2.083333, got %f\n", ptf[1].X);
        ok(broken(fabs(ptf[1].Y - 2.083333) < 0.001), "expected 2.083333, got %f\n", ptf[1].Y);
    }

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);
    status = GdipTranslateMatrix(matrix, 10.0, 10.0, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipSetWorldTransform(graphics, matrix);
    expect(Ok, status);
    GdipDeleteMatrix(matrix);

    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 65 && rc.top == 65 && rc.right == 140 && rc.bottom == 140,
       "expected 65,65-140,140, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);
    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 100.0;
    ptf[0].Y = 100.0;
    ptf[1].X = 200.0;
    ptf[1].Y = 200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    expectf(65.0, ptf[0].X);
    expectf(65.0, ptf[0].Y);
    expectf(140.0, ptf[1].X);
    expectf(140.0, ptf[1].X);

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);
    status = GdipScaleMatrix(matrix, 0.25, 0.5, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipSetWorldTransform(graphics, matrix);
    expect(Ok, status);
    GdipDeleteMatrix(matrix);

    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 300 && rc.top == 150 && rc.right == 600 && rc.bottom == 300,
       "expected 300,150-600,300, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);
    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 100.0;
    ptf[0].Y = 100.0;
    ptf[1].X = 200.0;
    ptf[1].Y = 200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    expectf(300.0, ptf[0].X);
    expectf(150.0, ptf[0].Y);
    expectf(600.0, ptf[1].X);
    expectf(300.0, ptf[1].Y);

    status = GdipSetPageScale(graphics, 2.0);
    expect(Ok, status);

    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 150 && rc.top == 75 && rc.right == 300 && rc.bottom == 150) ||
       broken(rc.left == 300 && rc.top == 150 && rc.right == 600 && rc.bottom == 300) /* before Win7 */,
       "expected 150,75-300,150, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);
    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200) ||
       broken(rc.left == 200 && rc.top == 200 && rc.right == 400 && rc.bottom == 400) /* before Win7 */,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 100.0;
    ptf[0].Y = 100.0;
    ptf[1].X = 200.0;
    ptf[1].Y = 200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    if (fabs(ptf[0].X - 150.0) < 0.001)
    {
        expectf(150.0, ptf[0].X);
        expectf(75.0, ptf[0].Y);
        expectf(300.0, ptf[1].X);
        expectf(150.0, ptf[1].Y);
    }
    else /* before Win7 */
    {
        ok(broken(fabs(ptf[0].X - 300.0) < 0.001), "expected 300.0, got %f\n", ptf[0].X);
        ok(broken(fabs(ptf[0].Y - 150.0) < 0.001), "expected 150.0, got %f\n", ptf[0].Y);
        ok(broken(fabs(ptf[1].X - 600.0) < 0.001), "expected 600.0, got %f\n", ptf[1].X);
        ok(broken(fabs(ptf[1].Y - 300.0) < 0.001), "expected 300.0, got %f\n", ptf[1].Y);
    }

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);
    status = GdipRotateMatrix(matrix, 45.0, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipSetWorldTransform(graphics, matrix);
    expect(Ok, status);
    GdipDeleteMatrix(matrix);

    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == COMPLEXREGION, "expected COMPLEXREGION, got %d\n", ret);
    ok((rc.left == 54 && rc.top == -26 && rc.right == 107 && rc.bottom == 27) ||
       /* rounding under Wine is slightly different */
       (rc.left == 53 && rc.top == -26 && rc.right == 106 && rc.bottom == 27) /* Wine */,
       "expected 54,-26-107,27, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);
    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 100.0;
    ptf[0].Y = 100.0;
    ptf[1].X = 200.0;
    ptf[1].Y = 200.0;
    ptf[2].X = 200.0;
    ptf[2].Y = 100.0;
    ptf[3].X = 100.0;
    ptf[3].Y = 200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 4);
    expect(Ok, status);
    expectf(53.033016, ptf[0].X);
    expectf(0.0, ptf[0].Y);
    expectf(106.066032, ptf[1].X);
    expectf(0.0, ptf[1].Y);
    expectf(79.549522, ptf[2].X);
    expectf(-26.516510, ptf[2].Y);
    expectf(79.549522, ptf[3].X);
    expectf(26.516508, ptf[3].Y);

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);
    status = GdipRotateMatrix(matrix, -45.0, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipSetWorldTransform(graphics, matrix);
    expect(Ok, status);
    GdipDeleteMatrix(matrix);

    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == COMPLEXREGION, "expected COMPLEXREGION, got %d\n", ret);
    ok((rc.left == -26 && rc.top == 54 && rc.right == 27 && rc.bottom == 107) ||
       /* rounding under Wine is slightly different */
       (rc.left == -27 && rc.top == 54 && rc.right == 27 && rc.bottom == 106) /* Wine */,
       "expected -26,54-27,107, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);
    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 100.0;
    ptf[0].Y = 100.0;
    ptf[1].X = 200.0;
    ptf[1].Y = 200.0;
    ptf[2].X = 200.0;
    ptf[2].Y = 100.0;
    ptf[3].X = 100.0;
    ptf[3].Y = 200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 4);
    expect(Ok, status);
    expectf(0.0, ptf[0].X);
    expectf(53.033005, ptf[0].Y);
    expectf(0.0, ptf[1].X);
    expectf(106.066010, ptf[1].Y);
    expectf(26.516491, ptf[2].X);
    expectf(79.549507, ptf[2].Y);
    expectf(-26.516520, ptf[3].X);
    expectf(79.549500, ptf[3].Y);

    GdipDeleteRegion(region);
    GdipDeleteGraphics(graphics);
    DeleteDC(hdc);
}