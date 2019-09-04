#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rgb ;
typedef  int /*<<< orphan*/  logpalbuf ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  bmibuf ;
typedef  int WORD ;
struct TYPE_28__ {int biClrUsed; } ;
struct TYPE_26__ {int* bmBits; } ;
struct TYPE_33__ {TYPE_3__ dsBmih; TYPE_1__ dsBm; } ;
struct TYPE_32__ {int* BaseAddress; int* AllocationBase; int AllocationProtect; int RegionSize; int State; int Protect; int Type; } ;
struct TYPE_31__ {int peRed; int peBlue; int peGreen; } ;
struct TYPE_25__ {int biSize; int biHeight; int biWidth; int biBitCount; int biPlanes; int biClrUsed; void* biCompression; } ;
struct TYPE_30__ {int rgbRed; int rgbGreen; int rgbBlue; int rgbReserved; int palVersion; int palNumEntries; TYPE_12__ bmiHeader; struct TYPE_30__* bmiColors; TYPE_6__* palPalEntry; } ;
struct TYPE_29__ {int rgbtRed; scalar_t__ rgbtGreen; int rgbtBlue; } ;
struct TYPE_27__ {int bcSize; int bcBitCount; int bcWidth; int bcHeight; int bcPlanes; } ;
struct TYPE_24__ {TYPE_2__ bmciHeader; TYPE_4__* bmciColors; } ;
typedef  TYPE_4__ RGBTRIPLE ;
typedef  TYPE_5__ RGBQUAD ;
typedef  int* PDWORD ;
typedef  TYPE_6__ PALETTEENTRY ;
typedef  TYPE_7__ MEMORY_BASIC_INFORMATION ;
typedef  TYPE_5__ LOGPALETTE ;
typedef  int /*<<< orphan*/ * HPALETTE ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int DWORD ;
typedef  TYPE_9__ DIBSECTION ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int BYTE ;
typedef  TYPE_5__ BITMAPINFO ;
typedef  TYPE_11__ BITMAPCOREINFO ;
typedef  int /*<<< orphan*/  BITMAPCOREHEADER ;

/* Variables and functions */
 void* BI_BITFIELDS ; 
 void* BI_RGB ; 
 void* BI_RLE8 ; 
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreatePalette (TYPE_5__*) ; 
 int /*<<< orphan*/  DIBINDEX (int) ; 
 int /*<<< orphan*/  DIB_PAL_COLORS ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int GetDIBColorTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 int GetDIBits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char**,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 scalar_t__ GetObjectW (int /*<<< orphan*/ *,int,TYPE_9__*) ; 
 int MEM_COMMIT ; 
 int MEM_PRIVATE ; 
 int PAGE_READWRITE ; 
 int /*<<< orphan*/  PALETTEINDEX (int) ; 
 int /*<<< orphan*/  PALETTERGB (int,int,int) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SelectPalette (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SetDIBColorTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int VirtualQuery (int*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcmp (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_color (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_dib_bits_access (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  test_dib_info (int /*<<< orphan*/ *,int*,TYPE_12__*) ; 

__attribute__((used)) static void test_dibsections(void)
{
    HDC hdc, hdcmem, hdcmem2;
    HBITMAP hdib, oldbm, hdib2, oldbm2;
    char bmibuf[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
    char bcibuf[sizeof(BITMAPCOREINFO) + 256 * sizeof(RGBTRIPLE)];
    BITMAPINFO *pbmi = (BITMAPINFO *)bmibuf;
    BITMAPCOREINFO *pbci = (BITMAPCOREINFO *)bcibuf;
    RGBQUAD *colors = pbmi->bmiColors;
    RGBTRIPLE *ccolors = pbci->bmciColors;
    HBITMAP hcoredib;
    char coreBits[256];
    BYTE *bits;
    RGBQUAD rgb[256];
    int ret;
    char logpalbuf[sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY)];
    LOGPALETTE *plogpal = (LOGPALETTE*)logpalbuf;
    PALETTEENTRY *palent = plogpal->palPalEntry;
    WORD *index;
    DWORD *bits32;
    HPALETTE hpal, oldpal;
    DIBSECTION dibsec;
    COLORREF c0, c1;
    int i;
    MEMORY_BASIC_INFORMATION info;

    hdc = GetDC(0);

    memset(pbmi, 0, sizeof(bmibuf));
    pbmi->bmiHeader.biSize = sizeof(pbmi->bmiHeader);
    pbmi->bmiHeader.biHeight = 100;
    pbmi->bmiHeader.biWidth = 512;
    pbmi->bmiHeader.biBitCount = 24;
    pbmi->bmiHeader.biPlanes = 1;
    pbmi->bmiHeader.biCompression = BI_RGB;

    SetLastError(0xdeadbeef);

    /* invalid pointer for BITMAPINFO
       (*bits should be NULL on error) */
    bits = (BYTE*)0xdeadbeef;
    hdib = CreateDIBSection(hdc, NULL, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hdib == NULL && bits == NULL, "CreateDIBSection failed for invalid parameter: bmi == 0x0\n");

    hdib = CreateDIBSection(hdc, pbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection error %d\n", GetLastError());
    ok(GetObjectW(hdib, sizeof(DIBSECTION), &dibsec) != 0, "GetObject failed for DIBSection\n");
    ok(dibsec.dsBm.bmBits == bits, "dibsec.dsBits %p != bits %p\n", dibsec.dsBm.bmBits, bits);

    /* test the DIB memory */
    ok(VirtualQuery(bits, &info, sizeof(info)) == sizeof(info),
        "VirtualQuery failed\n");
    ok(info.BaseAddress == bits, "%p != %p\n", info.BaseAddress, bits);
    ok(info.AllocationBase == bits, "%p != %p\n", info.AllocationBase, bits);
    ok(info.AllocationProtect == PAGE_READWRITE, "%x != PAGE_READWRITE\n", info.AllocationProtect);
    ok(info.RegionSize == 0x26000, "0x%lx != 0x26000\n", info.RegionSize);
    ok(info.State == MEM_COMMIT, "%x != MEM_COMMIT\n", info.State);
    ok(info.Protect == PAGE_READWRITE, "%x != PAGE_READWRITE\n", info.Protect);
    ok(info.Type == MEM_PRIVATE, "%x != MEM_PRIVATE\n", info.Type);

    test_dib_bits_access( hdib, bits );

    test_dib_info(hdib, bits, &pbmi->bmiHeader);
    DeleteObject(hdib);

    /* Test a top-down DIB. */
    pbmi->bmiHeader.biHeight = -100;
    hdib = CreateDIBSection(hdc, pbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection error %d\n", GetLastError());
    test_dib_info(hdib, bits, &pbmi->bmiHeader);
    DeleteObject(hdib);

    pbmi->bmiHeader.biHeight = 100;
    pbmi->bmiHeader.biBitCount = 8;
    pbmi->bmiHeader.biCompression = BI_RLE8;
    SetLastError(0xdeadbeef);
    hdib = CreateDIBSection(hdc, pbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hdib == NULL, "CreateDIBSection should fail when asked to create a compressed DIB section\n");
    ok(GetLastError() == 0xdeadbeef, "wrong error %d\n", GetLastError());

    pbmi->bmiHeader.biBitCount = 16;
    pbmi->bmiHeader.biCompression = BI_BITFIELDS;
    ((PDWORD)pbmi->bmiColors)[0] = 0xf800;
    ((PDWORD)pbmi->bmiColors)[1] = 0x07e0;
    ((PDWORD)pbmi->bmiColors)[2] = 0x001f;
    SetLastError(0xdeadbeef);
    hdib = CreateDIBSection(hdc, pbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection error %d\n", GetLastError());

    /* test the DIB memory */
    ok(VirtualQuery(bits, &info, sizeof(info)) == sizeof(info),
        "VirtualQuery failed\n");
    ok(info.BaseAddress == bits, "%p != %p\n", info.BaseAddress, bits);
    ok(info.AllocationBase == bits, "%p != %p\n", info.AllocationBase, bits);
    ok(info.AllocationProtect == PAGE_READWRITE, "%x != PAGE_READWRITE\n", info.AllocationProtect);
    ok(info.RegionSize == 0x19000, "0x%lx != 0x19000\n", info.RegionSize);
    ok(info.State == MEM_COMMIT, "%x != MEM_COMMIT\n", info.State);
    ok(info.Protect == PAGE_READWRITE, "%x != PAGE_READWRITE\n", info.Protect);
    ok(info.Type == MEM_PRIVATE, "%x != MEM_PRIVATE\n", info.Type);

    test_dib_info(hdib, bits, &pbmi->bmiHeader);
    DeleteObject(hdib);

    memset(pbmi, 0, sizeof(bmibuf));
    pbmi->bmiHeader.biSize = sizeof(pbmi->bmiHeader);
    pbmi->bmiHeader.biHeight = 16;
    pbmi->bmiHeader.biWidth = 16;
    pbmi->bmiHeader.biBitCount = 1;
    pbmi->bmiHeader.biPlanes = 1;
    pbmi->bmiHeader.biCompression = BI_RGB;
    colors[0].rgbRed = 0xff;
    colors[0].rgbGreen = 0;
    colors[0].rgbBlue = 0;
    colors[1].rgbRed = 0;
    colors[1].rgbGreen = 0;
    colors[1].rgbBlue = 0xff;

    hdib = CreateDIBSection(hdc, pbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection failed\n");
    ok(GetObjectW(hdib, sizeof(DIBSECTION), &dibsec) != 0, "GetObject failed for DIBSection\n");
    ok(dibsec.dsBmih.biClrUsed == 2,
        "created DIBSection: wrong biClrUsed field: %u, should be: %u\n", dibsec.dsBmih.biClrUsed, 2);

    /* Test if the old BITMAPCOREINFO structure is supported */

    pbci->bmciHeader.bcSize = sizeof(BITMAPCOREHEADER);
    pbci->bmciHeader.bcBitCount = 0;

    ret = GetDIBits(hdc, hdib, 0, 16, NULL, (BITMAPINFO*) pbci, DIB_RGB_COLORS);
    ok(ret, "GetDIBits doesn't work with a BITMAPCOREHEADER\n");
    ok((pbci->bmciHeader.bcWidth == 16) && (pbci->bmciHeader.bcHeight == 16)
        && (pbci->bmciHeader.bcBitCount == 1) && (pbci->bmciHeader.bcPlanes == 1),
    "GetDIBits didn't fill in the BITMAPCOREHEADER structure properly\n");

    ret = GetDIBits(hdc, hdib, 0, 16, &coreBits, (BITMAPINFO*) pbci, DIB_RGB_COLORS);
    ok(ret, "GetDIBits doesn't work with a BITMAPCOREHEADER\n");
    ok((ccolors[0].rgbtRed == 0xff) && (ccolors[0].rgbtGreen == 0) &&
        (ccolors[0].rgbtBlue == 0) && (ccolors[1].rgbtRed == 0) &&
        (ccolors[1].rgbtGreen == 0) && (ccolors[1].rgbtBlue == 0xff),
        "The color table has not been translated to the old BITMAPCOREINFO format\n");

    hcoredib = CreateDIBSection(hdc, (BITMAPINFO*) pbci, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hcoredib != NULL, "CreateDIBSection failed with a BITMAPCOREINFO\n");

    ZeroMemory(ccolors, 256 * sizeof(RGBTRIPLE));
    ret = GetDIBits(hdc, hcoredib, 0, 16, &coreBits, (BITMAPINFO*) pbci, DIB_RGB_COLORS);
    ok(ret, "GetDIBits doesn't work with a BITMAPCOREHEADER\n");
    ok((ccolors[0].rgbtRed == 0xff) && (ccolors[0].rgbtGreen == 0) &&
        (ccolors[0].rgbtBlue == 0) && (ccolors[1].rgbtRed == 0) &&
        (ccolors[1].rgbtGreen == 0) && (ccolors[1].rgbtBlue == 0xff),
        "The color table has not been translated to the old BITMAPCOREINFO format\n");

    DeleteObject(hcoredib);

    hdcmem = CreateCompatibleDC(hdc);
    oldbm = SelectObject(hdcmem, hdib);

    ret = GetDIBColorTable(hdcmem, 0, 2, rgb);
    ok(ret == 2, "GetDIBColorTable returned %d\n", ret);
    ok(!memcmp(rgb, pbmi->bmiColors, 2 * sizeof(RGBQUAD)),
       "GetDIBColorTable returns table 0: r%02x g%02x b%02x res%02x 1: r%02x g%02x b%02x res%02x\n",
       rgb[0].rgbRed, rgb[0].rgbGreen, rgb[0].rgbBlue, rgb[0].rgbReserved,
       rgb[1].rgbRed, rgb[1].rgbGreen, rgb[1].rgbBlue, rgb[1].rgbReserved);

    c0 = RGB(colors[0].rgbRed, colors[0].rgbGreen, colors[0].rgbBlue);
    c1 = RGB(colors[1].rgbRed, colors[1].rgbGreen, colors[1].rgbBlue);

    test_color(hdcmem, DIBINDEX(0), c0);
    test_color(hdcmem, DIBINDEX(1), c1);
    test_color(hdcmem, DIBINDEX(2), c0);
    test_color(hdcmem, PALETTEINDEX(0), c0);
    test_color(hdcmem, PALETTEINDEX(1), c0);
    test_color(hdcmem, PALETTEINDEX(2), c0);
    test_color(hdcmem, PALETTERGB(colors[0].rgbRed, colors[0].rgbGreen, colors[0].rgbBlue), c0);
    test_color(hdcmem, PALETTERGB(colors[1].rgbRed, colors[1].rgbGreen, colors[1].rgbBlue), c1);
    test_color(hdcmem, PALETTERGB(0, 0, 0), c0);
    test_color(hdcmem, PALETTERGB(0xff, 0xff, 0xff), c0);
    test_color(hdcmem, PALETTERGB(0, 0, 0xfe), c1);

    SelectObject(hdcmem, oldbm);
    DeleteObject(hdib);

    colors[0].rgbRed = 0xff;
    colors[0].rgbGreen = 0xff;
    colors[0].rgbBlue = 0xff;
    colors[1].rgbRed = 0;
    colors[1].rgbGreen = 0;
    colors[1].rgbBlue = 0;

    hdib = CreateDIBSection(hdc, pbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection failed\n");

    test_dib_info(hdib, bits, &pbmi->bmiHeader);

    oldbm = SelectObject(hdcmem, hdib);

    ret = GetDIBColorTable(hdcmem, 0, 2, rgb);
    ok(ret == 2, "GetDIBColorTable returned %d\n", ret);
    ok(!memcmp(rgb, colors, 2 * sizeof(RGBQUAD)),
       "GetDIBColorTable returns table 0: r%02x g%02x b%02x res%02x 1: r%02x g%02x b%02x res%02x\n",
       rgb[0].rgbRed, rgb[0].rgbGreen, rgb[0].rgbBlue, rgb[0].rgbReserved,
       rgb[1].rgbRed, rgb[1].rgbGreen, rgb[1].rgbBlue, rgb[1].rgbReserved);

    SelectObject(hdcmem, oldbm);
    test_dib_info(hdib, bits, &pbmi->bmiHeader);
    DeleteObject(hdib);

    pbmi->bmiHeader.biBitCount = 4;
    for (i = 0; i < 16; i++) {
        colors[i].rgbRed = i;
        colors[i].rgbGreen = 16-i;
        colors[i].rgbBlue = 0;
    }
    hdib = CreateDIBSection(hdcmem, pbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection failed\n");
    ok(GetObjectW(hdib, sizeof(DIBSECTION), &dibsec) != 0, "GetObject failed for DIB Section\n");
    ok(dibsec.dsBmih.biClrUsed == 16,
       "created DIBSection: wrong biClrUsed field: %u, should be: %u\n", dibsec.dsBmih.biClrUsed, 16);
    test_dib_info(hdib, bits, &pbmi->bmiHeader);
    DeleteObject(hdib);

    pbmi->bmiHeader.biBitCount = 8;

    for (i = 0; i < 128; i++) {
        colors[i].rgbRed = 255 - i * 2;
        colors[i].rgbGreen = i * 2;
        colors[i].rgbBlue = 0;
        colors[255 - i].rgbRed = 0;
        colors[255 - i].rgbGreen = i * 2;
        colors[255 - i].rgbBlue = 255 - i * 2;
    }
    hdib = CreateDIBSection(hdcmem, pbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection failed\n");
    ok(GetObjectW(hdib, sizeof(DIBSECTION), &dibsec) != 0, "GetObject failed for DIB Section\n");
    ok(dibsec.dsBmih.biClrUsed == 256,
        "created DIBSection: wrong biClrUsed field: %u, should be: %u\n", dibsec.dsBmih.biClrUsed, 256);

    oldbm = SelectObject(hdcmem, hdib);

    for (i = 0; i < 256; i++) {
        test_color(hdcmem, DIBINDEX(i), RGB(colors[i].rgbRed, colors[i].rgbGreen, colors[i].rgbBlue));
        test_color(hdcmem, PALETTERGB(colors[i].rgbRed, colors[i].rgbGreen, colors[i].rgbBlue),
                   RGB(colors[i].rgbRed, colors[i].rgbGreen, colors[i].rgbBlue));
    }

    SelectObject(hdcmem, oldbm);
    test_dib_info(hdib, bits, &pbmi->bmiHeader);
    DeleteObject(hdib);

    pbmi->bmiHeader.biBitCount = 1;

    /* Now create a palette and a palette indexed dib section */
    memset(plogpal, 0, sizeof(logpalbuf));
    plogpal->palVersion = 0x300;
    plogpal->palNumEntries = 2;
    palent[0].peRed = 0xff;
    palent[0].peBlue = 0xff;
    palent[1].peGreen = 0xff;

    index = (WORD*)pbmi->bmiColors;
    *index++ = 0;
    *index = 1;
    hpal = CreatePalette(plogpal);
    ok(hpal != NULL, "CreatePalette failed\n");
    oldpal = SelectPalette(hdc, hpal, TRUE);
    hdib = CreateDIBSection(hdc, pbmi, DIB_PAL_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection failed\n");
    ok(GetObjectW(hdib, sizeof(DIBSECTION), &dibsec) != 0, "GetObject failed for DIB Section\n");
    ok(dibsec.dsBmih.biClrUsed == 2, "created DIBSection: wrong biClrUsed field: %u, should be: %u\n", dibsec.dsBmih.biClrUsed, 2);

    /* The colour table has already been grabbed from the dc, so we select back the
       old palette */

    SelectPalette(hdc, oldpal, TRUE);
    oldbm = SelectObject(hdcmem, hdib);
    oldpal = SelectPalette(hdcmem, hpal, TRUE);

    ret = GetDIBColorTable(hdcmem, 0, 2, rgb);
    ok(ret == 2, "GetDIBColorTable returned %d\n", ret);
    ok(rgb[0].rgbRed == 0xff && rgb[0].rgbBlue == 0xff && rgb[0].rgbGreen == 0 &&
       rgb[1].rgbRed == 0    && rgb[1].rgbBlue == 0    && rgb[1].rgbGreen == 0xff,
       "GetDIBColorTable returns table 0: r%02x g%02x b%02x res%02x 1: r%02x g%02x b%02x res%02x\n",
       rgb[0].rgbRed, rgb[0].rgbGreen, rgb[0].rgbBlue, rgb[0].rgbReserved,
       rgb[1].rgbRed, rgb[1].rgbGreen, rgb[1].rgbBlue, rgb[1].rgbReserved);

    c0 = RGB(palent[0].peRed, palent[0].peGreen, palent[0].peBlue);
    c1 = RGB(palent[1].peRed, palent[1].peGreen, palent[1].peBlue);

    test_color(hdcmem, DIBINDEX(0), c0);
    test_color(hdcmem, DIBINDEX(1), c1);
    test_color(hdcmem, DIBINDEX(2), c0);
    test_color(hdcmem, PALETTEINDEX(0), c0);
    test_color(hdcmem, PALETTEINDEX(1), c1);
    test_color(hdcmem, PALETTEINDEX(2), c0);
    test_color(hdcmem, PALETTERGB(palent[0].peRed, palent[0].peGreen, palent[0].peBlue), c0);
    test_color(hdcmem, PALETTERGB(palent[1].peRed, palent[1].peGreen, palent[1].peBlue), c1);
    test_color(hdcmem, PALETTERGB(0, 0, 0), c1);
    test_color(hdcmem, PALETTERGB(0xff, 0xff, 0xff), c0);
    test_color(hdcmem, PALETTERGB(0, 0, 0xfe), c0);
    test_color(hdcmem, PALETTERGB(0, 1, 0), c1);
    test_color(hdcmem, PALETTERGB(0x3f, 0, 0x3f), c1);
    test_color(hdcmem, PALETTERGB(0x40, 0, 0x40), c0);

    /* Bottom and 2nd row from top green, everything else magenta */
    bits[0] = bits[1] = 0xff;
    bits[13 * 4] = bits[13*4 + 1] = 0xff;

    test_dib_info(hdib, bits, &pbmi->bmiHeader);

    pbmi->bmiHeader.biBitCount = 32;

    hdib2 = CreateDIBSection(NULL, pbmi, DIB_RGB_COLORS, (void **)&bits32, NULL, 0);
    ok(hdib2 != NULL, "CreateDIBSection failed\n");
    hdcmem2 = CreateCompatibleDC(hdc);
    oldbm2 = SelectObject(hdcmem2, hdib2);

    BitBlt(hdcmem2, 0, 0, 16,16, hdcmem, 0, 0, SRCCOPY);

    ok(bits32[0] == 0xff00, "lower left pixel is %08x\n", bits32[0]);
    ok(bits32[17] == 0xff00ff, "bottom but one, left pixel is %08x\n", bits32[17]);

    SelectObject(hdcmem2, oldbm2);
    test_dib_info(hdib2, bits32, &pbmi->bmiHeader);
    DeleteObject(hdib2);

    SelectObject(hdcmem, oldbm);
    SelectPalette(hdcmem, oldpal, TRUE);
    DeleteObject(hdib);
    DeleteObject(hpal);


    pbmi->bmiHeader.biBitCount = 8;

    memset(plogpal, 0, sizeof(logpalbuf));
    plogpal->palVersion = 0x300;
    plogpal->palNumEntries = 256;

    for (i = 0; i < 128; i++) {
        palent[i].peRed = 255 - i * 2;
        palent[i].peBlue = i * 2;
        palent[i].peGreen = 0;
        palent[255 - i].peRed = 0;
        palent[255 - i].peGreen = i * 2;
        palent[255 - i].peBlue = 255 - i * 2;
    }

    index = (WORD*)pbmi->bmiColors;
    for (i = 0; i < 256; i++) {
        *index++ = i;
    }

    hpal = CreatePalette(plogpal);
    ok(hpal != NULL, "CreatePalette failed\n");
    oldpal = SelectPalette(hdc, hpal, TRUE);
    hdib = CreateDIBSection(hdc, pbmi, DIB_PAL_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection failed\n");
    ok(GetObjectW(hdib, sizeof(DIBSECTION), &dibsec) != 0, "GetObject failed for DIB Section\n");
    ok(dibsec.dsBmih.biClrUsed == 256, "created DIBSection: wrong biClrUsed field: %u, should be: %u\n", dibsec.dsBmih.biClrUsed, 256);

    test_dib_info(hdib, bits, &pbmi->bmiHeader);

    SelectPalette(hdc, oldpal, TRUE);
    oldbm = SelectObject(hdcmem, hdib);
    oldpal = SelectPalette(hdcmem, hpal, TRUE);

    ret = GetDIBColorTable(hdcmem, 0, 256, rgb);
    ok(ret == 256, "GetDIBColorTable returned %d\n", ret);
    for (i = 0; i < 256; i++) {
        ok(rgb[i].rgbRed == palent[i].peRed && 
            rgb[i].rgbBlue == palent[i].peBlue && 
            rgb[i].rgbGreen == palent[i].peGreen, 
            "GetDIBColorTable returns table %d: r%02x g%02x b%02x res%02x\n",
            i, rgb[i].rgbRed, rgb[i].rgbGreen, rgb[i].rgbBlue, rgb[i].rgbReserved);
    }

    for (i = 0; i < 256; i++) {
        test_color(hdcmem, DIBINDEX(i), RGB(palent[i].peRed, palent[i].peGreen, palent[i].peBlue));
        test_color(hdcmem, PALETTEINDEX(i), RGB(palent[i].peRed, palent[i].peGreen, palent[i].peBlue));
        test_color(hdcmem, PALETTERGB(palent[i].peRed, palent[i].peGreen, palent[i].peBlue), 
                   RGB(palent[i].peRed, palent[i].peGreen, palent[i].peBlue));
    }

    SelectPalette(hdcmem, oldpal, TRUE);
    SelectObject(hdcmem, oldbm);
    DeleteObject(hdib);
    DeleteObject(hpal);

    plogpal->palNumEntries = 37;
    hpal = CreatePalette(plogpal);
    ok(hpal != NULL, "CreatePalette failed\n");
    oldpal = SelectPalette(hdc, hpal, TRUE);
    pbmi->bmiHeader.biClrUsed = 142;
    hdib = CreateDIBSection(hdc, pbmi, DIB_PAL_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection failed\n");
    ok(GetObjectW(hdib, sizeof(DIBSECTION), &dibsec) != 0, "GetObject failed for DIB Section\n");
    ok(dibsec.dsBmih.biClrUsed == 256, "created DIBSection: wrong biClrUsed field: %u, should be: %u\n", dibsec.dsBmih.biClrUsed, 256);

    test_dib_info(hdib, bits, &pbmi->bmiHeader);

    SelectPalette(hdc, oldpal, TRUE);
    oldbm = SelectObject(hdcmem, hdib);

    memset( rgb, 0xcc, sizeof(rgb) );
    ret = GetDIBColorTable(hdcmem, 0, 256, rgb);
    ok(ret == 256, "GetDIBColorTable returned %d\n", ret);
    for (i = 0; i < 256; i++)
    {
        if (i < pbmi->bmiHeader.biClrUsed)
        {
            ok(rgb[i].rgbRed == palent[i % 37].peRed &&
               rgb[i].rgbBlue == palent[i % 37].peBlue &&
               rgb[i].rgbGreen == palent[i % 37].peGreen,
               "GetDIBColorTable returns table %d: r %02x g %02x b %02x res%02x\n",
               i, rgb[i].rgbRed, rgb[i].rgbGreen, rgb[i].rgbBlue, rgb[i].rgbReserved);
            test_color(hdcmem, DIBINDEX(i),
                       RGB(palent[i % 37].peRed, palent[i % 37].peGreen, palent[i % 37].peBlue));
        }
        else
        {
            ok(rgb[i].rgbRed == 0 && rgb[i].rgbBlue == 0 && rgb[i].rgbGreen == 0,
               "GetDIBColorTable returns table %d: r %02x g %02x b %02x res%02x\n",
               i, rgb[i].rgbRed, rgb[i].rgbGreen, rgb[i].rgbBlue, rgb[i].rgbReserved);
            test_color(hdcmem, DIBINDEX(i), 0 );
        }
    }
    pbmi->bmiHeader.biClrUsed = 173;
    memset( pbmi->bmiColors, 0xcc, 256 * sizeof(RGBQUAD) );
    GetDIBits( hdc, hdib, 0, 1, NULL, pbmi, DIB_RGB_COLORS );
    ok( pbmi->bmiHeader.biClrUsed == 0, "wrong colors %u\n", pbmi->bmiHeader.biClrUsed );
    for (i = 0; i < 256; i++)
    {
        if (i < 142)
            ok(colors[i].rgbRed == palent[i % 37].peRed &&
               colors[i].rgbBlue == palent[i % 37].peBlue &&
               colors[i].rgbGreen == palent[i % 37].peGreen,
               "GetDIBits returns table %d: r %02x g %02x b %02x res%02x\n",
               i, colors[i].rgbRed, colors[i].rgbGreen, colors[i].rgbBlue, colors[i].rgbReserved);
        else
            ok(colors[i].rgbRed == 0 && colors[i].rgbBlue == 0 && colors[i].rgbGreen == 0,
               "GetDIBits returns table %d: r %02x g %02x b %02x res%02x\n",
               i, colors[i].rgbRed, colors[i].rgbGreen, colors[i].rgbBlue, colors[i].rgbReserved);
    }

    rgb[0].rgbRed = 1;
    rgb[0].rgbGreen = 2;
    rgb[0].rgbBlue = 3;
    rgb[0].rgbReserved = 123;
    ret = SetDIBColorTable( hdcmem, 0, 1, rgb );
    ok( ret == 1, "SetDIBColorTable returned unexpected result %u\n", ret );
    ok( rgb[0].rgbReserved == 123, "Expected rgbReserved = 123, got %u\n", rgb[0].rgbReserved );

    rgb[0].rgbRed = rgb[0].rgbGreen = rgb[0].rgbBlue = rgb[0].rgbReserved = -1;
    ret = GetDIBColorTable( hdcmem, 0, 1, rgb );
    ok( ret == 1, "GetDIBColorTable returned unexpected result %u\n", ret );
    ok( rgb[0].rgbRed == 1, "Expected rgbRed = 1, got %u\n", rgb[0].rgbRed );
    ok( rgb[0].rgbGreen == 2, "Expected rgbGreen = 2, got %u\n", rgb[0].rgbGreen );
    ok( rgb[0].rgbBlue == 3, "Expected rgbBlue = 3, got %u\n", rgb[0].rgbBlue );
    ok( rgb[0].rgbReserved == 0, "Expected rgbReserved = 0, got %u\n", rgb[0].rgbReserved );

    SelectObject(hdcmem, oldbm);
    DeleteObject(hdib);
    DeleteObject(hpal);

    /* ClrUsed ignored on > 8bpp */
    pbmi->bmiHeader.biBitCount = 16;
    pbmi->bmiHeader.biClrUsed = 37;
    hdib = CreateDIBSection(hdc, pbmi, DIB_PAL_COLORS, (void**)&bits, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection failed\n");
    ok(GetObjectW(hdib, sizeof(DIBSECTION), &dibsec) != 0, "GetObject failed for DIB Section\n");
    ok(dibsec.dsBmih.biClrUsed == 0, "created DIBSection: wrong biClrUsed field: %u\n", dibsec.dsBmih.biClrUsed);
    oldbm = SelectObject(hdcmem, hdib);
    ret = GetDIBColorTable(hdcmem, 0, 256, rgb);
    ok(ret == 0, "GetDIBColorTable returned %d\n", ret);
    SelectObject(hdcmem, oldbm);
    DeleteObject(hdib);

    DeleteDC(hdcmem);
    DeleteDC(hdcmem2);
    ReleaseDC(0, hdc);
}