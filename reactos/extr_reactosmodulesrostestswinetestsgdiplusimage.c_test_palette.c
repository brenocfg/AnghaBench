#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int* Entries; int Count; int Flags; } ;
typedef  int INT ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  TYPE_1__ ColorPalette ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int ARGB ;

/* Variables and functions */
 int GdipBitmapGetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int GdipBitmapSetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int GdipCreateBitmapFromScan0 (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipGetImagePalette (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int GdipGetImagePaletteSize (int /*<<< orphan*/ *,int*) ; 
 int GdipSetImagePalette (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int InvalidParameter ; 
 int Ok ; 
 int PaletteFlagsGrayScale ; 
 int PaletteFlagsHalftone ; 
 int /*<<< orphan*/  PixelFormat1bppIndexed ; 
 int /*<<< orphan*/  PixelFormat32bppRGB ; 
 int /*<<< orphan*/  PixelFormat4bppIndexed ; 
 int /*<<< orphan*/  PixelFormat8bppIndexed ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  check_halftone_palette (TYPE_1__*) ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_palette(void)
{
    GpStatus stat;
    GpBitmap *bitmap;
    INT size;
    BYTE buffer[1040];
    ColorPalette *palette=(ColorPalette*)buffer;
    ARGB *entries = palette->Entries;
    ARGB color=0;

    /* test initial palette from non-indexed bitmap */
    stat = GdipCreateBitmapFromScan0(2, 2, 8, PixelFormat32bppRGB, NULL, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImagePaletteSize((GpImage*)bitmap, &size);
    expect(Ok, stat);
    expect(sizeof(UINT)*2+sizeof(ARGB), size);

    stat = GdipGetImagePalette((GpImage*)bitmap, palette, size);
    expect(Ok, stat);
    expect(0, palette->Count);

    /* test setting palette on not-indexed bitmap */
    palette->Count = 3;

    stat = GdipSetImagePalette((GpImage*)bitmap, palette);
    expect(Ok, stat);

    stat = GdipGetImagePaletteSize((GpImage*)bitmap, &size);
    expect(Ok, stat);
    expect(sizeof(UINT)*2+sizeof(ARGB)*3, size);

    stat = GdipGetImagePalette((GpImage*)bitmap, palette, size);
    expect(Ok, stat);
    expect(3, palette->Count);

    GdipDisposeImage((GpImage*)bitmap);

    /* test initial palette on 1-bit bitmap */
    stat = GdipCreateBitmapFromScan0(2, 2, 4, PixelFormat1bppIndexed, NULL, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImagePaletteSize((GpImage*)bitmap, &size);
    expect(Ok, stat);
    expect(sizeof(UINT)*2+sizeof(ARGB)*2, size);

    stat = GdipGetImagePalette((GpImage*)bitmap, palette, size);
    expect(Ok, stat);
    expect(PaletteFlagsGrayScale, palette->Flags);
    expect(2, palette->Count);

    expect(0xff000000, entries[0]);
    expect(0xffffffff, entries[1]);

    /* test getting/setting pixels */
    stat = GdipBitmapGetPixel(bitmap, 0, 0, &color);
    expect(Ok, stat);
    expect(0xff000000, color);

    stat = GdipBitmapSetPixel(bitmap, 0, 1, 0xffffffff);
    ok((stat == Ok) ||
       broken(stat == InvalidParameter) /* pre-win7 */, "stat=%.8x\n", stat);

    if (stat == Ok)
    {
        stat = GdipBitmapGetPixel(bitmap, 0, 1, &color);
        expect(Ok, stat);
        expect(0xffffffff, color);
    }

    GdipDisposeImage((GpImage*)bitmap);

    /* test initial palette on 4-bit bitmap */
    stat = GdipCreateBitmapFromScan0(2, 2, 4, PixelFormat4bppIndexed, NULL, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImagePaletteSize((GpImage*)bitmap, &size);
    expect(Ok, stat);
    expect(sizeof(UINT)*2+sizeof(ARGB)*16, size);

    stat = GdipGetImagePalette((GpImage*)bitmap, palette, size);
    expect(Ok, stat);
    expect(0, palette->Flags);
    expect(16, palette->Count);

    check_halftone_palette(palette);

    /* test getting/setting pixels */
    stat = GdipBitmapGetPixel(bitmap, 0, 0, &color);
    expect(Ok, stat);
    expect(0xff000000, color);

    stat = GdipBitmapSetPixel(bitmap, 0, 1, 0xffff00ff);
    ok((stat == Ok) ||
       broken(stat == InvalidParameter) /* pre-win7 */, "stat=%.8x\n", stat);

    if (stat == Ok)
    {
        stat = GdipBitmapGetPixel(bitmap, 0, 1, &color);
        expect(Ok, stat);
        expect(0xffff00ff, color);
    }

    GdipDisposeImage((GpImage*)bitmap);

    /* test initial palette on 8-bit bitmap */
    stat = GdipCreateBitmapFromScan0(2, 2, 8, PixelFormat8bppIndexed, NULL, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImagePaletteSize((GpImage*)bitmap, &size);
    expect(Ok, stat);
    expect(sizeof(UINT)*2+sizeof(ARGB)*256, size);

    stat = GdipGetImagePalette((GpImage*)bitmap, palette, size);
    expect(Ok, stat);
    expect(PaletteFlagsHalftone, palette->Flags);
    expect(256, palette->Count);

    check_halftone_palette(palette);

    /* test getting/setting pixels */
    stat = GdipBitmapGetPixel(bitmap, 0, 0, &color);
    expect(Ok, stat);
    expect(0xff000000, color);

    stat = GdipBitmapSetPixel(bitmap, 0, 1, 0xffcccccc);
    ok((stat == Ok) ||
       broken(stat == InvalidParameter) /* pre-win7 */, "stat=%.8x\n", stat);

    if (stat == Ok)
    {
        stat = GdipBitmapGetPixel(bitmap, 0, 1, &color);
        expect(Ok, stat);
        expect(0xffcccccc, color);
    }

    /* test setting/getting a different palette */
    entries[1] = 0xffcccccc;

    stat = GdipSetImagePalette((GpImage*)bitmap, palette);
    expect(Ok, stat);

    entries[1] = 0;

    stat = GdipGetImagePaletteSize((GpImage*)bitmap, &size);
    expect(Ok, stat);
    expect(sizeof(UINT)*2+sizeof(ARGB)*256, size);

    stat = GdipGetImagePalette((GpImage*)bitmap, palette, size);
    expect(Ok, stat);
    expect(PaletteFlagsHalftone, palette->Flags);
    expect(256, palette->Count);
    expect(0xffcccccc, entries[1]);

    /* test count < 256 */
    palette->Flags = 12345;
    palette->Count = 3;

    stat = GdipSetImagePalette((GpImage*)bitmap, palette);
    expect(Ok, stat);

    entries[1] = 0;
    entries[3] = 0xdeadbeef;

    stat = GdipGetImagePaletteSize((GpImage*)bitmap, &size);
    expect(Ok, stat);
    expect(sizeof(UINT)*2+sizeof(ARGB)*3, size);

    stat = GdipGetImagePalette((GpImage*)bitmap, palette, size);
    expect(Ok, stat);
    expect(12345, palette->Flags);
    expect(3, palette->Count);
    expect(0xffcccccc, entries[1]);
    expect(0xdeadbeef, entries[3]);

    /* test count > 256 */
    palette->Count = 257;

    stat = GdipSetImagePalette((GpImage*)bitmap, palette);
    ok(stat == InvalidParameter ||
       broken(stat == Ok), /* Old gdiplus behavior */
       "Expected %.8x, got %.8x\n", InvalidParameter, stat);

    GdipDisposeImage((GpImage*)bitmap);
}