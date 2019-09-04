#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int Argb; } ;
struct TYPE_7__ {int Argb; } ;
struct TYPE_9__ {TYPE_2__ newColor; TYPE_1__ oldColor; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpImageAttributes ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  TYPE_3__ ColorMap ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  ColorAdjustTypeAny ; 
 int /*<<< orphan*/  ColorAdjustTypeCount ; 
 int /*<<< orphan*/  ColorAdjustTypeDefault ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* GdipAlloc (int) ; 
 int /*<<< orphan*/  GdipBitmapGetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipBitmapSetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateImageAttributes (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImageAttributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawImageRectRectI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFree (TYPE_3__*) ; 
 int /*<<< orphan*/  GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipResetImageAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetImageAttributesRemapTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat32bppRGB ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  color_match (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_remaptable(void)
{
    GpStatus stat;
    GpImageAttributes *imageattr;
    GpBitmap *bitmap1, *bitmap2;
    GpGraphics *graphics;
    ARGB color;
    ColorMap *map;

    map = GdipAlloc(sizeof(ColorMap));

    map->oldColor.Argb = 0xff00ff00;
    map->newColor.Argb = 0xffff00ff;

    stat = GdipSetImageAttributesRemapTable(NULL, ColorAdjustTypeDefault, TRUE, 1, map);
    expect(InvalidParameter, stat);

    stat = GdipCreateImageAttributes(&imageattr);
    expect(Ok, stat);

    stat = GdipSetImageAttributesRemapTable(imageattr, ColorAdjustTypeDefault, TRUE, 1, NULL);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesRemapTable(imageattr, ColorAdjustTypeCount, TRUE, 1, map);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesRemapTable(imageattr, ColorAdjustTypeAny, TRUE, 1, map);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesRemapTable(imageattr, ColorAdjustTypeDefault, TRUE, 0, map);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesRemapTable(imageattr, ColorAdjustTypeDefault, FALSE, 0, NULL);
    expect(Ok, stat);

    stat = GdipSetImageAttributesRemapTable(imageattr, ColorAdjustTypeDefault, TRUE, 1, map);
    expect(Ok, stat);

    stat = GdipCreateBitmapFromScan0(1, 1, 0, PixelFormat32bppRGB, NULL, &bitmap1);
    expect(Ok, stat);

    stat = GdipCreateBitmapFromScan0(1, 1, 0, PixelFormat32bppRGB, NULL, &bitmap2);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bitmap1, 0, 0, 0xff00ff00);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap2, &graphics);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage*)bitmap1, 0,0,1,1, 0,0,1,1,
	UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xffff00ff, color, 1), "Expected ffff00ff, got %.8x\n", color);

    stat = GdipResetImageAttributes(imageattr, ColorAdjustTypeDefault);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage*)bitmap1, 0,0,1,1, 0,0,1,1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff00ff00, color, 1), "Expected ff00ff00, got %.8x\n", color);

    GdipDeleteGraphics(graphics);
    GdipDisposeImage((GpImage*)bitmap1);
    GdipDisposeImage((GpImage*)bitmap2);
    GdipDisposeImageAttributes(imageattr);
    GdipFree(map);
}