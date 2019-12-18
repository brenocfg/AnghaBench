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
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpImageAttributes ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  ColorAdjustTypeAny ; 
 int /*<<< orphan*/  ColorAdjustTypeDefault ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdipBitmapGetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipBitmapSetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateImageAttributes (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImageAttributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawImageRectRectI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipResetImageAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetImageAttributesGamma (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat32bppRGB ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  color_match (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_gamma(void)
{
    GpStatus stat;
    GpImageAttributes *imageattr;
    GpBitmap *bitmap1, *bitmap2;
    GpGraphics *graphics;
    ARGB color;

    stat = GdipSetImageAttributesGamma(NULL, ColorAdjustTypeDefault, TRUE, 1.0);
    expect(InvalidParameter, stat);

    stat = GdipCreateImageAttributes(&imageattr);
    expect(Ok, stat);

    stat = GdipSetImageAttributesGamma(imageattr, ColorAdjustTypeDefault, TRUE, 1.0);
    expect(Ok, stat);

    stat = GdipSetImageAttributesGamma(imageattr, ColorAdjustTypeAny, TRUE, 1.0);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesGamma(imageattr, ColorAdjustTypeDefault, TRUE, -1.0);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesGamma(imageattr, ColorAdjustTypeDefault, TRUE, 0.0);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesGamma(imageattr, ColorAdjustTypeDefault, TRUE, 0.5);
    expect(Ok, stat);

    stat = GdipSetImageAttributesGamma(imageattr, ColorAdjustTypeDefault, FALSE, 0.0);
    expect(Ok, stat);

    /* Drawing a bitmap transforms the colors */
    stat = GdipSetImageAttributesGamma(imageattr, ColorAdjustTypeDefault, TRUE, 3.0);
    expect(Ok, stat);

    stat = GdipCreateBitmapFromScan0(1, 1, 0, PixelFormat32bppRGB, NULL, &bitmap1);
    expect(Ok, stat);

    stat = GdipCreateBitmapFromScan0(1, 1, 0, PixelFormat32bppRGB, NULL, &bitmap2);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bitmap1, 0, 0, 0xff80ffff);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap2, &graphics);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage*)bitmap1, 0,0,1,1, 0,0,1,1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff20ffff, color, 1), "Expected ff20ffff, got %.8x\n", color);

    stat = GdipResetImageAttributes(imageattr, ColorAdjustTypeDefault);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage*)bitmap1, 0,0,1,1, 0,0,1,1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff80ffff, color, 1), "Expected ff80ffff, got %.8x\n", color);

    GdipDeleteGraphics(graphics);
    GdipDisposeImage((GpImage*)bitmap1);
    GdipDisposeImage((GpImage*)bitmap2);
    GdipDisposeImageAttributes(imageattr);
}