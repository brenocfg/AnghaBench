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
typedef  int /*<<< orphan*/  GpRectF ;
typedef  int /*<<< orphan*/  GpRect ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetVisibleClipBounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetVisibleClipBoundsI (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_GdipGetVisibleClipBounds_screen () ; 
 int /*<<< orphan*/  test_GdipGetVisibleClipBounds_window () ; 

__attribute__((used)) static void test_GdipGetVisibleClipBounds(void)
{
    GpGraphics* graphics = NULL;
    GpRectF rectf;
    GpRect rect;
    HDC hdc = GetDC( hwnd );
    GpStatus status;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    /* test null parameters */
    status = GdipGetVisibleClipBounds(graphics, NULL);
    expect(InvalidParameter, status);

    status = GdipGetVisibleClipBounds(NULL, &rectf);
    expect(InvalidParameter, status);

    status = GdipGetVisibleClipBoundsI(graphics, NULL);
    expect(InvalidParameter, status);

    status = GdipGetVisibleClipBoundsI(NULL, &rect);
    expect(InvalidParameter, status);

    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);

    test_GdipGetVisibleClipBounds_screen();
    test_GdipGetVisibleClipBounds_window();
}