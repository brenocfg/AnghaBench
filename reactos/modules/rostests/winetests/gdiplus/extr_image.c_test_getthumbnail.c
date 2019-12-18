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
typedef  int UINT ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;

/* Variables and functions */
 int GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipGetImageHeight (int /*<<< orphan*/ *,int*) ; 
 int GdipGetImageThumbnail (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetImageWidth (int /*<<< orphan*/ *,int*) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat32bppRGB ; 
 int /*<<< orphan*/  expect (int,int) ; 

__attribute__((used)) static void test_getthumbnail(void)
{
    GpStatus stat;
    GpImage *bitmap1, *bitmap2;
    UINT width, height;

    stat = GdipGetImageThumbnail(NULL, 0, 0, &bitmap2, NULL, NULL);
    expect(InvalidParameter, stat);

    stat = GdipCreateBitmapFromScan0(128, 128, 0, PixelFormat32bppRGB, NULL, (GpBitmap**)&bitmap1);
    expect(Ok, stat);

    stat = GdipGetImageThumbnail(bitmap1, 0, 0, NULL, NULL, NULL);
    expect(InvalidParameter, stat);

    stat = GdipGetImageThumbnail(bitmap1, 0, 0, &bitmap2, NULL, NULL);
    expect(Ok, stat);

    if (stat == Ok)
    {
        stat = GdipGetImageWidth(bitmap2, &width);
        expect(Ok, stat);
        expect(120, width);

        stat = GdipGetImageHeight(bitmap2, &height);
        expect(Ok, stat);
        expect(120, height);

        GdipDisposeImage(bitmap2);
    }

    GdipDisposeImage(bitmap1);


    stat = GdipCreateBitmapFromScan0(64, 128, 0, PixelFormat32bppRGB, NULL, (GpBitmap**)&bitmap1);
    expect(Ok, stat);

    stat = GdipGetImageThumbnail(bitmap1, 32, 32, &bitmap2, NULL, NULL);
    expect(Ok, stat);

    if (stat == Ok)
    {
        stat = GdipGetImageWidth(bitmap2, &width);
        expect(Ok, stat);
        expect(32, width);

        stat = GdipGetImageHeight(bitmap2, &height);
        expect(Ok, stat);
        expect(32, height);

        GdipDisposeImage(bitmap2);
    }

    stat = GdipGetImageThumbnail(bitmap1, 0, 0, &bitmap2, NULL, NULL);
    expect(Ok, stat);

    if (stat == Ok)
    {
        stat = GdipGetImageWidth(bitmap2, &width);
        expect(Ok, stat);
        expect(120, width);

        stat = GdipGetImageHeight(bitmap2, &height);
        expect(Ok, stat);
        expect(120, height);

        GdipDisposeImage(bitmap2);
    }

    GdipDisposeImage(bitmap1);
}