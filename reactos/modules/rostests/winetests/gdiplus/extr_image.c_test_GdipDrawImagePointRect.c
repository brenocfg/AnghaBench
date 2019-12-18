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
typedef  int /*<<< orphan*/  white_2x2 ;
typedef  int /*<<< orphan*/  black_2x2 ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GdipBitmapSetResolution (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawImagePointRectI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipSetInterpolationMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InterpolationModeNearestNeighbor ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void test_GdipDrawImagePointRect(void)
{
    BYTE black_1x1[4] = { 0,0,0,0 };
    BYTE white_2x2[16] = { 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                           0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
    BYTE black_2x2[16] = { 0,0,0,0,0,0,0xff,0xff,
                           0,0,0,0,0,0,0xff,0xff };
    GpStatus status;
    union
    {
        GpBitmap *bitmap;
        GpImage *image;
    } u1, u2;
    GpGraphics *graphics;
    int match;

    status = GdipCreateBitmapFromScan0(1, 1, 4, PixelFormat24bppRGB, black_1x1, &u1.bitmap);
    expect(Ok, status);
    status = GdipBitmapSetResolution(u1.bitmap, 100.0, 100.0);
    expect(Ok, status);

    status = GdipCreateBitmapFromScan0(2, 2, 8, PixelFormat24bppRGB, white_2x2, &u2.bitmap);
    expect(Ok, status);
    status = GdipBitmapSetResolution(u2.bitmap, 300.0, 300.0);
    expect(Ok, status);
    status = GdipGetImageGraphicsContext(u2.image, &graphics);
    expect(Ok, status);
    status = GdipSetInterpolationMode(graphics, InterpolationModeNearestNeighbor);
    expect(Ok, status);

    status = GdipDrawImagePointRectI(graphics, u1.image, 0, 0, 0, 0, 1, 1, UnitPixel);
    expect(Ok, status);

    match = memcmp(white_2x2, black_2x2, sizeof(black_2x2)) == 0;
    ok(match, "data should match\n");
    if (!match)
    {
        UINT i, size = sizeof(white_2x2);
        BYTE *bits = white_2x2;
        for (i = 0; i < size; i++)
            trace(" %02x", bits[i]);
        trace("\n");
    }

    status = GdipDeleteGraphics(graphics);
    expect(Ok, status);
    status = GdipDisposeImage(u1.image);
    expect(Ok, status);
    status = GdipDisposeImage(u2.image);
    expect(Ok, status);
}