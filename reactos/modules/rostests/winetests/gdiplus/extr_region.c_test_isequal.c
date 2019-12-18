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
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipCreateRegion (int /*<<< orphan*/ **) ; 
 scalar_t__ GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipIsEqualRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GdipSetEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipSetInfinite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidParameter ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_isequal(void)
{
    GpRegion *region1, *region2;
    GpGraphics *graphics;
    GpRectF rectf;
    GpStatus status;
    HDC hdc = GetDC(0);
    BOOL res;

    status = GdipCreateFromHDC(hdc, &graphics);
    ok(status == Ok, "status %08x\n", status);

    status = GdipCreateRegion(&region1);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCreateRegion(&region2);
    ok(status == Ok, "status %08x\n", status);

    /* NULL */
    status = GdipIsEqualRegion(NULL, NULL, NULL, NULL);
    ok(status == InvalidParameter, "status %08x\n", status);
    status = GdipIsEqualRegion(region1, region2, NULL, NULL);
    ok(status == InvalidParameter, "status %08x\n", status);
    status = GdipIsEqualRegion(region1, region2, graphics, NULL);
    ok(status == InvalidParameter, "status %08x\n", status);
    status = GdipIsEqualRegion(region1, region2, NULL, &res);
    ok(status == InvalidParameter, "status %08x\n", status);

    /* infinite regions */
    res = FALSE;
    status = GdipIsEqualRegion(region1, region2, graphics, &res);
    ok(status == Ok, "status %08x\n", status);
    ok(res, "Expected to be equal.\n");
    /* empty regions */
    status = GdipSetEmpty(region1);
    ok(status == Ok, "status %08x\n", status);
    status = GdipSetEmpty(region2);
    ok(status == Ok, "status %08x\n", status);
    res = FALSE;
    status = GdipIsEqualRegion(region1, region2, graphics, &res);
    ok(status == Ok, "status %08x\n", status);
    ok(res, "Expected to be equal.\n");
    /* empty & infinite */
    status = GdipSetInfinite(region1);
    ok(status == Ok, "status %08x\n", status);
    res = TRUE;
    status = GdipIsEqualRegion(region1, region2, graphics, &res);
    ok(status == Ok, "status %08x\n", status);
    ok(!res, "Expected to be unequal.\n");
    /* rect & (inf/empty) */
    rectf.X = rectf.Y = 0.0;
    rectf.Width = rectf.Height = 100.0;
    status = GdipCombineRegionRect(region1, &rectf, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    res = TRUE;
    status = GdipIsEqualRegion(region1, region2, graphics, &res);
    ok(status == Ok, "status %08x\n", status);
    ok(!res, "Expected to be unequal.\n");
    status = GdipSetInfinite(region2);
    ok(status == Ok, "status %08x\n", status);
    res = TRUE;
    status = GdipIsEqualRegion(region1, region2, graphics, &res);
    ok(status == Ok, "status %08x\n", status);
    ok(!res, "Expected to be unequal.\n");
    /* roughly equal rectangles */
    rectf.X = rectf.Y = 0.0;
    rectf.Width = rectf.Height = 100.001;
    status = GdipCombineRegionRect(region2, &rectf, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    res = FALSE;
    status = GdipIsEqualRegion(region1, region2, graphics, &res);
    ok(status == Ok, "status %08x\n", status);
    ok(res, "Expected to be equal.\n");
    /* equal rectangles */
    rectf.X = rectf.Y = 0.0;
    rectf.Width = rectf.Height = 100.0;
    status = GdipCombineRegionRect(region2, &rectf, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    res = FALSE;
    status = GdipIsEqualRegion(region1, region2, graphics, &res);
    ok(status == Ok, "status %08x\n", status);
    ok(res, "Expected to be equal.\n");

    /* cleanup */
    status = GdipDeleteRegion(region1);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeleteRegion(region2);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeleteGraphics(graphics);
    ok(status == Ok, "status %08x\n", status);
    ReleaseDC(0, hdc);
}