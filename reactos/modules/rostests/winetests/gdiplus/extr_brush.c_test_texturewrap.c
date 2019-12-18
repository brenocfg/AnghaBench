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
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpWrapMode ;
typedef  int /*<<< orphan*/  GpTexture ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  GpBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateBitmapFromGraphics (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateTexture (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetTextureWrapMode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetTextureWrapMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WrapModeClamp ; 
 int /*<<< orphan*/  WrapModeTile ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_texturewrap(void)
{
    GpStatus status;
    GpTexture *texture;
    GpGraphics *graphics = NULL;
    GpBitmap *bitmap;
    HDC hdc = GetDC(0);
    GpWrapMode wrap;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    status = GdipCreateBitmapFromGraphics(1, 1, graphics, &bitmap);
    expect(Ok, status);

    status = GdipCreateTexture((GpImage*)bitmap, WrapModeTile, &texture);
    expect(Ok, status);

    /* NULL */
    status = GdipGetTextureWrapMode(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipGetTextureWrapMode(texture, NULL);
    expect(InvalidParameter, status);
    status = GdipGetTextureWrapMode(NULL, &wrap);
    expect(InvalidParameter, status);

    /* get */
    wrap = WrapModeClamp;
    status = GdipGetTextureWrapMode(texture, &wrap);
    expect(Ok, status);
    expect(WrapModeTile, wrap);
    /* set, then get */
    wrap = WrapModeClamp;
    status = GdipSetTextureWrapMode(texture, wrap);
    expect(Ok, status);
    wrap = WrapModeTile;
    status = GdipGetTextureWrapMode(texture, &wrap);
    expect(Ok, status);
    expect(WrapModeClamp, wrap);

    status = GdipDeleteBrush((GpBrush*)texture);
    expect(Ok, status);
    status = GdipDisposeImage((GpImage*)bitmap);
    expect(Ok, status);
    status = GdipDeleteGraphics(graphics);
    expect(Ok, status);
    ReleaseDC(0, hdc);
}