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
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsEmptyRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_isempty(void)
{
    GpStatus status;
    GpRegion *region;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC(0);
    BOOL res;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    status = GdipCreateRegion(&region);
    expect(Ok, status);

    /* NULL arguments */
    status = GdipIsEmptyRegion(NULL, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsEmptyRegion(region, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsEmptyRegion(NULL, graphics, NULL);
    expect(InvalidParameter, status);
    status = GdipIsEmptyRegion(NULL, NULL, &res);
    expect(InvalidParameter, status);
    status = GdipIsEmptyRegion(region, NULL, &res);
    expect(InvalidParameter, status);

    /* default is infinite */
    res = TRUE;
    status = GdipIsEmptyRegion(region, graphics, &res);
    expect(Ok, status);
    expect(FALSE, res);

    status = GdipSetEmpty(region);
    expect(Ok, status);

    res = FALSE;
    status = GdipIsEmptyRegion(region, graphics, &res);
    expect(Ok, status);
    expect(TRUE, res);

    GdipDeleteRegion(region);
    GdipDeleteGraphics(graphics);
    ReleaseDC(0, hdc);
}