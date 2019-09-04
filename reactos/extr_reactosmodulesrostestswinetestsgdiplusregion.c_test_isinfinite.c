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
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateMatrix2 (double,double,double,double,double,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsInfiniteRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_isinfinite(void)
{
    GpStatus status;
    GpRegion *region;
    GpGraphics *graphics = NULL;
    GpMatrix *m;
    HDC hdc = GetDC(0);
    BOOL res;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    status = GdipCreateRegion(&region);
    expect(Ok, status);

    GdipCreateMatrix2(3.0, 0.0, 0.0, 1.0, 20.0, 30.0, &m);

    /* NULL arguments */
    status = GdipIsInfiniteRegion(NULL, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsInfiniteRegion(region, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsInfiniteRegion(NULL, graphics, NULL);
    expect(InvalidParameter, status);
    status = GdipIsInfiniteRegion(NULL, NULL, &res);
    expect(InvalidParameter, status);
    status = GdipIsInfiniteRegion(region, NULL, &res);
    expect(InvalidParameter, status);

    res = FALSE;
    status = GdipIsInfiniteRegion(region, graphics, &res);
    expect(Ok, status);
    expect(TRUE, res);

    /* after world transform */
    status = GdipSetWorldTransform(graphics, m);
    expect(Ok, status);

    res = FALSE;
    status = GdipIsInfiniteRegion(region, graphics, &res);
    expect(Ok, status);
    expect(TRUE, res);

    GdipDeleteMatrix(m);
    GdipDeleteRegion(region);
    GdipDeleteGraphics(graphics);
    ReleaseDC(0, hdc);
}