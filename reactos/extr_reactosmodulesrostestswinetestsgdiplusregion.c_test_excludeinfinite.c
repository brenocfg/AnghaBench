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
typedef  int UINT ;
struct TYPE_6__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_5__ {double member_0; double member_1; double member_2; double member_3; } ;
typedef  TYPE_1__ RectF ;
typedef  int /*<<< orphan*/  INT ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_2__ GpRectF ;
typedef  int /*<<< orphan*/  GpMatrix ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeExclude ; 
 int GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int GdipGetRegionScans (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetRegionScansCount (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int Ok ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_excludeinfinite(void)
{
    GpStatus status;
    GpRegion *region;
    UINT count=0xdeadbeef;
    GpRectF scans[4];
    GpMatrix *identity;
    static const RectF rect_exclude = {0.0, 0.0, 1.0, 1.0};

    status = GdipCreateMatrix(&identity);
    expect(Ok, status);

    status = GdipCreateRegion(&region);
    expect(Ok, status);

    status = GdipCombineRegionRect(region, &rect_exclude, CombineModeExclude);
    expect(Ok, status);

    status = GdipGetRegionScansCount(region, &count, identity);
    expect(Ok, status);
    expect(4, count);

    count = 4;
    status = GdipGetRegionScans(region, scans, (INT*)&count, identity);
    expect(Ok, status);

    expectf(-4194304.0, scans[0].X);
    expectf(-4194304.0, scans[0].Y);
    expectf(8388608.0, scans[0].Width);
    expectf(4194304.0, scans[0].Height);

    expectf(-4194304.0, scans[1].X);
    expectf(0.0, scans[1].Y);
    expectf(4194304.0, scans[1].Width);
    expectf(1.0, scans[1].Height);

    expectf(1.0, scans[2].X);
    expectf(0.0, scans[2].Y);
    expectf(4194303.0, scans[2].Width);
    expectf(1.0, scans[2].Height);

    expectf(-4194304.0, scans[3].X);
    expectf(1.0, scans[3].Y);
    expectf(8388608.0, scans[3].Width);
    expectf(4194303.0, scans[3].Height);

    GdipDeleteRegion(region);
    GdipDeleteMatrix(identity);
}