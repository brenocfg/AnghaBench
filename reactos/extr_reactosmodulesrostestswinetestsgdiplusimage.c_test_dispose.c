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

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  ObjectBusy ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_dispose(void)
{
    GpStatus stat;
    GpImage *image;
    char invalid_image[256];

    stat = GdipDisposeImage(NULL);
    expect(InvalidParameter, stat);

    stat = GdipCreateBitmapFromScan0(2, 2, 0, PixelFormat32bppARGB, NULL, (GpBitmap**)&image);
    expect(Ok, stat);

    stat = GdipDisposeImage(image);
    expect(Ok, stat);

    stat = GdipDisposeImage(image);
    expect(ObjectBusy, stat);

    memset(invalid_image, 0, 256);
    stat = GdipDisposeImage((GpImage*)invalid_image);
    expect(ObjectBusy, stat);
}