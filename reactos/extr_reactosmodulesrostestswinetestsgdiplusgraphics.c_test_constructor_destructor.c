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
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFromHWND (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFromHWNDICM (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  OutOfMemory ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 

__attribute__((used)) static void test_constructor_destructor(void)
{
    GpStatus stat;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC( hwnd );

    stat = GdipCreateFromHDC(NULL, &graphics);
    expect(OutOfMemory, stat);
    stat = GdipDeleteGraphics(graphics);
    expect(InvalidParameter, stat);

    stat = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, stat);
    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipCreateFromHWND(NULL, &graphics);
    expect(Ok, stat);
    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipCreateFromHWNDICM(NULL, &graphics);
    expect(Ok, stat);
    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipDeleteGraphics(NULL);
    expect(InvalidParameter, stat);
    ReleaseDC(hwnd, hdc);
}