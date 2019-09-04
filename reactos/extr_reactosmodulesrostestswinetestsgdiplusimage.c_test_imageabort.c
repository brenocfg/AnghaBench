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
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pGdipImageSetAbort (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_imageabort(void)
{
    GpStatus stat;
    GpBitmap *bm;

    if (!pGdipImageSetAbort)
    {
        win_skip("GdipImageSetAbort() is not supported.\n");
        return;
    }

    bm = NULL;
    stat = GdipCreateBitmapFromScan0(8, 8, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);

    stat = pGdipImageSetAbort(NULL, NULL);
    expect(InvalidParameter, stat);

    stat = pGdipImageSetAbort((GpImage*)bm, NULL);
    expect(Ok, stat);

    GdipDisposeImage((GpImage*)bm);
}