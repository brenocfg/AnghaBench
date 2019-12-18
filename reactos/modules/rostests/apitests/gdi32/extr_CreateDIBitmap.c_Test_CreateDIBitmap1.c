#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bitmap ;
typedef  int ULONG ;
struct TYPE_8__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biSizeImage; int biXPelsPerMeter; int biYPelsPerMeter; int biClrUsed; int /*<<< orphan*/  biCompression; scalar_t__ biClrImportant; } ;
struct TYPE_7__ {scalar_t__ bmType; int bmWidth; int bmHeight; int bmWidthBytes; int bmPlanes; scalar_t__ bmBitsPixel; scalar_t__ bmBits; } ;
struct TYPE_6__ {TYPE_4__ bmiHeader; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_1__ BITMAPINFO ;
typedef  TYPE_2__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  BI_RLE8 ; 
 int /*<<< orphan*/  CBM_INIT ; 
 scalar_t__ CreateDIBitmap (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_PAL_COLORS ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetObject (scalar_t__,int,TYPE_2__*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void
Test_CreateDIBitmap1(void)
{
    BITMAPINFO bmi;
    HBITMAP hbmp;
    BITMAP bitmap;
    ULONG bits[128] = {0};
    BYTE rlebits[] = {2, 0, 0, 0, 2, 1, 0, 1};
    HDC hdc;
    int ret;

    hdc = GetDC(0);

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 2;
    bmi.bmiHeader.biHeight = 2;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 16;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 1;
    bmi.bmiHeader.biYPelsPerMeter = 1;
    bmi.bmiHeader.biClrUsed = 0;
    bmi.bmiHeader.biClrImportant = 0;

    hbmp = CreateDIBitmap(hdc, &bmi.bmiHeader, CBM_INIT, bits, &bmi, DIB_RGB_COLORS);
    ok(hbmp != 0, "failed\n");

    ret = GetObject(hbmp, sizeof(bitmap), &bitmap);
    ok(ret != 0, "failed\n");
    ok(bitmap.bmType == 0, "\n");
    ok(bitmap.bmWidth == 2, "\n");
    ok(bitmap.bmHeight == 2, "\n");
    ok(bitmap.bmWidthBytes == 8, "bmWidthBytes = %ld\n", bitmap.bmWidthBytes);
    ok(bitmap.bmPlanes == 1, "\n");
    ok(bitmap.bmBitsPixel == GetDeviceCaps(hdc, BITSPIXEL), "\n");
    ok(bitmap.bmBits == 0, "\n");

    SetLastError(0);
    bmi.bmiHeader.biCompression = BI_RLE8;
    bmi.bmiHeader.biBitCount = 8;
    bmi.bmiHeader.biSizeImage = 8;
    bmi.bmiHeader.biClrUsed = 1;
    hbmp = CreateDIBitmap(hdc, &bmi.bmiHeader, CBM_INIT, rlebits, &bmi, DIB_PAL_COLORS);
    ok(hbmp != 0, "failed\n");
    ok(GetLastError() == 0, "GetLastError() == %ld\n", GetLastError());

    ret = GetObject(hbmp, sizeof(bitmap), &bitmap);
    ok(ret != 0, "failed\n");
    ok(bitmap.bmType == 0, "\n");
    ok(bitmap.bmWidth == 2, "\n");
    ok(bitmap.bmHeight == 2, "\n");
    ok(bitmap.bmWidthBytes == 8, "bmWidthBytes = %ld\n", bitmap.bmWidthBytes);
    ok(bitmap.bmPlanes == 1, "\n");
    ok(bitmap.bmBitsPixel == GetDeviceCaps(hdc, BITSPIXEL), "\n");
    ok(bitmap.bmBits == 0, "\n");


}