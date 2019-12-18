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
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 scalar_t__ GdipAddPathEllipse (int /*<<< orphan*/ *,double,double,double,double) ; 
 scalar_t__ GdipCombineRegionPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipCreateRegion (int /*<<< orphan*/ **) ; 
 scalar_t__ GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipDeletePath (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipIsEqualRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GdipResetPath (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipSetEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipTranslateRegion (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidParameter ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_translate(void)
{
    GpRegion *region, *region2;
    GpGraphics *graphics;
    GpPath *path;
    GpRectF rectf;
    GpStatus status;
    HDC hdc = GetDC(0);
    BOOL res;

    status = GdipCreateFromHDC(hdc, &graphics);
    ok(status == Ok, "status %08x\n", status);

    status = GdipCreatePath(FillModeAlternate, &path);
    ok(status == Ok, "status %08x\n", status);

    status = GdipCreateRegion(&region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCreateRegion(&region2);
    ok(status == Ok, "status %08x\n", status);

    /* NULL */
    status = GdipTranslateRegion(NULL, 0.0, 0.0);
    ok(status == InvalidParameter, "status %08x\n", status);

    /* infinite */
    status = GdipTranslateRegion(region, 10.0, 10.0);
    ok(status == Ok, "status %08x\n", status);
    /* empty */
    status = GdipSetEmpty(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipTranslateRegion(region, 10.0, 10.0);
    ok(status == Ok, "status %08x\n", status);
    /* rect */
    rectf.X = 10.0; rectf.Y = 0.0;
    rectf.Width = rectf.Height = 100.0;
    status = GdipCombineRegionRect(region, &rectf, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    rectf.X = 15.0; rectf.Y = -2.0;
    rectf.Width = rectf.Height = 100.0;
    status = GdipCombineRegionRect(region2, &rectf, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    status = GdipTranslateRegion(region, 5.0, -2.0);
    ok(status == Ok, "status %08x\n", status);
    res = FALSE;
    status = GdipIsEqualRegion(region, region2, graphics, &res);
    ok(status == Ok, "status %08x\n", status);
    ok(res, "Expected to be equal.\n");
    /* path */
    status = GdipAddPathEllipse(path, 0.0, 10.0, 100.0, 150.0);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCombineRegionPath(region, path, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    status = GdipResetPath(path);
    ok(status == Ok, "status %08x\n", status);
    status = GdipAddPathEllipse(path, 10.0, 21.0, 100.0, 150.0);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCombineRegionPath(region2, path, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    status = GdipTranslateRegion(region, 10.0, 11.0);
    ok(status == Ok, "status %08x\n", status);
    res = FALSE;
    status = GdipIsEqualRegion(region, region2, graphics, &res);
    ok(status == Ok, "status %08x\n", status);
    ok(res, "Expected to be equal.\n");

    status = GdipDeleteRegion(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeleteRegion(region2);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeleteGraphics(graphics);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeletePath(path);
    ok(status == Ok, "status %08x\n", status);
    ReleaseDC(0, hdc);
}