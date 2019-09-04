#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  double REAL ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  TYPE_1__ GUID ;
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FrameDimensionPage ; 
 int GdipBitmapGetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GdipBitmapSetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int GdipCreateBitmapFromScan0 (double const,double const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipImageGetFrameCount (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 int GdipImageGetFrameDimensionsCount (int /*<<< orphan*/ *,int*) ; 
 int GdipImageGetFrameDimensionsList (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int GdipImageSelectActiveFrame (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expect_guid (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_GdipImageGetFrameDimensionsCount(void)
{
    GpBitmap *bm;
    GpStatus stat;
    const REAL WIDTH = 10.0, HEIGHT = 20.0;
    UINT w;
    GUID dimension = {0};
    UINT count;
    ARGB color;

    bm = (GpBitmap*)0xdeadbeef;
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB,NULL, &bm);
    expect(Ok,stat);
    ok((GpBitmap*)0xdeadbeef != bm, "Expected bitmap to not be 0xdeadbeef\n");
    ok(NULL != bm, "Expected bitmap to not be NULL\n");

    stat = GdipImageGetFrameDimensionsCount(NULL,&w);
    expect(InvalidParameter, stat);

    stat = GdipImageGetFrameDimensionsCount((GpImage*)bm,NULL);
    expect(InvalidParameter, stat);

    w = -1;
    stat = GdipImageGetFrameDimensionsCount((GpImage*)bm,&w);
    expect(Ok, stat);
    expect(1, w);

    stat = GdipImageGetFrameDimensionsList((GpImage*)bm, &dimension, 1);
    expect(Ok, stat);
    expect_guid(&FrameDimensionPage, &dimension, __LINE__, FALSE);

    stat = GdipImageGetFrameDimensionsList((GpImage*)bm, &dimension, 2);
    expect(InvalidParameter, stat);

    stat = GdipImageGetFrameDimensionsList((GpImage*)bm, &dimension, 0);
    expect(InvalidParameter, stat);

    stat = GdipImageGetFrameCount(NULL, &dimension, &count);
    expect(InvalidParameter, stat);

    /* WinXP crashes on this test */
    if(0)
    {
        stat = GdipImageGetFrameCount((GpImage*)bm, &dimension, NULL);
        expect(InvalidParameter, stat);
    }

    stat = GdipImageGetFrameCount((GpImage*)bm, NULL, &count);
    expect(Ok, stat);

    count = 12345;
    stat = GdipImageGetFrameCount((GpImage*)bm, &dimension, &count);
    expect(Ok, stat);
    expect(1, count);

    GdipBitmapSetPixel(bm, 0, 0, 0xffffffff);

    stat = GdipImageSelectActiveFrame((GpImage*)bm, &dimension, 0);
    expect(Ok, stat);

    /* SelectActiveFrame has no effect on image data of memory bitmaps */
    color = 0xdeadbeef;
    stat = GdipBitmapGetPixel(bm, 0, 0, &color);
    expect(Ok, stat);
    expect(0xffffffff, color);

    GdipDisposeImage((GpImage*)bm);
}