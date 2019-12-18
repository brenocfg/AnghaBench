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
typedef  int /*<<< orphan*/  REAL ;
typedef  int /*<<< orphan*/  PixelFormat ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateBitmapFromGraphics (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetDpiX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetDpiY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageHeight (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageHorizontalResolution (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImagePixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageVerticalResolution (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageWidth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int InvalidParameter ; 
 int Ok ; 
 int PixelFormat32bppPARGB ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 

__attribute__((used)) static void test_bitmapfromgraphics(void)
{
    GpStatus stat;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC( hwnd );
    GpBitmap *bitmap = NULL;
    PixelFormat format;
    REAL imageres, graphicsres;
    UINT width, height;

    stat = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, stat);

    stat = GdipCreateBitmapFromGraphics(12, 13, NULL, &bitmap);
    expect(InvalidParameter, stat);

    stat = GdipCreateBitmapFromGraphics(12, 13, graphics, NULL);
    expect(InvalidParameter, stat);

    stat = GdipCreateBitmapFromGraphics(12, 13, graphics, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImagePixelFormat((GpImage*)bitmap, &format);
    expect(Ok, stat);
    expect(PixelFormat32bppPARGB, format);

    stat = GdipGetDpiX(graphics, &graphicsres);
    expect(Ok, stat);

    stat = GdipGetImageHorizontalResolution((GpImage*)bitmap, &imageres);
    expect(Ok, stat);
    expectf(graphicsres, imageres);

    stat = GdipGetDpiY(graphics, &graphicsres);
    expect(Ok, stat);

    stat = GdipGetImageVerticalResolution((GpImage*)bitmap, &imageres);
    expect(Ok, stat);
    expectf(graphicsres, imageres);

    stat = GdipGetImageWidth((GpImage*)bitmap, &width);
    expect(Ok, stat);
    expect(12, width);

    stat = GdipGetImageHeight((GpImage*)bitmap, &height);
    expect(Ok, stat);
    expect(13, height);

    GdipDeleteGraphics(graphics);
    GdipDisposeImage((GpImage*)bitmap);
}