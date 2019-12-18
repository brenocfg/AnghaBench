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
typedef  int /*<<< orphan*/  bits ;
struct TYPE_7__ {int Width; int Height; int Stride; int* Scan0; int Reserved; int /*<<< orphan*/  PixelFormat; } ;
struct TYPE_6__ {int X; int Y; int Width; int Height; } ;
typedef  int INT ;
typedef  int GpStatus ;
typedef  TYPE_1__ GpRect ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int DWORD ;
typedef  TYPE_2__ BitmapData ;
typedef  int ARGB ;

/* Variables and functions */
 int GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int*) ; 
 int GdipBitmapLockBits (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int GdipBitmapUnlockBits (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int GdipCreateBitmapFromScan0 (int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int ImageLockModeRead ; 
 int ImageLockModeUserInputBuf ; 
 int ImageLockModeWrite ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void test_LockBits_UserBuf(void)
{
    GpStatus stat;
    GpBitmap *bm;
    GpRect rect;
    BitmapData bd;
    const INT WIDTH = 10, HEIGHT = 20;
    DWORD bits[200];
    ARGB color;

    bm = NULL;
    stat = GdipCreateBitmapFromScan0(WIDTH, HEIGHT, 0, PixelFormat32bppARGB, NULL, &bm);
    expect(Ok, stat);

    memset(bits, 0xaa, sizeof(bits));

    rect.X = 2;
    rect.Y = 3;
    rect.Width = 4;
    rect.Height = 5;

    bd.Width = 4;
    bd.Height = 6;
    bd.Stride = WIDTH * 4;
    bd.PixelFormat = PixelFormat32bppARGB;
    bd.Scan0 = &bits[2+3*WIDTH];
    bd.Reserved = 0xaaaaaaaa;

    /* read-only */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeRead|ImageLockModeUserInputBuf, PixelFormat32bppARGB, &bd);
    expect(Ok, stat);

    expect(0xaaaaaaaa, bits[0]);
    expect(0, bits[2+3*WIDTH]);

    bits[2+3*WIDTH] = 0xdeadbeef;

    if (stat == Ok) {
        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipBitmapGetPixel(bm, 2, 3, &color);
    expect(Ok, stat);
    expect(0, color);

    /* write-only */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeWrite|ImageLockModeUserInputBuf, PixelFormat32bppARGB, &bd);
    expect(Ok, stat);

    expect(0xdeadbeef, bits[2+3*WIDTH]);
    bits[2+3*WIDTH] = 0x12345678;

    if (stat == Ok) {
        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipBitmapGetPixel(bm, 2, 3, &color);
    expect(Ok, stat);
    expect(0x12345678, color);

    bits[2+3*WIDTH] = 0;

    /* read/write */
    stat = GdipBitmapLockBits(bm, &rect, ImageLockModeRead|ImageLockModeWrite|ImageLockModeUserInputBuf, PixelFormat32bppARGB, &bd);
    expect(Ok, stat);

    expect(0x12345678, bits[2+3*WIDTH]);
    bits[2+3*WIDTH] = 0xdeadbeef;

    if (stat == Ok) {
        stat = GdipBitmapUnlockBits(bm, &bd);
        expect(Ok, stat);
    }

    stat = GdipBitmapGetPixel(bm, 2, 3, &color);
    expect(Ok, stat);
    expect(0xdeadbeef, color);

    stat = GdipDisposeImage((GpImage*)bm);
    expect(Ok, stat);
}