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
typedef  int REAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  GdipBitmapSetResolution (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetDpiX (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GdipGetDpiY (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipGetImageHorizontalResolution (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GdipGetImageVerticalResolution (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (int,int) ; 

__attribute__((used)) static void test_resolution(void)
{
    GpStatus stat;
    GpBitmap *bitmap;
    GpGraphics *graphics;
    REAL res=-1.0;
    HDC screendc;
    int screenxres, screenyres;

    /* create Bitmap */
    stat = GdipCreateBitmapFromScan0(1, 1, 32, PixelFormat24bppRGB, NULL, &bitmap);
    expect(Ok, stat);

    /* test invalid values */
    stat = GdipGetImageHorizontalResolution(NULL, &res);
    expect(InvalidParameter, stat);

    stat = GdipGetImageHorizontalResolution((GpImage*)bitmap, NULL);
    expect(InvalidParameter, stat);

    stat = GdipGetImageVerticalResolution(NULL, &res);
    expect(InvalidParameter, stat);

    stat = GdipGetImageVerticalResolution((GpImage*)bitmap, NULL);
    expect(InvalidParameter, stat);

    stat = GdipBitmapSetResolution(NULL, 96.0, 96.0);
    expect(InvalidParameter, stat);

    stat = GdipBitmapSetResolution(bitmap, 0.0, 0.0);
    expect(InvalidParameter, stat);

    /* defaults to screen resolution */
    screendc = GetDC(0);

    screenxres = GetDeviceCaps(screendc, LOGPIXELSX);
    screenyres = GetDeviceCaps(screendc, LOGPIXELSY);

    ReleaseDC(0, screendc);

    stat = GdipGetImageHorizontalResolution((GpImage*)bitmap, &res);
    expect(Ok, stat);
    expectf((REAL)screenxres, res);

    stat = GdipGetImageVerticalResolution((GpImage*)bitmap, &res);
    expect(Ok, stat);
    expectf((REAL)screenyres, res);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap, &graphics);
    expect(Ok, stat);
    stat = GdipGetDpiX(graphics, &res);
    expect(Ok, stat);
    expectf((REAL)screenxres, res);
    stat = GdipGetDpiY(graphics, &res);
    expect(Ok, stat);
    expectf((REAL)screenyres, res);

    /* test changing the resolution */
    stat = GdipBitmapSetResolution(bitmap, screenxres*2.0, screenyres*3.0);
    expect(Ok, stat);

    stat = GdipGetImageHorizontalResolution((GpImage*)bitmap, &res);
    expect(Ok, stat);
    expectf(screenxres*2.0, res);

    stat = GdipGetImageVerticalResolution((GpImage*)bitmap, &res);
    expect(Ok, stat);
    expectf(screenyres*3.0, res);

    stat = GdipGetDpiX(graphics, &res);
    expect(Ok, stat);
    expectf((REAL)screenxres, res);
    stat = GdipGetDpiY(graphics, &res);
    expect(Ok, stat);
    expectf((REAL)screenyres, res);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap, &graphics);
    expect(Ok, stat);
    stat = GdipGetDpiX(graphics, &res);
    expect(Ok, stat);
    expectf(screenxres*2.0, res);
    stat = GdipGetDpiY(graphics, &res);
    expect(Ok, stat);
    expectf(screenyres*3.0, res);
    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)bitmap);
    expect(Ok, stat);
}