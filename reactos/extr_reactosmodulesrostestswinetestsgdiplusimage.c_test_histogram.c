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
typedef  size_t UINT ;
typedef  int HistogramFormat ;
typedef  size_t GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  GdipBitmapSetPixel (int /*<<< orphan*/ *,size_t,int,int) ; 
 size_t GdipCreateBitmapFromScan0 (size_t const,size_t const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int HistogramFormatA ; 
 int HistogramFormatARGB ; 
 int HistogramFormatB ; 
 int HistogramFormatG ; 
 int HistogramFormatGray ; 
 int HistogramFormatPARGB ; 
 int HistogramFormatR ; 
 int HistogramFormatRGB ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  expect (int,size_t) ; 
 int /*<<< orphan*/  ok (int,char*,size_t) ; 
 size_t pGdipBitmapGetHistogram (int /*<<< orphan*/ *,int,int,size_t*,size_t*,size_t*,size_t*) ; 
 size_t pGdipBitmapGetHistogramSize (int,size_t*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_histogram(void)
{
    UINT ch0[256], ch1[256], ch2[256], ch3[256];
    HistogramFormat test_formats[] =
    {
        HistogramFormatARGB,
        HistogramFormatPARGB,
        HistogramFormatRGB,
        HistogramFormatGray,
        HistogramFormatB,
        HistogramFormatG,
        HistogramFormatR,
        HistogramFormatA,
    };
    const UINT WIDTH = 8, HEIGHT = 16;
    UINT num, i, x;
    GpStatus stat;
    GpBitmap *bm;

    if (!pGdipBitmapGetHistogramSize)
    {
        win_skip("GdipBitmapGetHistogramSize is not supported\n");
        return;
    }

    stat = pGdipBitmapGetHistogramSize(HistogramFormatARGB, NULL);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogramSize(0xff, NULL);
    expect(InvalidParameter, stat);

    num = 123;
    stat = pGdipBitmapGetHistogramSize(10, &num);
    expect(Ok, stat);
    expect(256, num);

    for (i = 0; i < ARRAY_SIZE(test_formats); i++)
    {
        num = 0;
        stat = pGdipBitmapGetHistogramSize(test_formats[i], &num);
        expect(Ok, stat);
        expect(256, num);
    }

    bm = NULL;
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);

    /* Three solid rgb rows, next three rows are rgb shades. */
    for (x = 0; x < WIDTH; x++)
    {
        GdipBitmapSetPixel(bm, x, 0, 0xffff0000);
        GdipBitmapSetPixel(bm, x, 1, 0xff00ff00);
        GdipBitmapSetPixel(bm, x, 2, 0xff0000ff);

        GdipBitmapSetPixel(bm, x, 3, 0xff010000);
        GdipBitmapSetPixel(bm, x, 4, 0xff003f00);
        GdipBitmapSetPixel(bm, x, 5, 0xff000020);
    }

    stat = pGdipBitmapGetHistogram(NULL, HistogramFormatRGB, 256, ch0, ch1, ch2, ch3);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, 123, 256, ch0, ch1, ch2, ch3);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, 123, 256, ch0, ch1, ch2, NULL);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, 123, 256, ch0, ch1, NULL, NULL);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, 123, 256, ch0, NULL, NULL, NULL);
    expect(InvalidParameter, stat);

    /* Requested format matches bitmap format */
    stat = pGdipBitmapGetHistogram(bm, HistogramFormatRGB, 256, ch0, ch1, ch2, ch3);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, HistogramFormatRGB, 100, ch0, ch1, ch2, NULL);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, HistogramFormatRGB, 257, ch0, ch1, ch2, NULL);
    expect(InvalidParameter, stat);

    /* Channel 3 is not used, must be NULL */
    stat = pGdipBitmapGetHistogram(bm, HistogramFormatRGB, 256, ch0, ch1, ch2, NULL);
    expect(Ok, stat);

    ok(ch0[0xff] == WIDTH, "Got red (0xff) %u\n", ch0[0xff]);
    ok(ch1[0xff] == WIDTH, "Got green (0xff) %u\n", ch1[0xff]);
    ok(ch2[0xff] == WIDTH, "Got blue (0xff) %u\n", ch1[0xff]);
    ok(ch0[0x01] == WIDTH, "Got red (0x01) %u\n", ch0[0x01]);
    ok(ch1[0x3f] == WIDTH, "Got green (0x3f) %u\n", ch1[0x3f]);
    ok(ch2[0x20] == WIDTH, "Got blue (0x20) %u\n", ch1[0x20]);

    /* ARGB histogram from RGB data. */
    stat = pGdipBitmapGetHistogram(bm, HistogramFormatARGB, 256, ch0, ch1, ch2, NULL);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, HistogramFormatARGB, 256, ch0, ch1, ch2, ch3);
    expect(Ok, stat);

    ok(ch1[0xff] == WIDTH, "Got red (0xff) %u\n", ch1[0xff]);
    ok(ch2[0xff] == WIDTH, "Got green (0xff) %u\n", ch2[0xff]);
    ok(ch3[0xff] == WIDTH, "Got blue (0xff) %u\n", ch3[0xff]);
    ok(ch1[0x01] == WIDTH, "Got red (0x01) %u\n", ch1[0x01]);
    ok(ch2[0x3f] == WIDTH, "Got green (0x3f) %u\n", ch2[0x3f]);
    ok(ch3[0x20] == WIDTH, "Got blue (0x20) %u\n", ch3[0x20]);

    ok(ch0[0xff] == WIDTH * HEIGHT, "Got alpha (0xff) %u\n", ch0[0xff]);

    /* Request grayscale histogram from RGB bitmap. */
    stat = pGdipBitmapGetHistogram(bm, HistogramFormatGray, 256, ch0, ch1, ch2, ch3);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, HistogramFormatGray, 256, ch0, ch1, ch2, NULL);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, HistogramFormatGray, 256, ch0, ch1, NULL, NULL);
    expect(InvalidParameter, stat);

    stat = pGdipBitmapGetHistogram(bm, HistogramFormatGray, 256, ch0, NULL, NULL, NULL);
    expect(Ok, stat);

    GdipDisposeImage((GpImage*)bm);
}