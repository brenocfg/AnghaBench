#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {double member_0; double member_1; double member_2; double member_3; double member_4; } ;
struct TYPE_14__ {double member_0; double member_1; double member_2; double member_3; double member_4; } ;
struct TYPE_13__ {double member_0; double member_1; double member_2; double member_3; double member_4; } ;
struct TYPE_12__ {double member_0; double member_1; double member_2; double member_3; double member_4; } ;
struct TYPE_11__ {double member_0; double member_1; double member_2; double member_3; double member_4; } ;
struct TYPE_10__ {TYPE_6__ member_4; TYPE_5__ member_3; TYPE_4__ member_2; TYPE_3__ member_1; TYPE_2__ member_0; } ;
struct TYPE_16__ {TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpImageAttributes ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  TYPE_7__ ColorMatrix ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  ColorAdjustTypeAny ; 
 int /*<<< orphan*/  ColorAdjustTypeBitmap ; 
 int /*<<< orphan*/  ColorAdjustTypeCount ; 
 int /*<<< orphan*/  ColorAdjustTypeDefault ; 
 int ColorMatrixFlagsAltGray ; 
 int ColorMatrixFlagsDefault ; 
 int ColorMatrixFlagsSkipGrays ; 
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
 int /*<<< orphan*/  GdipSetImageAttributesColorMatrix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  GdipSetImageAttributesNoOp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  color_match (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_colormatrix(void)
{
    GpStatus stat;
    ColorMatrix colormatrix, graymatrix;
    GpImageAttributes *imageattr;
    const ColorMatrix identity = {{
        {1.0,0.0,0.0,0.0,0.0},
        {0.0,1.0,0.0,0.0,0.0},
        {0.0,0.0,1.0,0.0,0.0},
        {0.0,0.0,0.0,1.0,0.0},
        {0.0,0.0,0.0,0.0,1.0}}};
    const ColorMatrix double_red = {{
        {2.0,0.0,0.0,0.0,0.0},
        {0.0,1.0,0.0,0.0,0.0},
        {0.0,0.0,1.0,0.0,0.0},
        {0.0,0.0,0.0,1.0,0.0},
        {0.0,0.0,0.0,0.0,1.0}}};
    const ColorMatrix asymmetric = {{
        {0.0,1.0,0.0,0.0,0.0},
        {0.0,0.0,1.0,0.0,0.0},
        {0.0,0.0,0.0,1.0,0.0},
        {1.0,0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0,1.0}}};
    GpBitmap *bitmap1, *bitmap2;
    GpGraphics *graphics;
    ARGB color;

    colormatrix = identity;
    graymatrix = identity;

    stat = GdipSetImageAttributesColorMatrix(NULL, ColorAdjustTypeDefault,
        TRUE, &colormatrix, &graymatrix, ColorMatrixFlagsDefault);
    expect(InvalidParameter, stat);

    stat = GdipCreateImageAttributes(&imageattr);
    expect(Ok, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, &colormatrix, NULL, ColorMatrixFlagsDefault);
    expect(Ok, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, NULL, NULL, ColorMatrixFlagsDefault);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, &colormatrix, &graymatrix, ColorMatrixFlagsDefault);
    expect(Ok, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, &colormatrix, NULL, ColorMatrixFlagsSkipGrays);
    expect(Ok, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, &colormatrix, NULL, ColorMatrixFlagsAltGray);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, &colormatrix, &graymatrix, ColorMatrixFlagsAltGray);
    expect(Ok, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, &colormatrix, &graymatrix, 3);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeCount,
        TRUE, &colormatrix, &graymatrix, ColorMatrixFlagsDefault);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeAny,
        TRUE, &colormatrix, &graymatrix, ColorMatrixFlagsDefault);
    expect(InvalidParameter, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        FALSE, NULL, NULL, ColorMatrixFlagsDefault);
    expect(Ok, stat);

    /* Drawing a bitmap transforms the colors */
    colormatrix = double_red;
    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, &colormatrix, NULL, ColorMatrixFlagsDefault);
    expect(Ok, stat);

    stat = GdipCreateBitmapFromScan0(1, 1, 0, PixelFormat32bppARGB, NULL, &bitmap1);
    expect(Ok, stat);

    stat = GdipCreateBitmapFromScan0(1, 1, 0, PixelFormat32bppARGB, NULL, &bitmap2);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bitmap1, 0, 0, 0xff40ccee);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap2, &graphics);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage*)bitmap1, 0,0,1,1, 0,0,1,1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    expect(0xff80ccee, color);

    colormatrix = asymmetric;
    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, &colormatrix, NULL, ColorMatrixFlagsDefault);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bitmap2, 0, 0, 0);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage*)bitmap1, 0,0,1,1, 0,0,1,1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xeeff40cc, color, 3), "expected 0xeeff40cc, got 0x%08x\n", color);

    /* Toggle NoOp */
    stat = GdipSetImageAttributesNoOp(imageattr, ColorAdjustTypeDefault, FALSE);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xfefe40cc, color, 3), "expected 0xfefe40cc, got 0x%08x\n", color);

    stat = GdipSetImageAttributesNoOp(imageattr, ColorAdjustTypeDefault, TRUE);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff40ccee, color, 3), "expected 0xff40ccee, got 0x%08x\n", color);

    stat = GdipResetImageAttributes(imageattr, ColorAdjustTypeDefault);
    expect(Ok, stat);

    stat = GdipSetImageAttributesNoOp(imageattr, ColorAdjustTypeDefault, FALSE);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff40ccee, color, 3), "expected 0xff40ccee, got 0x%08x\n", color);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff40ccee, color, 1), "Expected ff40ccee, got %.8x\n", color);

    /* Disable adjustment, toggle NoOp */
    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        FALSE, &colormatrix, NULL, ColorMatrixFlagsDefault);
    expect(Ok, stat);

    stat = GdipSetImageAttributesNoOp(imageattr, ColorAdjustTypeDefault, FALSE);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff40ccee, color, 3), "expected 0xff40ccee, got 0x%08x\n", color);

    stat = GdipSetImageAttributesNoOp(imageattr, ColorAdjustTypeDefault, TRUE);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff40ccee, color, 3), "expected 0xff40ccee, got 0x%08x\n", color);

    /* Reset with NoOp on, enable adjustment. */
    stat = GdipResetImageAttributes(imageattr, ColorAdjustTypeDefault);
    expect(Ok, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeDefault,
        TRUE, &colormatrix, NULL, ColorMatrixFlagsDefault);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xfff24ace, color, 3), "expected 0xfff24ace, got 0x%08x\n", color);

    /* Now inhibit specific category. */
    stat = GdipResetImageAttributes(imageattr, ColorAdjustTypeDefault);
    expect(Ok, stat);

    stat = GdipSetImageAttributesColorMatrix(imageattr, ColorAdjustTypeBitmap,
        TRUE, &colormatrix, NULL, ColorMatrixFlagsDefault);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xfffe41cc, color, 3), "expected 0xfffe41cc, got 0x%08x\n", color);

    stat = GdipSetImageAttributesNoOp(imageattr, ColorAdjustTypeBitmap, TRUE);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff40ccee, color, 3), "expected 0xff40ccee, got 0x%08x\n", color);

    stat = GdipSetImageAttributesNoOp(imageattr, ColorAdjustTypeBitmap, FALSE);
    expect(Ok, stat);

    stat = GdipSetImageAttributesNoOp(imageattr, ColorAdjustTypeDefault, TRUE);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xfff24ace, color, 3), "expected 0xfff24ace, got 0x%08x\n", color);

    stat = GdipResetImageAttributes(imageattr, ColorAdjustTypeBitmap);
    expect(Ok, stat);

    stat = GdipDrawImageRectRectI(graphics, (GpImage *)bitmap1, 0, 0, 1, 1, 0, 0, 1, 1,
        UnitPixel, imageattr, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap2, 0, 0, &color);
    expect(Ok, stat);
    ok(color_match(0xff40ccee, color, 3), "expected 0xff40ccee, got 0x%08x\n", color);

    GdipDeleteGraphics(graphics);
    GdipDisposeImage((GpImage*)bitmap1);
    GdipDisposeImage((GpImage*)bitmap2);
    GdipDisposeImageAttributes(imageattr);
}