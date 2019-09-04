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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {double X; double Y; double Width; double Height; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int CombineModeReplace ; 
 int CombineModeUnion ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathEllipse (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCombineRegionPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  GdipCombineRegionRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegionRect (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetRegionData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetRegionDataSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Ok ; 
 int RGNDATA_INFINITE_RECT ; 
 int RGNDATA_PATH ; 
 int RGNDATA_RECT ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_dword (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  expect_magic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_combinereplace(void)
{
    GpStatus status;
    GpRegion *region, *region2;
    GpPath *path;
    GpRectF rectf;
    UINT needed;
    DWORD buf[50];

    rectf.X = rectf.Y = 0.0;
    rectf.Width = rectf.Height = 100.0;

    status = GdipCreateRegionRect(&rectf, &region);
    expect(Ok, status);

    /* replace with the same rectangle */
    status = GdipCombineRegionRect(region, &rectf,CombineModeReplace);
    expect(Ok, status);

    status = GdipGetRegionDataSize(region, &needed);
    expect(Ok, status);
    expect(36, needed);
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    expect(Ok, status);
    expect(36, needed);
    expect_dword(buf, 28);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_RECT);

    /* replace with path */
    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);
    status = GdipAddPathEllipse(path, 0.0, 0.0, 100.0, 250.0);
    expect(Ok, status);
    status = GdipCombineRegionPath(region, path, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetRegionDataSize(region, &needed);
    expect(Ok, status);
    expect(156, needed);
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    expect(Ok, status);
    expect(156, needed);
    expect_dword(buf, 148);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_PATH);
    GdipDeletePath(path);

    /* replace with infinite rect */
    status = GdipCreateRegion(&region2);
    expect(Ok, status);
    status = GdipCombineRegionRegion(region, region2, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetRegionDataSize(region, &needed);
    expect(Ok, status);
    expect(20, needed);
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    expect(Ok, status);
    expect(20, needed);
    expect_dword(buf, 12);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 0);
    expect_dword(buf + 4, RGNDATA_INFINITE_RECT);
    GdipDeleteRegion(region2);

    /* more complex case : replace with a combined region */
    status = GdipCreateRegionRect(&rectf, &region2);
    expect(Ok, status);
    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);
    status = GdipAddPathEllipse(path, 0.0, 0.0, 100.0, 250.0);
    expect(Ok, status);
    status = GdipCombineRegionPath(region2, path, CombineModeUnion);
    expect(Ok, status);
    GdipDeletePath(path);
    status = GdipCombineRegionRegion(region, region2, CombineModeReplace);
    expect(Ok, status);
    GdipDeleteRegion(region2);

    status = GdipGetRegionDataSize(region, &needed);
    expect(Ok, status);
    expect(180, needed);
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    expect(Ok, status);
    expect(180, needed);
    expect_dword(buf, 172);
    trace("buf[1] = %08x\n", buf[1]);
    expect_magic(buf + 2);
    expect_dword(buf + 3, 2);
    expect_dword(buf + 4, CombineModeUnion);

    GdipDeleteRegion(region);
}