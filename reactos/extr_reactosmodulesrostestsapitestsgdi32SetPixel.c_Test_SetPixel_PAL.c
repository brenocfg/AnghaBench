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
typedef  int WORD ;
typedef  int USHORT ;
struct TYPE_6__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biXPelsPerMeter; int biYPelsPerMeter; int biClrUsed; scalar_t__ biClrImportant; scalar_t__ biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_7__ {TYPE_1__ bmiHeader; } ;
typedef  TYPE_2__* PVOID ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  LOGPALETTE ;
typedef  int /*<<< orphan*/ * HPALETTE ;
typedef  scalar_t__ HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 scalar_t__ CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateDIBSection (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreatePalette (int /*<<< orphan*/ *) ; 
 int DIBINDEX (int) ; 
 int /*<<< orphan*/  DIB_PAL_COLORS ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int PALETTEINDEX (int) ; 
 int RGB (int,int,int) ; 
 scalar_t__ SelectObject (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SelectPalette (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixel (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpal ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 

void Test_SetPixel_PAL()
{
    struct
    {
        BITMAPINFOHEADER bmiHeader;
        WORD bmiColors[8];
    } bmibuffer;
    BITMAPINFO *pbmi = (PVOID)&bmibuffer;
    HBITMAP hbmp;
    HDC hdc;
    HPALETTE hpal, hpalOld;
    PULONG pulBits;
    USHORT i;

    /* Initialize the BITMAPINFO */
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biWidth = 1;
    pbmi->bmiHeader.biHeight = 1;
    pbmi->bmiHeader.biPlanes = 1;
    pbmi->bmiHeader.biBitCount = 8;
    pbmi->bmiHeader.biCompression = BI_RGB;
    pbmi->bmiHeader.biSizeImage = 0;
    pbmi->bmiHeader.biXPelsPerMeter = 1;
    pbmi->bmiHeader.biYPelsPerMeter = 1;
    pbmi->bmiHeader.biClrUsed = 8;
    pbmi->bmiHeader.biClrImportant = 0;
    for( i = 0; i < 8; i++ )
    {
        bmibuffer.bmiColors[i] = i + 1;
    }

    /* Create a memory DC */
    hdc = CreateCompatibleDC(0);
    ok(hdc != 0, "failed\n");

    /* Create a DIB section and select it */
    hbmp = CreateDIBSection(hdc, pbmi, DIB_PAL_COLORS, (PVOID*)&pulBits, 0, 0 );
    ok(hbmp != NULL, "CreateDIBSection failed with error %ld\n", GetLastError());
    ok(SelectObject(hdc, hbmp) != 0, "SelectObject failed\n");

    ok_long(SetPixel(hdc, 0, 0, 0), 0);
    ok_long(pulBits[0], 8);
    ok_long(SetPixel(hdc, 0, 0, 1), 0);
    ok_long(pulBits[0], 8);
    ok_long(SetPixel(hdc, 0, 0, RGB(255,255,255)), 0xc0dcc0);
    ok_long(pulBits[0], 7);

    ok_long(SetPixel(hdc, 0, 0, RGB(255,0,0)), 0x80);
    ok_long(pulBits[0], 0);

    /* Test DIBINDEX */
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(0)), 0x80);
    ok_long(pulBits[0], 0);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(1)), 0x8000);
    ok_long(pulBits[0], 1);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(7)), 0xc0dcc0);
    ok_long(pulBits[0], 7);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(8)), 0);
    ok_long(pulBits[0], 8);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(126)), 0);
    ok_long(pulBits[0], 126);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(0x123456)), 0);
    ok_long(pulBits[0], 0x56);

    /* Test PALETTEINDEX */
    ok_long(SetPixel(hdc, 0, 0, PALETTEINDEX(0)), 0);
    ok_long(pulBits[0], 8);
    ok_long(SetPixel(hdc, 0, 0, PALETTEINDEX(1)), 0x80);
    ok_long(pulBits[0], 0);
    ok_long(SetPixel(hdc, 0, 0, PALETTEINDEX(2)), 0x8000);
    ok_long(pulBits[0], 1);

    /* Delete the DIB section */
    DeleteObject(hbmp);


    /* Initialize the logical palette and select it */
    hpal = CreatePalette((LOGPALETTE*)&gpal);
    hpalOld = SelectPalette(hdc, hpal, FALSE);
    ok(hpalOld != NULL, "error=%ld\n", GetLastError());


    /* Create a DIB section and select it */
    hbmp = CreateDIBSection(hdc, pbmi, DIB_PAL_COLORS, (PVOID*)&pulBits, 0, 0 );
    ok(hbmp != NULL, "CreateDIBSection failed with error %ld\n", GetLastError());
    ok(SelectObject(hdc, hbmp) != 0, "SelectObject failed\n");

    ok_long(SetPixel(hdc, 0, 0, 0), 0);
    ok_long(pulBits[0], 8);

    ok_long(SetPixel(hdc, 0, 0, RGB(255,0,0)), 0x605040);
    ok_long(pulBits[0], 2);

    /* Test DIBINDEX */
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(0)), 0x403020);
    ok_long(pulBits[0], 0);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(1)), 0x504030);
    ok_long(pulBits[0], 1);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(7)), 0x302010);
    ok_long(pulBits[0], 7);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(8)), 0);
    ok_long(pulBits[0], 8);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(126)), 0);
    ok_long(pulBits[0], 126);
    ok_long(SetPixel(hdc, 0, 0, DIBINDEX(0x123456)), 0);
    ok_long(pulBits[0], 0x56);

    /* Test PALETTEINDEX */
    ok_long(SetPixel(hdc, 0, 0, PALETTEINDEX(0)), 0x302010);
    ok_long(pulBits[0], 7);
    ok_long(SetPixel(hdc, 0, 0, PALETTEINDEX(1)), 0x403020);
    ok_long(pulBits[0], 0);
    ok_long(SetPixel(hdc, 0, 0, PALETTEINDEX(253)), 0x302010);
    ok_long(pulBits[0], 7);
    ok_long(SetPixel(hdc, 0, 0, PALETTEINDEX(254)), 0x302010);
    ok_long(pulBits[0], 7);


}