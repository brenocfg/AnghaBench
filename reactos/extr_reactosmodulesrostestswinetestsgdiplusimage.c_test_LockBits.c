#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int Stride; int Width; int Height; scalar_t__ Scan0; } ;
struct TYPE_6__ {int X; int Y; int Width; int Height; } ;
typedef  int INT ;
typedef  int GpStatus ;
typedef  TYPE_1__ GpRect ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  TYPE_2__ BitmapData ;
typedef  int BYTE ;
typedef  int ARGB ;

/* Variables and functions */
 int GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int*) ; 
 int GdipBitmapLockBits (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int GdipBitmapSetPixel (int /*<<< orphan*/ *,int,int,int) ; 
 int GdipBitmapUnlockBits (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int GdipCreateBitmapFromScan0 (int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int ImageLockModeRead ; 
 int ImageLockModeWrite ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat24bppRGB ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int WrongState ; 
 int /*<<< orphan*/  expect (int,int const) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_LockBits(void)
{
    GpStatus stat;
    GpBitmap *bm;
    GpRect rect;
    BitmapData bd;
    const INT WIDTH = 10, HEIGHT = 20;
    ARGB color;
    int y;

    bm = NULL;
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);

    rect.X = 2;
    rect.Y = 3;
    rect.Width = 4;
    rect.Height = 5;

    stat = GdipBitmapSetPixel(bm, 2, 3, 0xffc30000);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bm, 2, 8, 0xff480000);
    expect(Ok, stat);

    /* read-only */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeRead, PixelFormat24bppRGB, &bd);
    expect(Ok, stat);

    if (stat == Ok) {
        expect(0xc3, ((BYTE*)bd.Scan0)[2]);
        expect(0x48, ((BYTE*)bd.Scan0)[2 + bd.Stride * 5]);

        ((char*)bd.Scan0)[2] = 0xff;

        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipBitmapGetPixel(bm, 2, 3, &color);
    expect(Ok, stat);
    expect(0xffff0000, color);

    stat = GdipBitmapSetPixel(bm, 2, 3, 0xffc30000);
    expect(Ok, stat);

    /* read-only, with NULL rect -> whole bitmap lock */
    stat = GdipBitmapLockBits(bm, NULL, ImageLockModeRead, PixelFormat24bppRGB, &bd);
    expect(Ok, stat);
    expect(bd.Width,  WIDTH);
    expect(bd.Height, HEIGHT);

    if (stat == Ok) {
        ((char*)bd.Scan0)[2 + 2*3 + 3*bd.Stride] = 0xff;

        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipBitmapGetPixel(bm, 2, 3, &color);
    expect(Ok, stat);
    expect(0xffff0000, color);

    /* read-only, consecutive */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeRead, PixelFormat24bppRGB, &bd);
    expect(Ok, stat);

    if (stat == Ok) {
        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipDisposeImage((GpImage*)bm);
    expect(Ok, stat);
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);

    /* read x2 */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeRead, PixelFormat24bppRGB, &bd);
    expect(Ok, stat);
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeRead, PixelFormat24bppRGB, &bd);
    expect(WrongState, stat);

    stat = GdipBitmapUnlockBits(bm, &bd);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)bm);
    expect(Ok, stat);
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bm, 2, 3, 0xffff0000);
    expect(Ok, stat);

    stat = GdipBitmapSetPixel(bm, 2, 8, 0xffc30000);
    expect(Ok, stat);

    /* write, no conversion */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeWrite, PixelFormat24bppRGB, &bd);
    expect(Ok, stat);

    if (stat == Ok) {
        /* all bits are readable, inside the rect or not */
        expect(0xff, ((BYTE*)bd.Scan0)[2]);
        expect(0xc3, ((BYTE*)bd.Scan0)[2 + bd.Stride * 5]);

        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    /* read, conversion */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeRead, PixelFormat32bppARGB, &bd);
    expect(Ok, stat);

    if (stat == Ok) {
        expect(0xff, ((BYTE*)bd.Scan0)[2]);
        if (0)
            /* Areas outside the rectangle appear to be uninitialized */
            ok(0xc3 != ((BYTE*)bd.Scan0)[2 + bd.Stride * 5], "original image bits are readable\n");

        ((BYTE*)bd.Scan0)[2] = 0xc3;

        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    /* writes do not work in read mode if there was a conversion */
    stat = GdipBitmapGetPixel(bm, 2, 3, &color);
    expect(Ok, stat);
    expect(0xffff0000, color);

    /* read/write, conversion */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeRead|ImageLockModeWrite, PixelFormat32bppARGB, &bd);
    expect(Ok, stat);

    if (stat == Ok) {
        expect(0xff, ((BYTE*)bd.Scan0)[2]);
        ((BYTE*)bd.Scan0)[1] = 0x88;
        if (0)
            /* Areas outside the rectangle appear to be uninitialized */
            ok(0xc3 != ((BYTE*)bd.Scan0)[2 + bd.Stride * 5], "original image bits are readable\n");

        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipBitmapGetPixel(bm, 2, 3, &color);
    expect(Ok, stat);
    expect(0xffff8800, color);

    /* write, conversion */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeWrite, PixelFormat32bppARGB, &bd);
    expect(Ok, stat);

    if (stat == Ok) {
        if (0)
        {
            /* This is completely uninitialized. */
            ok(0xff != ((BYTE*)bd.Scan0)[2], "original image bits are readable\n");
            ok(0xc3 != ((BYTE*)bd.Scan0)[2 + bd.Stride * 5], "original image bits are readable\n");
        }

        /* Initialize the buffer so the unlock doesn't access undefined memory */
        for (y=0; y<5; y++)
            memset(((BYTE*)bd.Scan0) + bd.Stride * y, 0, 12);

        ((BYTE*)bd.Scan0)[0] = 0x12;
        ((BYTE*)bd.Scan0)[1] = 0x34;
        ((BYTE*)bd.Scan0)[2] = 0x56;

        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipBitmapGetPixel(bm, 2, 3, &color);
    expect(Ok, stat);
    expect(0xff563412, color);

    stat = GdipBitmapGetPixel(bm, 2, 8, &color);
    expect(Ok, stat);
    expect(0xffc30000, color);

    stat = GdipDisposeImage((GpImage*)bm);
    expect(Ok, stat);
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);

    /* write, no modification */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeWrite, PixelFormat24bppRGB, &bd);
    expect(Ok, stat);

    if (stat == Ok) {
        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    /* write, consecutive */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeWrite, PixelFormat24bppRGB, &bd);
    expect(Ok, stat);

    if (stat == Ok) {
        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipDisposeImage((GpImage*)bm);
    expect(Ok, stat);
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);

    /* write, modify */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeWrite, PixelFormat24bppRGB, &bd);
    expect(Ok, stat);

    if (stat == Ok) {
        if (bd.Scan0)
            ((char*)bd.Scan0)[2] = 0xff;

        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipBitmapGetPixel(bm, 2, 3, &color);
    expect(Ok, stat);
    expect(0xffff0000, color);

    stat = GdipDisposeImage((GpImage*)bm);
    expect(Ok, stat);

    /* dispose locked */
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat24bppRGB, NULL, &bm);
    expect(Ok, stat);
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeRead, PixelFormat24bppRGB, &bd);
    expect(Ok, stat);
    stat = GdipDisposeImage((GpImage*)bm);
    expect(Ok, stat);
}