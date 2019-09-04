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
typedef  int /*<<< orphan*/  buf ;
typedef  int UINT ;
struct TYPE_6__ {int X; int Y; int Width; int Height; } ;
struct TYPE_5__ {int X; int Y; } ;
typedef  TYPE_1__ RegionDataPoint ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_2__ GpRect ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int CombineModeComplement ; 
 int CombineModeExclude ; 
 int CombineModeIntersect ; 
 int CombineModeUnion ; 
 int CombineModeXor ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int GdipAddPathArc (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int GdipAddPathLine (int /*<<< orphan*/ *,double,double,int,double) ; 
 int /*<<< orphan*/  GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipAddPathRectangleI (int /*<<< orphan*/ *,int,int,int,int) ; 
 int GdipClosePathFigure (int /*<<< orphan*/ *) ; 
 int GdipCombineRegionPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int GdipCombineRegionRectI (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int GdipCombineRegionRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int GdipCreateRegionPath (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipCreateRegionRectI (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int GdipDeletePath (int /*<<< orphan*/ *) ; 
 int GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int GdipGetRegionData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int GdipGetRegionDataSize (int /*<<< orphan*/ *,int*) ; 
 int GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int GdipSetInfinite (int /*<<< orphan*/ *) ; 
 int GdipTransformRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipTranslateRegion (int /*<<< orphan*/ *,double,double) ; 
 int InsufficientBuffer ; 
 int InvalidParameter ; 
 int Ok ; 
 int RGNDATA_EMPTY_RECT ; 
 int RGNDATA_INFINITE_RECT ; 
 int RGNDATA_PATH ; 
 int RGNDATA_RECT ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expect_dword (int*,int) ; 
 int /*<<< orphan*/  expect_float (int*,double) ; 
 int /*<<< orphan*/  expect_magic (int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  test_region_data (int*,int,int) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_getregiondata(void)
{
    GpStatus status;
    GpRegion *region, *region2;
    RegionDataPoint *point;
    UINT needed;
    DWORD buf[256];
    GpRect rect;
    GpPath *path;
    GpMatrix *matrix;

    status = GdipCreateRegion(&region);
    ok(status == Ok, "status %08x\n", status);

    needed = 0;
    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(20, needed);

    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, 0, &needed);
    ok(status == InvalidParameter, "status %08x\n", status);

    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, 4, &needed);
    ok(status == InsufficientBuffer, "status %08x\n", status);
    expect(4, needed);
    expect_dword(buf, 0xeeeeeeee);

    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(20, needed);
    expect_dword(buf, 12);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_INFINITE_RECT);
    expect_dword(buf + 6, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipSetEmpty(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(20, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(20, needed);
    expect_dword(buf, 12);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_EMPTY_RECT);
    expect_dword(buf + 6, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipSetInfinite(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(20, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(20, needed);
    expect_dword(buf, 12);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_INFINITE_RECT);
    expect_dword(buf + 6, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipDeleteRegion(region);
    ok(status == Ok, "status %08x\n", status);

    rect.X = 10;
    rect.Y = 20;
    rect.Width = 100;
    rect.Height = 200;
    status = GdipCreateRegionRectI(&rect, &region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(36, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(36, needed);
    expect_dword(buf, 28);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_RECT);
    expect_float(buf + 5, 10.0);
    expect_float(buf + 6, 20.0);
    expect_float(buf + 7, 100.0);
    expect_float(buf + 8, 200.0);
    expect_dword(buf + 10, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    rect.X = 50;
    rect.Y = 30;
    rect.Width = 10;
    rect.Height = 20;
    status = GdipCombineRegionRectI(region, &rect, CombineModeIntersect);
    ok(status == Ok, "status %08x\n", status);
    rect.X = 100;
    rect.Y = 300;
    rect.Width = 30;
    rect.Height = 50;
    status = GdipCombineRegionRectI(region, &rect, CombineModeXor);
    ok(status == Ok, "status %08x\n", status);

    rect.X = 200;
    rect.Y = 100;
    rect.Width = 133;
    rect.Height = 266;
    status = GdipCreateRegionRectI(&rect, &region2);
    ok(status == Ok, "status %08x\n", status);
    rect.X = 20;
    rect.Y = 10;
    rect.Width = 40;
    rect.Height = 66;
    status = GdipCombineRegionRectI(region2, &rect, CombineModeUnion);
    ok(status == Ok, "status %08x\n", status);

    status = GdipCombineRegionRegion(region, region2, CombineModeComplement);
    ok(status == Ok, "status %08x\n", status);

    rect.X = 400;
    rect.Y = 500;
    rect.Width = 22;
    rect.Height = 55;
    status = GdipCombineRegionRectI(region, &rect, CombineModeExclude);
    ok(status == Ok, "status %08x\n", status);

    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(156, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(156, needed);
    expect_dword(buf, 148);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 10);
    expect_dword(buf + 4, CombineModeExclude);
    expect_dword(buf + 5, CombineModeComplement);
    expect_dword(buf + 6, CombineModeXor);
    expect_dword(buf + 7, CombineModeIntersect);
    expect_dword(buf + 8, RGNDATA_RECT);
    expect_float(buf + 9, 10.0);
    expect_float(buf + 10, 20.0);
    expect_float(buf + 11, 100.0);
    expect_float(buf + 12, 200.0);
    expect_dword(buf + 13, RGNDATA_RECT);
    expect_float(buf + 14, 50.0);
    expect_float(buf + 15, 30.0);
    expect_float(buf + 16, 10.0);
    expect_float(buf + 17, 20.0);
    expect_dword(buf + 18, RGNDATA_RECT);
    expect_float(buf + 19, 100.0);
    expect_float(buf + 20, 300.0);
    expect_float(buf + 21, 30.0);
    expect_float(buf + 22, 50.0);
    expect_dword(buf + 23, CombineModeUnion);
    expect_dword(buf + 24, RGNDATA_RECT);
    expect_float(buf + 25, 200.0);
    expect_float(buf + 26, 100.0);
    expect_float(buf + 27, 133.0);
    expect_float(buf + 28, 266.0);
    expect_dword(buf + 29, RGNDATA_RECT);
    expect_float(buf + 30, 20.0);
    expect_float(buf + 31, 10.0);
    expect_float(buf + 32, 40.0);
    expect_float(buf + 33, 66.0);
    expect_dword(buf + 34, RGNDATA_RECT);
    expect_float(buf + 35, 400.0);
    expect_float(buf + 36, 500.0);
    expect_float(buf + 37, 22.0);
    expect_float(buf + 38, 55.0);
    expect_dword(buf + 39, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipDeleteRegion(region2);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeleteRegion(region);
    ok(status == Ok, "status %08x\n", status);

    /* Try some paths */

    status = GdipCreatePath(FillModeAlternate, &path);
    ok(status == Ok, "status %08x\n", status);
    GdipAddPathRectangle(path, 12.5, 13.0, 14.0, 15.0);

    status = GdipCreateRegionPath(path, &region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(72, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(72, needed);
    expect_dword(buf, 64);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_PATH);
    expect_dword(buf + 5, 0x00000030);
    expect_magic(buf + 6);
    expect_dword(buf + 7, 0x00000004);
    expect_dword(buf + 8, 0x00000000);
    expect_float(buf + 9, 12.5);
    expect_float(buf + 10, 13.0);
    expect_float(buf + 11, 26.5);
    expect_float(buf + 12, 13.0);
    expect_float(buf + 13, 26.5);
    expect_float(buf + 14, 28.0);
    expect_float(buf + 15, 12.5);
    expect_float(buf + 16, 28.0);
    expect_dword(buf + 17, 0x81010100);
    expect_dword(buf + 18, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    rect.X = 50;
    rect.Y = 30;
    rect.Width = 10;
    rect.Height = 20;
    status = GdipCombineRegionRectI(region, &rect, CombineModeIntersect);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(96, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(96, needed);
    expect_dword(buf, 88);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 2);
    expect_dword(buf + 4, CombineModeIntersect);
    expect_dword(buf + 5, RGNDATA_PATH);
    expect_dword(buf + 6, 0x00000030);
    expect_magic(buf + 7);
    expect_dword(buf + 8, 0x00000004);
    expect_dword(buf + 9, 0x00000000);
    expect_float(buf + 10, 12.5);
    expect_float(buf + 11, 13.0);
    expect_float(buf + 12, 26.5);
    expect_float(buf + 13, 13.0);
    expect_float(buf + 14, 26.5);
    expect_float(buf + 15, 28.0);
    expect_float(buf + 16, 12.5);
    expect_float(buf + 17, 28.0);
    expect_dword(buf + 18, 0x81010100);
    expect_dword(buf + 19, RGNDATA_RECT);
    expect_float(buf + 20, 50.0);
    expect_float(buf + 21, 30.0);
    expect_float(buf + 22, 10.0);
    expect_float(buf + 23, 20.0);
    expect_dword(buf + 24, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipDeleteRegion(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeletePath(path);
    ok(status == Ok, "status %08x\n", status);

    /* Test an empty path */
    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);
    status = GdipCreateRegionPath(path, &region);
    expect(Ok, status);
    status = GdipGetRegionDataSize(region, &needed);
    expect(Ok, status);
    expect(36, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    expect(Ok, status);
    expect(36, needed);
    expect_dword(buf, 28);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_PATH);
    /* Second signature for pathdata */
    expect_dword(buf + 5, 12);
    expect_magic(buf + 6);
    expect_dword(buf + 7, 0);
    /* flags 0 means that a path is an array of FLOATs */
    ok(*(buf + 8) == 0x4000 /* before win7 */ || *(buf + 8) == 0,
       "expected 0x4000 or 0, got %08x\n", *(buf + 8));
    expect_dword(buf + 10, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    /* Transform an empty region */
    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);
    status = GdipTransformRegion(region, matrix);
    expect(Ok, status);
    GdipDeleteMatrix(matrix);

    status = GdipDeleteRegion(region);
    expect(Ok, status);

    /* Test a simple triangle of INTs */
    status = GdipAddPathLine(path, 5, 6, 7, 8);
    expect(Ok, status);
    status = GdipAddPathLine(path, 8, 1, 5, 6);
    expect(Ok, status);
    status = GdipClosePathFigure(path);
    expect(Ok, status);
    status = GdipCreateRegionPath(path, &region);
    expect(Ok, status);
    status = GdipGetRegionDataSize(region, &needed);
    expect(Ok, status);
    expect(56, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    expect(Ok, status);
    expect(56, needed);
    expect_dword(buf, 48);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3 , 0);
    expect_dword(buf + 4 , RGNDATA_PATH);
    expect_dword(buf + 5, 32);
    expect_magic(buf + 6);
    expect_dword(buf + 7, 4);
    /* flags 0x4000 means that a path is an array of shorts instead of FLOATs */
    expect_dword(buf + 8, 0x4000);

    point = (RegionDataPoint*)(buf + 9);
    expect(5, point[0].X);
    expect(6, point[0].Y);
    expect(7, point[1].X); /* buf + 10 */
    expect(8, point[1].Y);
    expect(8, point[2].X); /* buf + 11 */
    expect(1, point[2].Y);
    expect(5, point[3].X); /* buf + 12 */
    expect(6, point[3].Y);
    expect_dword(buf + 13, 0x81010100); /* 0x01010100 if we don't close the path */
    expect_dword(buf + 14, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipTranslateRegion(region, 0.6, 0.8);
    expect(Ok, status);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    expect(Ok, status);
    expect(72, needed);
    expect_dword(buf, 64);
    expect_magic(buf + 2);
    expect_dword(buf + 3 , 0);
    expect_dword(buf + 4 , RGNDATA_PATH);
    expect_dword(buf + 5, 48);
    expect_magic(buf + 6);
    expect_dword(buf + 7, 4);
    /* flags 0 means that a path is an array of FLOATs */
    expect_dword(buf + 8, 0);
    expect_float(buf + 9, 5.6);
    expect_float(buf + 10, 6.8);
    expect_float(buf + 11, 7.6);
    expect_float(buf + 12, 8.8);
    expect_float(buf + 13, 8.6);
    expect_float(buf + 14, 1.8);
    expect_float(buf + 15, 5.6);
    expect_float(buf + 16, 6.8);
    expect_dword(buf + 17, 0x81010100); /* 0x01010100 if we don't close the path */
    expect_dword(buf + 18, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipDeletePath(path);
    expect(Ok, status);
    status = GdipDeleteRegion(region);
    expect(Ok, status);

    /* Test a floating-point triangle */
    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);
    status = GdipAddPathLine(path, 5.6, 6.2, 7.2, 8.9);
    expect(Ok, status);
    status = GdipAddPathLine(path, 8.1, 1.6, 5.6, 6.2);
    expect(Ok, status);
    status = GdipCreateRegionPath(path, &region);
    expect(Ok, status);
    status = GdipGetRegionDataSize(region, &needed);
    expect(Ok, status);
    expect(72, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    expect(Ok, status);
    expect(72, needed);
    expect_dword(buf, 64);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_PATH);
    expect_dword(buf + 5, 48);
    expect_magic(buf + 6);
    expect_dword(buf + 7, 4);
    expect_dword(buf + 8, 0);
    expect_float(buf + 9, 5.6);
    expect_float(buf + 10, 6.2);
    expect_float(buf + 11, 7.2);
    expect_float(buf + 12, 8.9);
    expect_float(buf + 13, 8.1);
    expect_float(buf + 14, 1.6);
    expect_float(buf + 15, 5.6);
    expect_float(buf + 16, 6.2);
    expect_dword(buf + 17, 0x01010100);
    expect_dword(buf + 18, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipDeletePath(path);
    expect(Ok, status);
    status = GdipDeleteRegion(region);
    expect(Ok, status);

    /* Test for a path with > 4 points, and CombineRegionPath */
    GdipCreatePath(FillModeAlternate, &path);
    status = GdipAddPathLine(path, 50, 70.2, 60, 102.8);
    expect(Ok, status);
    status = GdipAddPathLine(path, 55.4, 122.4, 40.4, 60.2);
    expect(Ok, status);
    status = GdipAddPathLine(path, 45.6, 20.2, 50, 70.2);
    expect(Ok, status);
    rect.X = 20;
    rect.Y = 25;
    rect.Width = 60;
    rect.Height = 120;
    status = GdipCreateRegionRectI(&rect, &region);
    expect(Ok, status);
    status = GdipCombineRegionPath(region, path, CombineModeUnion);
    expect(Ok, status);

    status = GdipGetRegionDataSize(region, &needed);
    expect(Ok, status);
    expect(116, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    expect(Ok, status);
    expect(116, needed);
    expect_dword(buf, 108);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 2);
    expect_dword(buf + 4, CombineModeUnion);
    expect_dword(buf + 5, RGNDATA_RECT);
    expect_float(buf + 6, 20.0);
    expect_float(buf + 7, 25.0);
    expect_float(buf + 8, 60.0);
    expect_float(buf + 9, 120.0);
    expect_dword(buf + 10, RGNDATA_PATH);
    expect_dword(buf + 11, 68);
    expect_magic(buf + 12);
    expect_dword(buf + 13, 6);
    expect_float(buf + 14, 0.0);
    expect_float(buf + 15, 50.0);
    expect_float(buf + 16, 70.2);
    expect_float(buf + 17, 60.0);
    expect_float(buf + 18, 102.8);
    expect_float(buf + 19, 55.4);
    expect_float(buf + 20, 122.4);
    expect_float(buf + 21, 40.4);
    expect_float(buf + 22, 60.2);
    expect_float(buf + 23, 45.6);
    expect_float(buf + 24, 20.2);
    expect_float(buf + 25, 50.0);
    expect_float(buf + 26, 70.2);
    expect_dword(buf + 27, 0x01010100);
    ok(*(buf + 28) == 0x00000101 || *(buf + 28) == 0x43050101 /* Win 7 */,
       "expected 00000101 or 43050101 got %08x\n", *(buf + 28));
    expect_dword(buf + 29, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipDeletePath(path);
    expect(Ok, status);
    status = GdipDeleteRegion(region);
    expect(Ok, status);

    /* Test how shorts are stored in the region path data */
    status = GdipCreatePath(FillModeAlternate, &path);
    ok(status == Ok, "status %08x\n", status);
    GdipAddPathRectangleI(path, -1969, -1974, 1995, 1997);

    status = GdipCreateRegionPath(path, &region);
    ok(status == Ok, "status %08x\n", status);
    needed = 0;
    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(56, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(56, needed);
    expect_dword(buf, 48);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_PATH);
    expect_dword(buf + 5, 32);
    expect_magic(buf + 6);
    expect_dword(buf + 7, 4);
    /* flags 0x4000 means that a path is an array of shorts instead of FLOATs */
    expect_dword(buf + 8, 0x4000);
    point = (RegionDataPoint*)(buf + 9);
    expect(-1969, point[0].X);
    expect(-1974, point[0].Y);
    expect(26, point[1].X); /* buf + 10 */
    expect(-1974, point[1].Y);
    expect(26, point[2].X); /* buf + 11 */
    expect(23, point[2].Y);
    expect(-1969, point[3].X); /* buf + 12 */
    expect(23, point[3].Y);
    expect_dword(buf + 13, 0x81010100); /* 0x01010100 if we don't close the path */
    expect_dword(buf + 14, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipDeletePath(path);
    expect(Ok, status);
    status = GdipDeleteRegion(region);
    expect(Ok, status);

    /* Test with integers that can't be stored as shorts */
    status = GdipCreatePath(FillModeAlternate, &path);
    ok(status == Ok, "status %08x\n", status);
    GdipAddPathRectangleI(path, -196900, -197400, 199500, 199700);

    status = GdipCreateRegionPath(path, &region);
    ok(status == Ok, "status %08x\n", status);
    needed = 0;
    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(72, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(72, needed);
    expect_dword(buf, 64);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_PATH);
    expect_dword(buf + 5, 48);
    expect_magic(buf + 6);
    expect_dword(buf + 7, 4);
    /* flags 0 means that a path is an array of FLOATs */
    expect_dword(buf + 8, 0);
    expect_float(buf + 9, -196900.0);
    expect_float(buf + 10, -197400.0);
    expect_float(buf + 11, 2600.0);
    expect_float(buf + 12, -197400.0);
    expect_float(buf + 13, 2600.0);
    expect_float(buf + 14, 2300.0);
    expect_float(buf + 15, -196900.0);
    expect_float(buf + 16, 2300.0);
    expect_dword(buf + 17, 0x81010100); /* 0x01010100 if we don't close the path */
    expect_dword(buf + 18, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipDeletePath(path);
    expect(Ok, status);
    status = GdipDeleteRegion(region);
    expect(Ok, status);

    /* Test beziers */
    GdipCreatePath(FillModeAlternate, &path);
      /* Exactly 90 degrees */
    status = GdipAddPathArc(path, 100.0, 100.0, 500.0, 700.0, 0.0, 90.0);
    expect(Ok, status);
    /* Over 90 degrees */
    status = GdipAddPathArc(path, 100.0, 100.0, 500.0, 700.0, 0.0, 100.0);
    expect(Ok, status);
    status = GdipCreateRegionPath(path, &region);
    ok(status == Ok, "status %08x\n", status);
    needed = 0;
    status = GdipGetRegionDataSize(region, &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(136, needed);
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %08x\n", status);
    expect(136, needed);
    expect_dword(buf, 128);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_PATH);
    expect_dword(buf + 5, 112);
    expect_magic(buf + 6);
    expect_dword(buf + 7, 11);
    /* flags 0 means that a path is an array of FLOATs */
    expect_dword(buf + 8, 0);
    expect_float(buf + 9, 600.0);
    expect_float(buf + 10, 450.0);
    expect_float(buf + 11, 600.0);
    expect_float(buf + 12, 643.299561);
    expect_float(buf + 13, 488.071198);
    expect_float(buf + 14, 800.0);
    expect_float(buf + 15, 350.0);
    expect_float(buf + 16, 800.0);
    expect_float(buf + 17, 600.0);
    expect_float(buf + 18, 450.0);
    expect_float(buf + 19, 600.0);
    expect_float(buf + 20, 643.299622);
    expect_float(buf + 21, 488.071167);
    expect_float(buf + 22, 800.0);
    expect_float(buf + 23, 350.0);
    expect_float(buf + 24, 800.0);
    expect_float(buf + 25, 329.807129);
    expect_float(buf + 26, 800.0);
    expect_float(buf + 27, 309.688568);
    expect_float(buf + 28, 796.574890);
    expect_float(buf + 29, 290.084167);
    expect_float(buf + 30, 789.799561);
    expect_dword(buf + 31, 0x03030300);
    expect_dword(buf + 32, 0x03030301);
    ok(*(buf + 33) == 0x00030303 /* before win7 */ ||
       *(buf + 33) == 0x43030303 /* 32-bit win7 */ || *(buf + 33) == 0x4c030303 /* 64-bit win7 */,
       "expected 0x00030303 or 0x43030303 or 0x4c030303 got %08x\n", *(buf + 33));
    expect_dword(buf + 34, 0xeeeeeeee);
    test_region_data(buf, needed, __LINE__);

    status = GdipDeletePath(path);
    expect(Ok, status);
    status = GdipDeleteRegion(region);
    expect(Ok, status);
}