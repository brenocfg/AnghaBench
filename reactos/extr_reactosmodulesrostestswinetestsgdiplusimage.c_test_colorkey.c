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
 int /*<<< orphan*/  ColorAdjustTypeCount ; 
 int /*<<< orphan*/  ColorAdjustTypeDefault ; 
 int /*<<< orphan*/  GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipBitmapSetPixel (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateImageAttributes (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImageAttributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawImageRectRectI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipResetImageAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetImageAttributesColorKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  color_match (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_colorkey(void)
{
    GpStatus stat;
    GpImageAttributes *imageattr;
    GpBitmap *bitmap1, *bitmap2;
    GpGraphics *graphics;
    ARGB color;

    stat = GdipSetImageAttributesColorKeys(NULL, ColorAdjustTypeDefault, TRUE, 0xff405060, 0xff708090);
    expect(InvalidParameter, stat);

    stat = GdipCreateImageAttributes(&imageattr);
    expect(Ok, stat);

    stat = GdipSetImageAttributesColorKeys(imageattr, ColorAdjustTypeCount, TRUE, 0xff405060, 0xff708090);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesColorKeys(imageattr, ColorAdjustTypeAny, TRUE, 0xff405060, 0xff708090);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesColorKeys(imageattr, ColorAdjustTypeDefault, TRUE, 0xff405060, 0xff708090);
    expect(Ok, stat);

    stat = GdipCreateBitmapFromScan0(2, 2, 0, PixelFormat32bppARGB, NULL, &bitmap1);
    expect(Ok, stat);

    stat = GdipCreateBitmapFromScan0(2, 2, 0, PixelFormat32bppARGB, NULL, &bitmap2);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bitmap1, 0, 0, 0x20405060);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bitmap1, 0, 1, 0x40506070);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bitmap1, 1, 0, 0x60708090);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bitmap1, 1, 1, 0xffffffff);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap2, &graphics);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage*)bitmap1, 0,0,2,2, 0,0,2,2,
	UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0x00000000, color, 1), "Expected 00000000, got %.8x\n", color);

    stat = GdipBitmapGetPixel(bitmap2, 0, 1, &color);
    expect(Ok, stat);
    ok(color_match(0x00000000, color, 1), "Expected 00000000, got %.8x\n", color);

    stat = GdipBitmapGetPixel(bitmap2, 1, 0, &color);
    expect(Ok, stat);
    ok(color_match(0x00000000, color, 1), "Expected 00000000, got %.8x\n", color);

    stat = GdipBitmapGetPixel(bitmap2, 1, 1, &color);
    expect(Ok, stat);
    ok(color_match(0xffffffff, color, 1), "Expected ffffffff, got %.8x\n", color);

    stat = GdipResetImageAttributes(imageattr, ColorAdjustTypeDefault);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage*)bitmap1, 0,0,2,2, 0,0,2,2,
	UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0x20405060, color, 1), "Expected 20405060, got %.8x\n", color);

    stat = GdipBitmapGetPixel(bitmap2, 0, 1, &color);
    expect(Ok, stat);
    ok(color_match(0x40506070, color, 1), "Expected 40506070, got %.8x\n", color);

    stat = GdipBitmapGetPixel(bitmap2, 1, 0, &color);
    expect(Ok, stat);
    ok(color_match(0x60708090, color, 1), "Expected 60708090, got %.8x\n", color);

    stat = GdipBitmapGetPixel(bitmap2, 1, 1, &color);
    expect(Ok, stat);
    ok(color_match(0xffffffff, color, 1), "Expected ffffffff, got %.8x\n", color);


    GdipDeleteGraphics(graphics);
    GdipDisposeImage((GpImage*)bitmap1);
    GdipDisposeImage((GpImage*)bitmap2);
    GdipDisposeImageAttributes(imageattr);
}