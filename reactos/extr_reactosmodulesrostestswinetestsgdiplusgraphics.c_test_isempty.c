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
 int /*<<< orphan*/  GdipIsClipEmpty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 

__attribute__((used)) static void test_isempty(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC( hwnd );
    GpRegion *clip;
    BOOL res;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipCreateRegion(&clip);
    expect(Ok, status);

    /* NULL */
    status = GdipIsClipEmpty(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsClipEmpty(graphics, NULL);
    expect(InvalidParameter, status);
    status = GdipIsClipEmpty(NULL, &res);
    expect(InvalidParameter, status);

    /* default is infinite */
    res = TRUE;
    status = GdipIsClipEmpty(graphics, &res);
    expect(Ok, status);
    expect(FALSE, res);

    GdipDeleteRegion(clip);

    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);
}