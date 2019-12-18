#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_2__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biXPelsPerMeter; int biYPelsPerMeter; int biClrUsed; int biClrImportant; scalar_t__ biSizeImage; int /*<<< orphan*/  biCompression; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int BYTE ;
typedef  TYPE_1__ BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_PAL_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdiPalSetColorTable ; 
 int /*<<< orphan*/  NtGdiDoPalette (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetDCBrushColor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetDCPenColor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 

void
Test_NtGdiDoPalette_SetDIBColorTable(void)
{
    HDC hdc;
    HBITMAP hbmp;
    BYTE *pjBits;

    struct
    {
        BITMAPINFOHEADER bmiHeader;
        ULONG bmiColors[10];
    } bmi;

    hdc = CreateCompatibleDC(0);
    ok(hdc != NULL, "hdc was NULL.\n");

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 10;
    bmi.bmiHeader.biHeight = 10;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 8;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 1;
    bmi.bmiHeader.biYPelsPerMeter = 1;
    bmi.bmiHeader.biClrUsed = 9;
    bmi.bmiHeader.biClrImportant = 9;
    bmi.bmiColors[0] = 0x000000;
    bmi.bmiColors[1] = 0x202020;
    bmi.bmiColors[2] = 0x404040;
    bmi.bmiColors[3] = 0x606060;
    bmi.bmiColors[4] = 0x808080;
    bmi.bmiColors[5] = 0xA0A0A0;
    bmi.bmiColors[6] = 0xC0C0C0;
    bmi.bmiColors[7] = 0xE0E0E0;
    bmi.bmiColors[8] = 0xffffff;
    hbmp = CreateDIBSection(hdc, (BITMAPINFO*)&bmi, DIB_PAL_COLORS, (PVOID*)&pjBits, NULL, 0);
    ok(hbmp != NULL, "hbmp was NULL.\n");
    ok(pjBits != NULL, "pjBits was NULL.\n");

    SelectObject(hdc, hbmp);

    pjBits[0] = 8;
    pjBits[1] = 1;
    pjBits[2] = 2;
    pjBits[3] = 3;

    bmi.bmiColors[8] = 0x000000;
    bmi.bmiColors[7] = 0x202020;
    bmi.bmiColors[6] = 0x404040;
    bmi.bmiColors[5] = 0x606060;
    bmi.bmiColors[4] = 0x808080;
    bmi.bmiColors[3] = 0xA0A0A0;
    bmi.bmiColors[2] = 0xC0C0C0;
    bmi.bmiColors[1] = 0xE0E0E0;
    bmi.bmiColors[0] = 0xffffff;
    ok_long(NtGdiDoPalette(hdc, 0, 9, &bmi.bmiColors, GdiPalSetColorTable, FALSE), 9);

    SetDCPenColor(hdc, 0xE0E0E0);
    SetDCBrushColor(hdc, 0x202020);
    Rectangle(hdc, 0, 0, 10, 10);

    DeleteDC(hdc);
    DeleteObject(hbmp);
}