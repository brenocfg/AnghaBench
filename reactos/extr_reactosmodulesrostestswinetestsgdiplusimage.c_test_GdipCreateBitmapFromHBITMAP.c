#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int biSize; int biHeight; int biWidth; int biBitCount; int biPlanes; void* biCompression; scalar_t__ biClrUsed; } ;
struct TYPE_11__ {TYPE_2__ bmiHeader; } ;
struct TYPE_8__ {int* masks; } ;
union BITMAPINFOUNION {TYPE_7__ bi; TYPE_1__ bf; } ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  bmi ;
struct TYPE_10__ {int palVersion; int palNumEntries; } ;
typedef  int REAL ;
typedef  scalar_t__ PixelFormat ;
typedef  TYPE_3__ LOGPALETTE ;
typedef  int /*<<< orphan*/ * HPALETTE ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 void* BI_BITFIELDS ; 
 void* BI_RGB ; 
 int /*<<< orphan*/ * CreateBitmap (int const,int const,int,int,scalar_t__**) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreatePalette (TYPE_3__*) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* GdipAlloc (int) ; 
 scalar_t__ GdipBitmapSetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GdipCreateBitmapFromHBITMAP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFree (TYPE_3__*) ; 
 scalar_t__ GdipGetImageDimension (int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ GdipGetImagePixelFormat (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ImageFormatMemoryBMP ; 
 scalar_t__ InvalidParameter ; 
 scalar_t__ Ok ; 
 scalar_t__ PixelFormat16bppRGB555 ; 
 scalar_t__ PixelFormat16bppRGB565 ; 
 int /*<<< orphan*/  expect (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  expect_rawformat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (int const,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_GdipCreateBitmapFromHBITMAP(void)
{
    GpBitmap* gpbm = NULL;
    HBITMAP hbm = NULL;
    HPALETTE hpal = NULL;
    GpStatus stat;
    BYTE buff[1000];
    LOGPALETTE* LogPal = NULL;
    REAL width, height;
    const REAL WIDTH1 = 5;
    const REAL HEIGHT1 = 15;
    const REAL WIDTH2 = 10;
    const REAL HEIGHT2 = 20;
    HDC hdc;
    union BITMAPINFOUNION bmi;
    BYTE *bits;
    PixelFormat format;

    stat = GdipCreateBitmapFromHBITMAP(NULL, NULL, NULL);
    expect(InvalidParameter, stat);

    hbm = CreateBitmap(WIDTH1, HEIGHT1, 1, 1, NULL);
    stat = GdipCreateBitmapFromHBITMAP(hbm, NULL, NULL);
    expect(InvalidParameter, stat);

    stat = GdipCreateBitmapFromHBITMAP(hbm, NULL, &gpbm);
    expect(Ok, stat);
    expect(Ok, GdipGetImageDimension((GpImage*) gpbm, &width, &height));
    expectf(WIDTH1,  width);
    expectf(HEIGHT1, height);
    if (stat == Ok)
        GdipDisposeImage((GpImage*)gpbm);
    DeleteObject(hbm);

    memset(buff, 0, sizeof(buff));
    hbm = CreateBitmap(WIDTH2, HEIGHT2, 1, 1, &buff);
    stat = GdipCreateBitmapFromHBITMAP(hbm, NULL, &gpbm);
    expect(Ok, stat);
    /* raw format */
    expect_rawformat(&ImageFormatMemoryBMP, (GpImage*)gpbm, __LINE__, FALSE);

    expect(Ok, GdipGetImageDimension((GpImage*) gpbm, &width, &height));
    expectf(WIDTH2,  width);
    expectf(HEIGHT2, height);
    if (stat == Ok)
        GdipDisposeImage((GpImage*)gpbm);
    DeleteObject(hbm);

    hdc = CreateCompatibleDC(0);
    ok(hdc != NULL, "CreateCompatibleDC failed\n");
    bmi.bi.bmiHeader.biSize = sizeof(bmi.bi.bmiHeader);
    bmi.bi.bmiHeader.biHeight = HEIGHT1;
    bmi.bi.bmiHeader.biWidth = WIDTH1;
    bmi.bi.bmiHeader.biBitCount = 24;
    bmi.bi.bmiHeader.biPlanes = 1;
    bmi.bi.bmiHeader.biCompression = BI_RGB;
    bmi.bi.bmiHeader.biClrUsed = 0;

    hbm = CreateDIBSection(hdc, &bmi.bi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hbm != NULL, "CreateDIBSection failed\n");

    bits[0] = 0;

    stat = GdipCreateBitmapFromHBITMAP(hbm, NULL, &gpbm);
    expect(Ok, stat);
    expect(Ok, GdipGetImageDimension((GpImage*) gpbm, &width, &height));
    expectf(WIDTH1,  width);
    expectf(HEIGHT1, height);
    if (stat == Ok)
    {
        /* test whether writing to the bitmap affects the original */
        stat = GdipBitmapSetPixel(gpbm, 0, 0, 0xffffffff);
        expect(Ok, stat);

        expect(0, bits[0]);

        GdipDisposeImage((GpImage*)gpbm);
    }

    LogPal = GdipAlloc(sizeof(LOGPALETTE));
    ok(LogPal != NULL, "unable to allocate LOGPALETTE\n");
    LogPal->palVersion = 0x300;
    LogPal->palNumEntries = 1;
    hpal = CreatePalette(LogPal);
    ok(hpal != NULL, "CreatePalette failed\n");
    GdipFree(LogPal);

    stat = GdipCreateBitmapFromHBITMAP(hbm, hpal, &gpbm);
    expect(Ok, stat);

    if (stat == Ok)
        GdipDisposeImage((GpImage*)gpbm);

    DeleteObject(hpal);
    DeleteObject(hbm);

    /* 16-bit 555 dib, rgb */
    bmi.bi.bmiHeader.biBitCount = 16;
    bmi.bi.bmiHeader.biCompression = BI_RGB;

    hbm = CreateDIBSection(hdc, &bmi.bi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hbm != NULL, "CreateDIBSection failed\n");

    bits[0] = 0;

    stat = GdipCreateBitmapFromHBITMAP(hbm, NULL, &gpbm);
    expect(Ok, stat);

    if (stat == Ok)
    {
        stat = GdipGetImageDimension((GpImage*) gpbm, &width, &height);
        expect(Ok, stat);
        expectf(WIDTH1,  width);
        expectf(HEIGHT1, height);

        stat = GdipGetImagePixelFormat((GpImage*) gpbm, &format);
        expect(Ok, stat);
        expect(PixelFormat16bppRGB555, format);

        GdipDisposeImage((GpImage*)gpbm);
    }
    DeleteObject(hbm);

    /* 16-bit 555 dib, with bitfields */
    bmi.bi.bmiHeader.biSize = sizeof(bmi);
    bmi.bi.bmiHeader.biCompression = BI_BITFIELDS;
    bmi.bf.masks[0] = 0x7c00;
    bmi.bf.masks[1] = 0x3e0;
    bmi.bf.masks[2] = 0x1f;

    hbm = CreateDIBSection(hdc, &bmi.bi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hbm != NULL, "CreateDIBSection failed\n");

    bits[0] = 0;

    stat = GdipCreateBitmapFromHBITMAP(hbm, NULL, &gpbm);
    expect(Ok, stat);

    if (stat == Ok)
    {
        stat = GdipGetImageDimension((GpImage*) gpbm, &width, &height);
        expect(Ok, stat);
        expectf(WIDTH1,  width);
        expectf(HEIGHT1, height);

        stat = GdipGetImagePixelFormat((GpImage*) gpbm, &format);
        expect(Ok, stat);
        expect(PixelFormat16bppRGB555, format);

        GdipDisposeImage((GpImage*)gpbm);
    }
    DeleteObject(hbm);

    /* 16-bit 565 dib, with bitfields */
    bmi.bf.masks[0] = 0xf800;
    bmi.bf.masks[1] = 0x7e0;
    bmi.bf.masks[2] = 0x1f;

    hbm = CreateDIBSection(hdc, &bmi.bi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hbm != NULL, "CreateDIBSection failed\n");

    bits[0] = 0;

    stat = GdipCreateBitmapFromHBITMAP(hbm, NULL, &gpbm);
    expect(Ok, stat);

    if (stat == Ok)
    {
        stat = GdipGetImageDimension((GpImage*) gpbm, &width, &height);
        expect(Ok, stat);
        expectf(WIDTH1,  width);
        expectf(HEIGHT1, height);

        stat = GdipGetImagePixelFormat((GpImage*) gpbm, &format);
        expect(Ok, stat);
        expect(PixelFormat16bppRGB565, format);

        GdipDisposeImage((GpImage*)gpbm);
    }
    DeleteObject(hbm);

    DeleteDC(hdc);
}