#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {double X; double Y; } ;
struct TYPE_11__ {double X; double Y; double Width; double Height; } ;
struct TYPE_10__ {int left; int top; int right; int bottom; } ;
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
 int /*<<< orphan*/  GdipGetClipBounds (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  GdipGetPageUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetRegionBounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  GdipGetRegionHRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipRotateMatrix (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipScaleMatrix (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetPageScale (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  GdipSetPageUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTransformPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipTransformRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTranslateMatrix (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int GetRgnBox (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int /*<<< orphan*/  Ok ; 
 int SIMPLEREGION ; 
 int /*<<< orphan*/  SetViewportOrgEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnitDisplay ; 
 int /*<<< orphan*/  UnitPoint ; 
 int broken (int) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,double) ; 
 int /*<<< orphan*/  expectf_ (double,double,double) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void test_clipping(void)
{
    HDC hdc;
    GpStatus status;
    GpGraphics *graphics;
    GpRegion *region, *region100x100;
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

    status = GdipCreateRegion(&region);
    expect(Ok, status);
    status = GdipSetEmpty(region);
    expect(Ok, status);

    status = GdipCreateRegion(&region100x100);
    expect(Ok, status);
    status = GdipSetEmpty(region100x100);
    expect(Ok, status);

    rect.X = rect.Y = 100.0;
    rect.Width = rect.Height = 100.0;
    status = GdipCombineRegionRect(region100x100, &rect, CombineModeUnion);
    expect(Ok, status);
    status = GdipSetClipRegion(graphics, region100x100, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetClipBounds(graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 100.0 && rect.Y == 100.0 && rect.Width == 100.0 && rect.Height == 100.0,
       "expected 100.0,100.0-100.0,100.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    /* Clip region does not account for changes to gdi32 transform */
    SetViewportOrgEx(hdc, 10, 10, NULL);

    status = GdipGetClipBounds(graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 100.0 && rect.Y == 100.0 && rect.Width == 100.0 && rect.Height == 100.0,
       "expected 100.0,100.0-100.0,100.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    SetViewportOrgEx(hdc, 0, 0, NULL);

    status = GdipSetEmpty(region);
    expect(Ok, status);
    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionBounds(region, graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 100.0 && rect.Y == 100.0 && rect.Width == 100.0 && rect.Height == 100.0,
       "expected 100.0,100.0-100.0,100.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    ptf[0].X = 100.0;
    ptf[0].Y = 100.0;
    ptf[1].X = 200.0;
    ptf[1].Y = 200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    ok(ptf[0].X == 100.0 && ptf[0].Y == 100.0 && ptf[1].X == 200.0 && ptf[1].Y == 200.0,
       "expected 100.0,100.0-200.0,200.0, got %f,%f-%f,%f\n", ptf[0].X, ptf[0].Y, ptf[1].X, ptf[1].Y);

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);
    status = GdipScaleMatrix(matrix, 2.0, 4.0, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipTranslateMatrix(matrix, 10.0, 20.0, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipSetWorldTransform(graphics, matrix);
    expect(Ok, status);

    status = GdipGetClipBounds(graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 45.0 && rect.Y == 20.0 && rect.Width == 50.0 && rect.Height == 25.0,
       "expected 45.0,20.0-50.0,25.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipSetEmpty(region);
    expect(Ok, status);
    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionBounds(region, graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 45.0 && rect.Y == 20.0 && rect.Width == 50.0 && rect.Height == 25.0,
       "expected 45.0,20.0-50.0,25.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipGetRegionBounds(region100x100, graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 100.0 && rect.Y == 100.0 && rect.Width == 100.0 && rect.Height == 100.0,
       "expected 100.0,100.0-100.0,100.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 45 && rc.top == 20 && rc.right == 95 && rc.bottom == 45,
       "expected 45,20-95,45, got %s\n", wine_dbgstr_rect(&rc));
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
    ok(ptf[0].X == 45.0 && ptf[0].Y == 20.0 && ptf[1].X == 95.0 && ptf[1].Y == 45.0,
       "expected 45.0,20.0-95.0,45.0, got %f,%f-%f,%f\n", ptf[0].X, ptf[0].Y, ptf[1].X, ptf[1].Y);

    status = GdipGetRegionHRgn(region100x100, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    status = GdipGetRegionHRgn(region100x100, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 210 && rc.top == 420 && rc.right == 410 && rc.bottom == 820,
       "expected 210,420-410,820, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 210.0;
    ptf[0].Y = 420.0;
    ptf[1].X = 410.0;
    ptf[1].Y = 820.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    ok(ptf[0].X == 100.0 && ptf[0].Y == 100.0 && ptf[1].X == 200.0 && ptf[1].Y == 200.0,
       "expected 100.0,100.0-200.0,200.0, got %f,%f-%f,%f\n", ptf[0].X, ptf[0].Y, ptf[1].X, ptf[1].Y);

    status = GdipSetPageScale(graphics, 2.0);
    expect(Ok, status);

    status = GdipGetClipBounds(graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 45.0 && rect.Y == 20.0 && rect.Width == 50.0 && rect.Height == 25.0,
       "expected 45.0,20.0-50.0,25.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipSetEmpty(region);
    expect(Ok, status);
    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionBounds(region, graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 45.0 && rect.Y == 20.0 && rect.Width == 50.0 && rect.Height == 25.0,
       "expected 45.0,20.0-50.0,25.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipGetRegionBounds(region100x100, graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 100.0 && rect.Y == 100.0 && rect.Width == 100.0 && rect.Height == 100.0,
       "expected 100.0,100.0-100.0,100.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 45 && rc.top == 20 && rc.right == 95 && rc.bottom == 45,
       "expected 45,20-95,45, got %s\n", wine_dbgstr_rect(&rc));
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
    ok(ptf[0].X == 45.0 && ptf[0].Y == 20.0 && ptf[1].X == 95.0 && ptf[1].Y == 45.0,
       "expected 45.0,20.0-95.0,45.0, got %f,%f-%f,%f\n", ptf[0].X, ptf[0].Y, ptf[1].X, ptf[1].Y);

    status = GdipGetRegionHRgn(region100x100, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    status = GdipGetRegionHRgn(region100x100, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 210 && rc.top == 420 && rc.right == 410 && rc.bottom == 820,
       "expected 210,420-410,820, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 210.0;
    ptf[0].Y = 420.0;
    ptf[1].X = 410.0;
    ptf[1].Y = 820.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    ok(ptf[0].X == 100.0 && ptf[0].Y == 100.0 && ptf[1].X == 200.0 && ptf[1].Y == 200.0,
       "expected 100.0,100.0-200.0,200.0, got %f,%f-%f,%f\n", ptf[0].X, ptf[0].Y, ptf[1].X, ptf[1].Y);

    GdipSetPageUnit(graphics, UnitPoint);
    expect(Ok, status);

    status = GdipGetClipBounds(graphics, &rect);
    expect(Ok, status);
    ok((rect.X == 13.75 && rect.Y == 4.375 && rect.Width == 18.75 && rect.Height == 9.375) ||
       /* rounding under Wine is slightly different */
       (rect.X == 14.0 && rect.Y == 4.0 && rect.Width == 19.0 && rect.Height == 10.0) /* Wine */ ||
       broken(rect.X == 45.0 && rect.Y == 20.0 && rect.Width == 50.0 && rect.Height == 25.0) /* before Win7 */,
       "expected 13.75,4.375-18.75,9.375, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipSetEmpty(region);
    expect(Ok, status);
    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionBounds(region, graphics, &rect);
    expect(Ok, status);
    ok((rect.X == 13.75 && rect.Y == 4.375 && rect.Width == 18.75 && rect.Height == 9.375) ||
       /* rounding under Wine is slightly different */
       (rect.X == 14.0 && rect.Y == 4.0 && rect.Width == 19.0 && rect.Height == 10.0) /* Wine */ ||
       broken(rect.X == 45.0 && rect.Y == 20.0 && rect.Width == 50.0 && rect.Height == 25.0) /* before Win7 */,
       "expected 13.75,4.375-18.75,9.375, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipGetRegionBounds(region100x100, graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 100.0 && rect.Y == 100.0 && rect.Width == 100.0 && rect.Height == 100.0,
       "expected 100.0,100.0-100.0,100.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 14 && rc.top == 5 && rc.right == 33 && rc.bottom == 14) ||
       /* rounding under Wine is slightly different */
       (rc.left == 14 && rc.top == 4 && rc.right == 33 && rc.bottom == 14) /* Wine */ ||
       broken(rc.left == 45 && rc.top == 20 && rc.right == 95 && rc.bottom == 45) /* before Win7 */,
       "expected 14,5-33,14, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200) ||
      broken(rc.left == 267 && rc.top == 267 && rc.right == 534 && rc.bottom == 534) /* before Win7 */,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 100.0;
    ptf[0].Y = 100.0;
    ptf[1].X = 200.0;
    ptf[1].Y = 200.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    ok((ptf[0].X == 13.75 && ptf[0].Y == 4.375 && ptf[1].X == 32.5 && ptf[1].Y == 13.75) ||
       broken(ptf[0].X == 45.0 && ptf[0].Y == 20.0 && ptf[1].X == 95.0 && ptf[1].Y == 45.0) /* before Win7 */,
       "expected 13.75,4.375-32.5,13.75, got %f,%f-%f,%f\n", ptf[0].X, ptf[0].Y, ptf[1].X, ptf[1].Y);

    status = GdipGetRegionHRgn(region100x100, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 100 && rc.top == 100 && rc.right == 200 && rc.bottom == 200,
       "expected 100,100-200,200, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    status = GdipGetRegionHRgn(region100x100, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 560 && rc.top == 1120 && rc.right == 1094 && rc.bottom == 2187) ||
       /* rounding under Wine is slightly different */
       (rc.left == 560 && rc.top == 1120 && rc.right == 1093 && rc.bottom == 2187) /* Wine */,
       "expected 560,1120-1094,2187, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 560.0;
    ptf[0].Y = 1120.0;
    ptf[1].X = 1094.0;
    ptf[1].Y = 2187.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    if (fabs(ptf[0].X - 100.0) < 0.001)
    {
        expectf(100.0, ptf[0].X);
        expectf(100.0, ptf[0].Y);
        expectf(200.125, ptf[1].X);
        expectf(200.03125, ptf[1].Y);
    }
    else /* before Win7 */
    {
        ok(broken(fabs(ptf[0].X - 275.0) < 0.001), "expected 275.0, got %f\n", ptf[0].X);
        ok(broken(fabs(ptf[0].Y - 275.0) < 0.001), "expected 275.0, got %f\n", ptf[0].Y);
        ok(broken(fabs(ptf[1].X - 542.0) < 0.001), "expected 542.0, got %f\n", ptf[1].X);
        ok(broken(fabs(ptf[1].Y - 541.75) < 0.001), "expected 541.75, got %f\n", ptf[1].Y);
    }

    status = GdipTransformRegion(region100x100, matrix);
    expect(Ok, status);

    status = GdipGetRegionBounds(region100x100, graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 210.0 && rect.Y == 420.0 && rect.Width == 200.0 && rect.Height == 400.0,
       "expected 210.0,420.0-200.0,400.0, got %.2f,%.2f-%.2f,%.2f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipGetRegionHRgn(region100x100, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 210 && rc.top == 420 && rc.right == 410 && rc.bottom == 820,
       "expected 210,420-410,820, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    status = GdipGetRegionHRgn(region100x100, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok((rc.left == 1147 && rc.top == 4534 && rc.right == 2214 && rc.bottom == 8800) ||
       /* rounding under Wine is slightly different */
       (rc.left == 1147 && rc.top == 4533 && rc.right == 2213 && rc.bottom == 8800) /* Wine */,
       "expected 1147,4534-2214,8800, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = 1147.0;
    ptf[0].Y = 4534.0;
    ptf[1].X = 2214.0;
    ptf[1].Y = 8800.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 2);
    expect(Ok, status);
    if (fabs(ptf[0].X - 210.0625) < 0.001)
    {
        expectf(210.0625, ptf[0].X);
        expectf(420.0625, ptf[0].Y);
        expectf(410.125, ptf[1].X);
        expectf(820.0, ptf[1].Y);
    }
    else /* before Win7 */
    {
        ok(broken(fabs(ptf[0].X - 568.5) < 0.001), "expected 568.5, got %f\n", ptf[0].X);
        ok(broken(fabs(ptf[0].Y - 1128.5) < 0.001), "expected 1128.5, got %f\n", ptf[0].Y);
        ok(broken(fabs(ptf[1].X - 1102.0) < 0.001), "expected 1102.0, got %f\n", ptf[1].X);
        ok(broken(fabs(ptf[1].Y - 2195.0) < 0.001), "expected 2195.0, got %f\n", ptf[1].Y);
    }

    status = GdipRotateMatrix(matrix, 30.0, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipSetWorldTransform(graphics, matrix);
    expect(Ok, status);

    status = GdipGetClipBounds(graphics, &rect);
    expect(Ok, status);
    expectf_(20.612978, rect.X, 1.0);
    expectf_(-6.256012, rect.Y, 1.5);
    expectf_(25.612978, rect.Width, 1.0);
    expectf_(12.806489, rect.Height, 1.0);

    status = GdipSetEmpty(region);
    expect(Ok, status);
    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionBounds(region, graphics, &rect);
    expect(Ok, status);
   /* rounding under Wine is slightly different */
    expectf_(20.612978, rect.X, 1.0);
    expectf_(-6.256012, rect.Y, 1.5);
    expectf_(25.612978, rect.Width, 1.0);
    expectf_(12.806489, rect.Height, 1.0);

    status = GdipGetRegionBounds(region100x100, graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 210.0 && rect.Y == 420.0 && rect.Width == 200.0 && rect.Height == 400.0,
       "expected 210.0,420.0-200.0,400.0, got %f,%f-%f,%f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == COMPLEXREGION, "expected COMPLEXREGION, got %d\n", ret);
    ok((rc.left == 22 && rc.top == -6 && rc.right == 46 && rc.bottom == 7) ||
       /* rounding under Wine is slightly different */
       (rc.left == 21 && rc.top == -5 && rc.right == 46 && rc.bottom == 7) /* Wine */,
       "expected (22,-6)-(46,7), got %s\n", wine_dbgstr_rect(&rc));
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
    expectf(20.612978, ptf[0].X);
    expectf(-1.568512, ptf[0].Y);
    expectf(46.225956, ptf[1].X);
    expectf(1.862977, ptf[1].Y);
    expectf(36.850956, ptf[2].X);
    expectf(-6.256012, ptf[2].Y);
    expectf(29.987980, ptf[3].X);
    expectf(6.550478, ptf[3].Y);

    status = GdipGetRegionHRgn(region100x100, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 210 && rc.top == 420 && rc.right == 410 && rc.bottom == 820,
       "expected 210,420-410,820, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    status = GdipGetRegionHRgn(region100x100, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == COMPLEXREGION, "expected COMPLEXREGION, got %d\n", ret);
    ok((rc.left == -3406 && rc.top == 4500 && rc.right == -350 && rc.bottom == 8728) ||
       /* rounding under Wine is slightly different */
       (rc.left == -3407 && rc.top == 4500 && rc.right == -350 && rc.bottom == 8728) /* Wine */,
       "expected (-3406,4500)-(-350,8728), got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = -3406.0;
    ptf[0].Y = 4500.0;
    ptf[1].X = -350.0;
    ptf[1].Y = 8728.0;
    ptf[2].X = -350.0;
    ptf[2].Y = 4500.0;
    ptf[3].X = -3406.0;
    ptf[3].Y = 8728.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 4);
    expect(Ok, status);
    expectf(-136.190491, ptf[0].X);
    expectf(520.010742, ptf[0].Y);
    expectf(756.417175, ptf[1].X);
    expectf(720.031616, ptf[1].Y);
    expectf(360.042114, ptf[2].X);
    expectf(376.760742, ptf[2].Y);
    expectf(260.184570, ptf[3].X);
    expectf(863.281616, ptf[3].Y);

    status = GdipRotateMatrix(matrix, -90.0, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipSetWorldTransform(graphics, matrix);
    expect(Ok, status);

    status = GdipGetClipBounds(graphics, &rect);
    expect(Ok, status);
    expectf_(-28.100956, rect.X, 1.0);
    expectf_(7.806488, rect.Y, 1.5);
    expectf_(25.612978, rect.Width, 1.0);
    expectf_(12.806489, rect.Height, 1.0);

    status = GdipSetEmpty(region);
    expect(Ok, status);
    status = GdipGetClip(graphics, region);
    expect(Ok, status);
    status = GdipGetRegionBounds(region, graphics, &rect);
    expect(Ok, status);
   /* rounding under Wine is slightly different */
    expectf_(-28.100956, rect.X, 1.0);
    expectf_(7.806488, rect.Y, 1.5);
    expectf_(25.612978, rect.Width, 1.0);
    expectf_(12.806489, rect.Height, 1.0);

    status = GdipGetRegionBounds(region100x100, graphics, &rect);
    expect(Ok, status);
    ok(rect.X == 210.0 && rect.Y == 420.0 && rect.Width == 200.0 && rect.Height == 400.0,
       "expected 210.0,420.0-200.0,400.0, got %f,%f-%f,%f\n", rect.X, rect.Y, rect.Width, rect.Height);

    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == COMPLEXREGION, "expected COMPLEXREGION, got %d\n", ret);
    ok((rc.left == -27 && rc.top == 8 && rc.right == -2 && rc.bottom == 21) ||
       /* rounding under Wine is slightly different */
       (rc.left == -28 && rc.top == 9 && rc.right == -2 && rc.bottom == 21) /* Wine */,
       "expected (-27,8)-(-2,21), got %s\n", wine_dbgstr_rect(&rc));
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
    expectf(-11.862979, ptf[0].X);
    expectf(7.806488, ptf[0].Y);
    expectf(-18.725958, ptf[1].X);
    expectf(20.612976, ptf[1].Y);
    expectf(-2.487981, ptf[2].X);
    expectf(15.925477, ptf[2].Y);
    expectf(-28.100956, ptf[3].X);
    expectf(12.493987, ptf[3].Y);

    status = GdipGetRegionHRgn(region100x100, NULL, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == SIMPLEREGION, "expected SIMPLEREGION, got %d\n", ret);
    ok(rc.left == 210 && rc.top == 420 && rc.right == 410 && rc.bottom == 820,
       "expected 210,420-410,820, got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    status = GdipGetRegionHRgn(region100x100, graphics, &hrgn);
    expect(Ok, status);
    ret = GetRgnBox(hrgn, &rc);
    ok(ret == COMPLEXREGION, "expected COMPLEXREGION, got %d\n", ret);
    ok((rc.left == 4500 && rc.top == 351 && rc.right == 8728 && rc.bottom == 3407) ||
       /* rounding under Wine is slightly different */
       (rc.left == 4499 && rc.top == 351 && rc.right == 8728 && rc.bottom == 3407) /* Wine */,
       "expected (4500,351)-(8728,3407), got %s\n", wine_dbgstr_rect(&rc));
    DeleteObject(hrgn);

    ptf[0].X = -3406.0;
    ptf[0].Y = 4500.0;
    ptf[1].X = -350.0;
    ptf[1].Y = 8728.0;
    ptf[2].X = -350.0;
    ptf[2].Y = 4500.0;
    ptf[3].X = -3406.0;
    ptf[3].Y = 8728.0;
    status = GdipTransformPoints(graphics, CoordinateSpaceWorld, CoordinateSpaceDevice, ptf, 4);
    expect(Ok, status);
    expectf(-1055.021484, ptf[0].X);
    expectf(-70.595329, ptf[0].Y);
    expectf(-1455.063232, ptf[1].X);
    expectf(375.708435, ptf[1].Y);
    expectf(-768.521484, ptf[2].X);
    expectf(177.520981, ptf[2].Y);
    expectf(-1741.563110, ptf[3].X);
    expectf(127.592125, ptf[3].Y);

    GdipDeleteMatrix(matrix);
    GdipDeleteRegion(region);
    GdipDeleteRegion(region100x100);
    GdipDeleteGraphics(graphics);
    DeleteDC(hdc);
}