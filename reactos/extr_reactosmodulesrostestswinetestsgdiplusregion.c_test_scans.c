#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_7__ {int X; int Y; int Width; int Height; } ;
struct TYPE_6__ {double X; double Y; double Width; double Height; } ;
typedef  int INT ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpRect ;
typedef  int /*<<< orphan*/  GpMatrix ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  CombineModeUnion ; 
 int GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int GdipGetRegionScans (int /*<<< orphan*/ *,TYPE_1__*,int*,int /*<<< orphan*/ *) ; 
 int GdipGetRegionScansCount (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int GdipGetRegionScansI (int /*<<< orphan*/ *,TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,double) ; 

__attribute__((used)) static void test_scans(void)
{
    GpRegion *region;
    GpMatrix *matrix;
    GpRectF rectf;
    GpStatus status;
    ULONG count=80085;
    INT icount;
    GpRectF scans[2];
    GpRect scansi[2];

    status = GdipCreateRegion(&region);
    expect(Ok, status);

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);

    /* test NULL values */
    status = GdipGetRegionScansCount(NULL, &count, matrix);
    expect(InvalidParameter, status);

    status = GdipGetRegionScansCount(region, NULL, matrix);
    expect(InvalidParameter, status);

    status = GdipGetRegionScansCount(region, &count, NULL);
    expect(InvalidParameter, status);

    status = GdipGetRegionScans(NULL, scans, &icount, matrix);
    expect(InvalidParameter, status);

    status = GdipGetRegionScans(region, scans, NULL, matrix);
    expect(InvalidParameter, status);

    status = GdipGetRegionScans(region, scans, &icount, NULL);
    expect(InvalidParameter, status);

    /* infinite */
    status = GdipGetRegionScansCount(region, &count, matrix);
    expect(Ok, status);
    expect(1, count);

    status = GdipGetRegionScans(region, NULL, &icount, matrix);
    expect(Ok, status);
    expect(1, icount);

    status = GdipGetRegionScans(region, scans, &icount, matrix);
    expect(Ok, status);
    expect(1, icount);

    status = GdipGetRegionScansI(region, scansi, &icount, matrix);
    expect(Ok, status);
    expect(1, icount);
    expect(-0x400000, scansi[0].X);
    expect(-0x400000, scansi[0].Y);
    expect(0x800000, scansi[0].Width);
    expect(0x800000, scansi[0].Height);

    status = GdipGetRegionScans(region, scans, &icount, matrix);
    expect(Ok, status);
    expect(1, icount);
    expectf((double)-0x400000, scans[0].X);
    expectf((double)-0x400000, scans[0].Y);
    expectf((double)0x800000, scans[0].Width);
    expectf((double)0x800000, scans[0].Height);

    /* empty */
    status = GdipSetEmpty(region);
    expect(Ok, status);

    status = GdipGetRegionScansCount(region, &count, matrix);
    expect(Ok, status);
    expect(0, count);

    status = GdipGetRegionScans(region, scans, &icount, matrix);
    expect(Ok, status);
    expect(0, icount);

    /* single rectangle */
    rectf.X = rectf.Y = 0.0;
    rectf.Width = rectf.Height = 5.0;
    status = GdipCombineRegionRect(region, &rectf, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetRegionScansCount(region, &count, matrix);
    expect(Ok, status);
    expect(1, count);

    status = GdipGetRegionScans(region, scans, &icount, matrix);
    expect(Ok, status);
    expect(1, icount);
    expectf(0.0, scans[0].X);
    expectf(0.0, scans[0].Y);
    expectf(5.0, scans[0].Width);
    expectf(5.0, scans[0].Height);

    /* two rectangles */
    rectf.X = rectf.Y = 5.0;
    rectf.Width = rectf.Height = 5.0;
    status = GdipCombineRegionRect(region, &rectf, CombineModeUnion);
    expect(Ok, status);

    status = GdipGetRegionScansCount(region, &count, matrix);
    expect(Ok, status);
    expect(2, count);

    /* Native ignores the initial value of count */
    scans[1].X = scans[1].Y = scans[1].Width = scans[1].Height = 8.0;
    icount = 1;
    status = GdipGetRegionScans(region, scans, &icount, matrix);
    expect(Ok, status);
    expect(2, icount);
    expectf(0.0, scans[0].X);
    expectf(0.0, scans[0].Y);
    expectf(5.0, scans[0].Width);
    expectf(5.0, scans[0].Height);
    expectf(5.0, scans[1].X);
    expectf(5.0, scans[1].Y);
    expectf(5.0, scans[1].Width);
    expectf(5.0, scans[1].Height);

    status = GdipGetRegionScansI(region, scansi, &icount, matrix);
    expect(Ok, status);
    expect(2, icount);
    expect(0, scansi[0].X);
    expect(0, scansi[0].Y);
    expect(5, scansi[0].Width);
    expect(5, scansi[0].Height);
    expect(5, scansi[1].X);
    expect(5, scansi[1].Y);
    expect(5, scansi[1].Width);
    expect(5, scansi[1].Height);

    status = GdipDeleteRegion(region);
    expect(Ok, status);
    status = GdipDeleteMatrix(matrix);
    expect(Ok, status);
}