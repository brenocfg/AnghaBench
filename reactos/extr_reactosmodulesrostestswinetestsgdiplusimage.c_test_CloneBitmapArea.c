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
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  BitmapData ;

/* Variables and functions */
 int /*<<< orphan*/  GdipBitmapLockBits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipBitmapUnlockBits (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCloneBitmapAreaI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int ImageLockModeRead ; 
 int ImageLockModeWrite ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  WrongState ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_CloneBitmapArea(void)
{
    GpStatus status;
    GpBitmap *bitmap, *copy;
    BitmapData data, data2;

    status = GdipCreateBitmapFromScan0(1, 1, 0, PixelFormat24bppRGB, NULL, &bitmap);
    expect(Ok, status);

    status = GdipBitmapLockBits(bitmap, NULL, ImageLockModeRead | ImageLockModeWrite, PixelFormat24bppRGB, &data);
    expect(Ok, status);

    status = GdipBitmapLockBits(bitmap, NULL, ImageLockModeRead, PixelFormat24bppRGB, &data2);
    expect(WrongState, status);

    status = GdipCloneBitmapAreaI(0, 0, 1, 1, PixelFormat24bppRGB, bitmap, &copy);
    expect(Ok, status);

    status = GdipBitmapUnlockBits(bitmap, &data);
    expect(Ok, status);

    GdipDisposeImage((GpImage *)copy);
    GdipDisposeImage((GpImage *)bitmap);
}