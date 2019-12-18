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
typedef  double REAL ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (double const,double const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetImageDimension (int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double const,double) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_GetImageDimension(void)
{
    GpBitmap *bm;
    GpStatus stat;
    const REAL WIDTH = 10.0, HEIGHT = 20.0;
    REAL w,h;

    bm = (GpBitmap*)0xdeadbeef;
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB,NULL, &bm);
    expect(Ok,stat);
    ok((GpBitmap*)0xdeadbeef != bm, "Expected bitmap to not be 0xdeadbeef\n");
    ok(NULL != bm, "Expected bitmap to not be NULL\n");

    stat = GdipGetImageDimension(NULL,&w,&h);
    expect(InvalidParameter, stat);

    stat = GdipGetImageDimension((GpImage*)bm,NULL,&h);
    expect(InvalidParameter, stat);

    stat = GdipGetImageDimension((GpImage*)bm,&w,NULL);
    expect(InvalidParameter, stat);

    w = -1;
    h = -1;
    stat = GdipGetImageDimension((GpImage*)bm,&w,&h);
    expect(Ok, stat);
    expectf(WIDTH,  w);
    expectf(HEIGHT, h);
    GdipDisposeImage((GpImage*)bm);
}