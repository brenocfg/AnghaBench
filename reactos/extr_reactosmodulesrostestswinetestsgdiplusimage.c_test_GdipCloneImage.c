#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
typedef  int /*<<< orphan*/  REAL ;
typedef  int INT ;
typedef  int /*<<< orphan*/  GpUnit ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdipCloneImage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageBounds (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ImageFormatMemoryBMP ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_rawformat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_GdipCloneImage(void)
{
    GpStatus stat;
    GpRectF rectF;
    GpUnit unit;
    GpBitmap *bm;
    GpImage *image_src, *image_dest = NULL;
    const INT WIDTH = 10, HEIGHT = 20;

    /* Create an image, clone it, delete the original, make sure the copy works */
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);
    expect_rawformat(&ImageFormatMemoryBMP, (GpImage*)bm, __LINE__, FALSE);

    image_src = ((GpImage*)bm);
    stat = GdipCloneImage(image_src, &image_dest);
    expect(Ok, stat);
    expect_rawformat(&ImageFormatMemoryBMP, image_dest, __LINE__, FALSE);

    stat = GdipDisposeImage((GpImage*)bm);
    expect(Ok, stat);
    stat = GdipGetImageBounds(image_dest, &rectF, &unit);
    expect(Ok, stat);

    /* Treat FP values carefully */
    expectf((REAL)WIDTH, rectF.Width);
    expectf((REAL)HEIGHT, rectF.Height);

    stat = GdipDisposeImage(image_dest);
    expect(Ok, stat);
}