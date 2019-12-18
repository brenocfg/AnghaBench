#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int GdipCreateRegionRgnData (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int GdipGetRegionData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int GdipIsEmptyRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int GdipIsInfiniteRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_GdipCreateRegionRgnData(void)
{
    GpGraphics *graphics = NULL;
    GpRegion *region, *region2;
    HDC hdc = GetDC(0);
    GpStatus status;
    BYTE buf[512];
    UINT needed;
    BOOL ret;

    status = GdipCreateRegionRgnData(NULL, 0, NULL);
    ok(status == InvalidParameter, "status %d\n", status);

    status = GdipCreateFromHDC(hdc, &graphics);
    ok(status == Ok, "status %d\n", status);

    status = GdipCreateRegion(&region);
    ok(status == Ok, "status %d\n", status);

    /* infinite region */
    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %d\n", status);
    expect(20, needed);

    status = GdipCreateRegionRgnData(buf, needed, NULL);
    ok(status == InvalidParameter, "status %d\n", status);

    status = GdipCreateRegionRgnData(buf, needed, &region2);
    ok(status == Ok, "status %d\n", status);

    ret = FALSE;
    status = GdipIsInfiniteRegion(region2, graphics, &ret);
    ok(status == Ok, "status %d\n", status);
    ok(ret, "got %d\n", ret);
    GdipDeleteRegion(region2);

    /* empty region */
    status = GdipSetEmpty(region);
    ok(status == Ok, "status %d\n", status);

    memset(buf, 0xee, sizeof(buf));
    needed = 0;
    status = GdipGetRegionData(region, (BYTE*)buf, sizeof(buf), &needed);
    ok(status == Ok, "status %d\n", status);
    expect(20, needed);

    status = GdipCreateRegionRgnData(buf, needed, &region2);
    ok(status == Ok, "status %d\n", status);

    ret = FALSE;
    status = GdipIsEmptyRegion(region2, graphics, &ret);
    ok(status == Ok, "status %d\n", status);
    ok(ret, "got %d\n", ret);
    GdipDeleteRegion(region2);

    GdipDeleteGraphics(graphics);
    GdipDeleteRegion(region);
    ReleaseDC(0, hdc);
}