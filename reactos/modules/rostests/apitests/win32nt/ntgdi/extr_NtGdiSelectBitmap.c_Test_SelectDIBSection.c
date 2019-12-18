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
struct TYPE_2__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biXPelsPerMeter; int biYPelsPerMeter; int biClrUsed; int biClrImportant; scalar_t__ biSizeImage; int /*<<< orphan*/  biCompression; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PBITMAPINFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  TYPE_1__ BITMAPINFOHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateDIBSection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_PAL_COLORS ; 
 scalar_t__ NtGdiSelectBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST (int) ; 

void
Test_SelectDIBSection(void)
{
    HDC hdc;
    HBITMAP hbmp;
    struct
    {
        BITMAPINFOHEADER bmiHeader;
        RGBQUAD          bmiColors[100];
    } bmi;
    PBITMAPINFO pbmi = (PBITMAPINFO)&bmi;
    PVOID pvBits;

    hdc = CreateCompatibleDC(0);
    ASSERT(hdc);

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 2;
    bmi.bmiHeader.biHeight = 2;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 100;
    bmi.bmiHeader.biYPelsPerMeter = 100;
    bmi.bmiHeader.biClrUsed = 2;
    bmi.bmiHeader.biClrImportant = 2;

    hbmp = CreateDIBSection(hdc, pbmi, DIB_PAL_COLORS, &pvBits, NULL, 0);
    ASSERT(hbmp);

    TEST(NtGdiSelectBitmap(hdc, hbmp) != 0);

}