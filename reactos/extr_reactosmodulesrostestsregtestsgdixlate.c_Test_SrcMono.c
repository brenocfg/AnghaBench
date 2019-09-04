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
typedef  int WORD ;
typedef  int ULONG ;
struct TYPE_2__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biXPelsPerMeter; int biYPelsPerMeter; int biClrUsed; int biClrImportant; void* biCompression; scalar_t__ biSizeImage; } ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  LPBITMAPINFO ;
typedef  scalar_t__ HBITMAP ;
typedef  TYPE_1__ BITMAPINFOHEADER ;

/* Variables and functions */
 void* BI_BITFIELDS ; 
 void* BI_RGB ; 
 int /*<<< orphan*/  BMF_16BPP_555 ; 
 int /*<<< orphan*/  BMF_16BPP_565 ; 
 int /*<<< orphan*/  BMF_1BPP ; 
 int /*<<< orphan*/  BMF_32BPP_BGR ; 
 scalar_t__ CreateDIBSection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int GetPixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetPixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Test_SrcMono1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ hbmp1bpp_a ; 
 scalar_t__ hbmp1bpp_b ; 
 scalar_t__ hbmpCompat ; 
 int /*<<< orphan*/  hdcDst ; 
 int /*<<< orphan*/  hdcSrc ; 
 int /*<<< orphan*/  iDcFormat ; 
 int iXlateFromRGB (int /*<<< orphan*/ ,int) ; 
 int iXlateToRGB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void
Test_SrcMono()
{
    HBITMAP hbmp;
    struct
    {
        BITMAPINFOHEADER bmiHeader;
        ULONG bmiColors[3];
    } bmi;
    PVOID pvBits;
    ULONG c, expected;

    SelectObject(hdcSrc, hbmp1bpp_a);

    Test_SrcMono1(BMF_1BPP, hbmp1bpp_b, 0);
    Test_SrcMono1(iDcFormat, hbmpCompat, 0);

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 2;
    bmi.bmiHeader.biHeight = -2;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 16;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 1;
    bmi.bmiHeader.biYPelsPerMeter = 1;
    bmi.bmiHeader.biClrUsed = 0;
    bmi.bmiHeader.biClrImportant = 0;
    hbmp = CreateDIBSection(hdcDst, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);
    ok(hbmp != 0, "CreateDIBSection failed\n");
    memset(pvBits, 0x55555555, 8 * 8 * 2);

    SelectObject(hdcDst, hbmp);

    c = GetPixel(hdcDst, 0, 0);
    expected = iXlateToRGB(BMF_16BPP_555, 0x5555);
    ok(c == expected, "expected %lx, got %lx\n", expected, c);

    expected = 0x123456;
    SetPixel(hdcDst, 0, 0, expected);
    expected = iXlateFromRGB(BMF_16BPP_555, expected);
    c = *(volatile WORD*)pvBits;
    ok(c == expected, "expected %lx, got %lx\n", expected, c);

    Test_SrcMono1(BMF_16BPP_555, hbmp, pvBits);
 
    DeleteObject(hbmp);

    /* Create a 565 DIB section */
    bmi.bmiHeader.biCompression = BI_BITFIELDS;
    bmi.bmiHeader.biClrUsed = 3;
    bmi.bmiHeader.biClrImportant = 3;
    bmi.bmiColors[0] = 0xF800;
    bmi.bmiColors[1] = 0x7E0;
    bmi.bmiColors[2] = 0x1F;
    hbmp = CreateDIBSection(hdcDst, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);
    ok(hbmp != 0, "CreateDIBSection failed\n");
    SelectObject(hdcDst, hbmp);

    Test_SrcMono1(BMF_16BPP_565, hbmp, pvBits);

    DeleteObject(hbmp);

    /* Create a 32 bpp DIB section */
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biClrUsed = 0;
    bmi.bmiHeader.biClrImportant = 0;
    hbmp = CreateDIBSection(hdcDst, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);
    ok(hbmp != 0, "CreateDIBSection failed\n");
    SelectObject(hdcDst, hbmp);

    Test_SrcMono1(BMF_32BPP_BGR, hbmp, pvBits);

    DeleteObject(hbmp);

}