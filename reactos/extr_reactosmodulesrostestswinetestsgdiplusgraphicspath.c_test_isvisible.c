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
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsVisiblePathPoint (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetClipRect (int /*<<< orphan*/ *,double,double,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_isvisible(void)
{
    GpPath *path;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC(0);
    BOOL result;
    GpStatus status;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);

    /* NULL */
    status = GdipIsVisiblePathPoint(NULL, 0.0, 0.0, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, graphics, NULL);
    expect(InvalidParameter, status);

    /* empty path */
    result = TRUE;
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, NULL, &result);
    expect(Ok, status);
    expect(FALSE, result);
    /* rect */
    status = GdipAddPathRectangle(path, 0.0, 0.0, 10.0, 10.0);
    expect(Ok, status);
    result = FALSE;
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, NULL, &result);
    expect(Ok, status);
    expect(TRUE, result);
    result = TRUE;
    status = GdipIsVisiblePathPoint(path, 11.0, 11.0, NULL, &result);
    expect(Ok, status);
    expect(FALSE, result);
    /* not affected by clipping */
    status = GdipSetClipRect(graphics, 5.0, 5.0, 5.0, 5.0, CombineModeReplace);
    expect(Ok, status);
    result = FALSE;
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, graphics, &result);
    expect(Ok, status);
    expect(TRUE, result);

    GdipDeletePath(path);
    GdipDeleteGraphics(graphics);
    ReleaseDC(0, hdc);
}