#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_7__ {char bfType; int bfSize; int bfOffBits; int /*<<< orphan*/  bfReserved2; int /*<<< orphan*/  bfReserved1; } ;
struct TYPE_6__ {int biBitCount; int biSize; int biPlanes; int biHeight; int biSizeImage; int /*<<< orphan*/  biWidth; } ;
struct TYPE_5__ {int cy; int /*<<< orphan*/  cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  int INT ;
typedef  int /*<<< orphan*/  ILHEAD ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAPFILEHEADER ;

/* Variables and functions */
 int DIB_GetWidthBytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,char,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static ULONG check_bitmap_data(const ILHEAD *header, const char *bm_data,
    ULONG bm_data_size, const SIZE *bmpsize, INT bpp, const char *comment)
{
    const BITMAPFILEHEADER *bmfh = (const BITMAPFILEHEADER *)bm_data;
    const BITMAPINFOHEADER *bmih = (const BITMAPINFOHEADER *)(bm_data + sizeof(*bmfh));
    ULONG hdr_size, image_size;

    hdr_size = sizeof(*bmfh) + sizeof(*bmih);
    if (bmih->biBitCount <= 8) hdr_size += (1 << bpp) * sizeof(RGBQUAD);

    ok(bmfh->bfType == (('M' << 8) | 'B'), "wrong bfType 0x%02x\n", bmfh->bfType);
    ok(bmfh->bfSize == hdr_size, "wrong bfSize 0x%02x\n", bmfh->bfSize);
    ok(bmfh->bfReserved1 == 0, "wrong bfReserved1 0x%02x\n", bmfh->bfReserved1);
    ok(bmfh->bfReserved2 == 0, "wrong bfReserved2 0x%02x\n", bmfh->bfReserved2);
    ok(bmfh->bfOffBits == hdr_size, "wrong bfOffBits 0x%02x\n", bmfh->bfOffBits);

    ok(bmih->biSize == sizeof(*bmih), "wrong biSize %d\n", bmih->biSize);
    ok(bmih->biPlanes == 1, "wrong biPlanes %d\n", bmih->biPlanes);
    ok(bmih->biBitCount == bpp, "wrong biBitCount %d\n", bmih->biBitCount);

    image_size = DIB_GetWidthBytes(bmih->biWidth, bmih->biBitCount) * bmih->biHeight;
    ok(bmih->biSizeImage == image_size, "wrong biSizeImage %u\n", bmih->biSizeImage);
    ok(bmih->biWidth == bmpsize->cx && bmih->biHeight == bmpsize->cy, "Unexpected bitmap size %d x %d, "
            "expected %d x %d\n", bmih->biWidth, bmih->biHeight, bmpsize->cx, bmpsize->cy);

if (0)
{
    char fname[256];
    FILE *f;
    sprintf(fname, "bmp_%s.bmp", comment);
    f = fopen(fname, "wb");
    fwrite(bm_data, 1, bm_data_size, f);
    fclose(f);
}

    return hdr_size + image_size;
}