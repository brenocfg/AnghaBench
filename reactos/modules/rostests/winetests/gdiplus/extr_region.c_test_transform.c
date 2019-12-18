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
struct TYPE_3__ {double X; double Y; double Width; double Height; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathEllipse (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCombineRegionPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsEqualRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipResetPath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipRotateMatrix (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipScaleMatrix (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTransformRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_region_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_transform(void)
{
    GpRegion *region, *region2;
    GpMatrix *matrix;
    GpGraphics *graphics;
    GpPath *path;
    GpRectF rectf;
    GpStatus status;
    HDC hdc = GetDC(0);
    BOOL res;
    DWORD type;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);

    status = GdipCreateRegion(&region);
    expect(Ok, status);
    status = GdipCreateRegion(&region2);
    expect(Ok, status);

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);
    status = GdipScaleMatrix(matrix, 2.0, 3.0, MatrixOrderAppend);
    expect(Ok, status);

    /* NULL */
    status = GdipTransformRegion(NULL, matrix);
    expect(InvalidParameter, status);

    status = GdipTransformRegion(region, NULL);
    expect(InvalidParameter, status);

    /* infinite */
    status = GdipTransformRegion(region, matrix);
    expect(Ok, status);

    res = FALSE;
    status = GdipIsEqualRegion(region, region2, graphics, &res);
    expect(Ok, status);
    ok(res, "Expected to be equal.\n");
    type = get_region_type(region);
    expect(0x10000003 /* RegionDataInfiniteRect */, type);

    /* empty */
    status = GdipSetEmpty(region);
    expect(Ok, status);
    status = GdipTransformRegion(region, matrix);
    expect(Ok, status);

    status = GdipSetEmpty(region2);
    expect(Ok, status);

    res = FALSE;
    status = GdipIsEqualRegion(region, region2, graphics, &res);
    expect(Ok, status);
    ok(res, "Expected to be equal.\n");
    type = get_region_type(region);
    expect(0x10000002 /* RegionDataEmptyRect */, type);

    /* rect */
    rectf.X = 10.0;
    rectf.Y = 0.0;
    rectf.Width = rectf.Height = 100.0;
    status = GdipCombineRegionRect(region, &rectf, CombineModeReplace);
    expect(Ok, status);
    rectf.X = 20.0;
    rectf.Y = 0.0;
    rectf.Width = 200.0;
    rectf.Height = 300.0;
    status = GdipCombineRegionRect(region2, &rectf, CombineModeReplace);
    expect(Ok, status);
    status = GdipTransformRegion(region, matrix);
    expect(Ok, status);
    res = FALSE;
    status = GdipIsEqualRegion(region, region2, graphics, &res);
    expect(Ok, status);
    ok(res, "Expected to be equal.\n");
    type = get_region_type(region);
    expect(0x10000000 /* RegionDataRect */, type);

    /* path */
    status = GdipAddPathEllipse(path, 0.0, 10.0, 100.0, 150.0);
    expect(Ok, status);
    status = GdipCombineRegionPath(region, path, CombineModeReplace);
    expect(Ok, status);
    status = GdipResetPath(path);
    expect(Ok, status);
    status = GdipAddPathEllipse(path, 0.0, 30.0, 200.0, 450.0);
    expect(Ok, status);
    status = GdipCombineRegionPath(region2, path, CombineModeReplace);
    expect(Ok, status);
    status = GdipTransformRegion(region, matrix);
    expect(Ok, status);
    res = FALSE;
    status = GdipIsEqualRegion(region, region2, graphics, &res);
    expect(Ok, status);
    ok(res, "Expected to be equal.\n");
    type = get_region_type(region);
    expect(0x10000001 /* RegionDataPath */, type);

    /* rotated rect -> path */
    rectf.X = 10.0;
    rectf.Y = 0.0;
    rectf.Width = rectf.Height = 100.0;
    status = GdipCombineRegionRect(region, &rectf, CombineModeReplace);
    expect(Ok, status);
    status = GdipRotateMatrix(matrix, 45.0, MatrixOrderAppend);
    expect(Ok, status);
    status = GdipTransformRegion(region, matrix);
    expect(Ok, status);
    type = get_region_type(region);
    expect(0x10000001 /* RegionDataPath */, type);

    status = GdipDeleteRegion(region);
    expect(Ok, status);
    status = GdipDeleteRegion(region2);
    expect(Ok, status);
    status = GdipDeleteGraphics(graphics);
    expect(Ok, status);
    status = GdipDeletePath(path);
    expect(Ok, status);
    status = GdipDeleteMatrix(matrix);
    expect(Ok, status);
    ReleaseDC(0, hdc);
}