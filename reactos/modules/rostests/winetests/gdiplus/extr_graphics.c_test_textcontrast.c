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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetTextContrast (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 

__attribute__((used)) static void test_textcontrast(void)
{
    GpStatus status;
    HDC hdc = GetDC( hwnd );
    GpGraphics *graphics;
    UINT contrast;

    status = GdipGetTextContrast(NULL, NULL);
    expect(InvalidParameter, status);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipGetTextContrast(graphics, NULL);
    expect(InvalidParameter, status);
    status = GdipGetTextContrast(graphics, &contrast);
    expect(Ok, status);
    expect(4, contrast);

    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);
}