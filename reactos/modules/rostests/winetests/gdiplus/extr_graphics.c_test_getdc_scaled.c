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
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipScaleWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  RGB (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_getdc_scaled(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpBitmap *bitmap = NULL;
    HDC hdc=NULL;
    HBRUSH hbrush, holdbrush;
    ARGB color;

    status = GdipCreateBitmapFromScan0(10, 10, 12, PixelFormat24bppRGB, NULL, &bitmap);
    expect(Ok, status);

    status = GdipGetImageGraphicsContext((GpImage*)bitmap, &graphics);
    expect(Ok, status);

    status = GdipScaleWorldTransform(graphics, 2.0, 2.0, MatrixOrderPrepend);
    expect(Ok, status);

    status = GdipGetDC(graphics, &hdc);
    expect(Ok, status);
    ok(hdc != NULL, "got NULL hdc\n");

    hbrush = CreateSolidBrush(RGB(255, 0, 0));

    holdbrush = SelectObject(hdc, hbrush);

    Rectangle(hdc, 2, 2, 6, 6);

    SelectObject(hdc, holdbrush);

    DeleteObject(hbrush);

    status = GdipReleaseDC(graphics, hdc);
    expect(Ok, status);

    GdipDeleteGraphics(graphics);

    status = GdipBitmapGetPixel(bitmap, 3, 3, &color);
    expect(Ok, status);
    expect(0xffff0000, color);

    status = GdipBitmapGetPixel(bitmap, 8, 8, &color);
    expect(Ok, status);
    expect(0xff000000, color);

    GdipDisposeImage((GpImage*)bitmap);
}