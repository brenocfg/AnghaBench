#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double member_0; double member_1; double member_2; double member_3; } ;
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int INT ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_2__ GpRectF ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeComplement ; 
 int /*<<< orphan*/  CombineModeExclude ; 
 int /*<<< orphan*/  CombineModeIntersect ; 
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  CombineModeUnion ; 
 int /*<<< orphan*/  CombineModeXor ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int GdipCombineRegionRect (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int GdipCreateRegionPath (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipCreateRegionRect (TYPE_2__ const*,int /*<<< orphan*/ **) ; 
 int GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int GdipDeletePath (int /*<<< orphan*/ *) ; 
 int GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int GdipGetRegionHRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipScaleWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int GdipSetInfinite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetRgnBox (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SIMPLEREGION ; 
 int /*<<< orphan*/  SetViewportOrgEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  verify_region (int /*<<< orphan*/ *,TYPE_1__ const*) ; 

__attribute__((used)) static void test_gethrgn(void)
{
    GpStatus status;
    GpRegion *region, *region2;
    GpPath *path;
    GpGraphics *graphics;
    HRGN hrgn;
    HDC hdc=GetDC(0);
    INT rgntype;
    RECT rgnbox;
    static const RECT empty_rect = {0,0,0,0};
    static const RECT test_rect = {10, 11, 20, 21};
    static const GpRectF test_rectF = {10.0, 11.0, 10.0, 10.0};
    static const RECT scaled_rect = {20, 22, 40, 42};
    static const RECT test_rect2 = {10, 21, 20, 31};
    static const GpRectF test_rect2F = {10.0, 21.0, 10.0, 10.0};
    static const RECT test_rect3 = {10, 11, 20, 31};
    static const GpRectF test_rect3F = {10.0, 11.0, 10.0, 20.0};

    status = GdipCreateFromHDC(hdc, &graphics);
    ok(status == Ok, "status %08x\n", status);

    status = GdipCreateRegion(&region);
    ok(status == Ok, "status %08x\n", status);

    status = GdipGetRegionHRgn(NULL, graphics, &hrgn);
    ok(status == InvalidParameter, "status %08x\n", status);
    status = GdipGetRegionHRgn(region, graphics, NULL);
    ok(status == InvalidParameter, "status %08x\n", status);

    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    ok(hrgn == NULL, "hrgn=%p\n", hrgn);

    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    ok(hrgn == NULL, "hrgn=%p\n", hrgn);

    status = GdipSetEmpty(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &empty_rect);
    DeleteObject(hrgn);

    status = GdipCreatePath(FillModeAlternate, &path);
    ok(status == Ok, "status %08x\n", status);
    status = GdipAddPathRectangle(path, 10.0, 11.0, 10.0, 10.0);
    ok(status == Ok, "status %08x\n", status);

    status = GdipCreateRegionPath(path, &region2);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionHRgn(region2, NULL, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &test_rect);
    DeleteObject(hrgn);

    /* resulting HRGN is in device coordinates */
    status = GdipScaleWorldTransform(graphics, 2.0, 2.0, MatrixOrderPrepend);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionHRgn(region2, graphics, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &scaled_rect);
    DeleteObject(hrgn);

    status = GdipCombineRegionRect(region2, &test_rectF, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionHRgn(region2, NULL, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &test_rect);
    DeleteObject(hrgn);

    status = GdipGetRegionHRgn(region2, graphics, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &scaled_rect);
    DeleteObject(hrgn);

    status = GdipSetInfinite(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCombineRegionRect(region, &test_rectF, CombineModeIntersect);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &test_rect);
    DeleteObject(hrgn);

    status = GdipCombineRegionRect(region, &test_rectF, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCombineRegionRect(region, &test_rect2F, CombineModeUnion);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &test_rect3);
    DeleteObject(hrgn);

    status = GdipCombineRegionRect(region, &test_rect3F, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCombineRegionRect(region, &test_rect2F, CombineModeXor);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &test_rect);
    DeleteObject(hrgn);

    status = GdipCombineRegionRect(region, &test_rect3F, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCombineRegionRect(region, &test_rectF, CombineModeExclude);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &test_rect2);
    DeleteObject(hrgn);

    status = GdipCombineRegionRect(region, &test_rectF, CombineModeReplace);
    ok(status == Ok, "status %08x\n", status);
    status = GdipCombineRegionRect(region, &test_rect3F, CombineModeComplement);
    ok(status == Ok, "status %08x\n", status);
    status = GdipGetRegionHRgn(region, NULL, &hrgn);
    ok(status == Ok, "status %08x\n", status);
    verify_region(hrgn, &test_rect2);
    DeleteObject(hrgn);

    status = GdipDeletePath(path);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeleteRegion(region);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeleteRegion(region2);
    ok(status == Ok, "status %08x\n", status);
    status = GdipDeleteGraphics(graphics);
    ok(status == Ok, "status %08x\n", status);

    /* test with gdi32 transform */
    SetViewportOrgEx(hdc, 10, 10, NULL);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipCreateRegionRect(&test_rectF, &region);
    expect(Ok, status);

    status = GdipGetRegionHRgn(region, graphics, &hrgn);
    expect(Ok, status);

    rgntype = GetRgnBox(hrgn, &rgnbox);
    DeleteObject(hrgn);

    expect(SIMPLEREGION, rgntype);
    expect(20, rgnbox.left);
    expect(21, rgnbox.top);
    expect(30, rgnbox.right);
    expect(31, rgnbox.bottom);

    status = GdipDeleteRegion(region);
    expect(Ok, status);
    status = GdipDeleteGraphics(graphics);
    expect(Ok, status);

    SetViewportOrgEx(hdc, 0, 0, NULL);

    ReleaseDC(0, hdc);
}