#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ajBuffer ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int biSize; int biWidth; int biBitCount; int biHeight; int biPlanes; int biCompression; int biSizeImage; int biXPelsPerMeter; int biYPelsPerMeter; int biClrUsed; int biClrImportant; } ;
struct TYPE_6__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  TYPE_2__* PBITMAPINFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;

/* Variables and functions */
 int BI_BITFIELDS ; 
 int BI_RGB ; 
 int /*<<< orphan*/  CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ok_int (int,int) ; 

void
Test_GetDIBits_xBpp(
    ULONG cBitsPixel)
{
    UCHAR ajBuffer[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
    PBITMAPINFO pbmi = (PBITMAPINFO)ajBuffer;
    HBITMAP hbmp;
    ULONG cjSizeImage, cColors;
    HDC hdc;

    hdc = GetDC(0);
    hbmp = CreateBitmap(3, 3, 1, cBitsPixel, NULL);

    /* Fill in the size field */
    ZeroMemory(pbmi, sizeof(ajBuffer));
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    /* Get info */
    ok_int(GetDIBits(hdc, hbmp, 0, 0, NULL, pbmi, DIB_RGB_COLORS), 1);
    cjSizeImage = (((pbmi->bmiHeader.biWidth * pbmi->bmiHeader.biBitCount) + 31) & ~31) * pbmi->bmiHeader.biHeight / 8;
    cColors = cBitsPixel <= 8 ? 1 << pbmi->bmiHeader.biBitCount : 0;

    ok_int(pbmi->bmiHeader.biSize, sizeof(BITMAPINFOHEADER));
    ok_int(pbmi->bmiHeader.biWidth, 3);
    ok_int(pbmi->bmiHeader.biHeight, 3);
    ok_int(pbmi->bmiHeader.biPlanes, 1);
    ok_int(pbmi->bmiHeader.biBitCount, cBitsPixel);
    ok_int(pbmi->bmiHeader.biCompression, (cBitsPixel == 16) || (cBitsPixel == 32) ? BI_BITFIELDS : BI_RGB);
    ok_int(pbmi->bmiHeader.biSizeImage, cjSizeImage);
    ok_int(pbmi->bmiHeader.biXPelsPerMeter, 0);
    ok_int(pbmi->bmiHeader.biYPelsPerMeter, 0);
    ok_int(pbmi->bmiHeader.biClrUsed, cColors);
    ok_int(pbmi->bmiHeader.biClrImportant, cColors);

//    pbmi->bmiHeader.biSizeImage = 0;
   //ok_int(GetDIBits(NULL, hbmp, 0, 0, NULL, pbmi, DIB_RGB_COLORS), 1);

    /* Test a bitmap with values partly set */
    ZeroMemory(pbmi, sizeof(ajBuffer));
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biWidth = 12;
    pbmi->bmiHeader.biHeight = 14;
    pbmi->bmiHeader.biPlanes = 2;
    pbmi->bmiHeader.biBitCount = 0; // keep biBitCount == 0!
    pbmi->bmiHeader.biCompression = 7;
    pbmi->bmiHeader.biSizeImage = 123;
    ok_int(GetDIBits(hdc, hbmp, 0, 5, NULL, pbmi, DIB_RGB_COLORS), 1);
    ok_int(pbmi->bmiHeader.biWidth, 3);
    ok_int(pbmi->bmiHeader.biHeight, 3);
    ok_int(pbmi->bmiHeader.biPlanes, 1);
    ok_int(pbmi->bmiHeader.biBitCount, cBitsPixel);
    ok_int(pbmi->bmiHeader.biSizeImage, cjSizeImage);
    ok_int(pbmi->bmiHeader.biXPelsPerMeter, 0);
    ok_int(pbmi->bmiHeader.biYPelsPerMeter, 0);
    ok_int(pbmi->bmiHeader.biClrUsed, cColors);
    ok_int(pbmi->bmiHeader.biClrImportant, cColors);


#if 0
    /* Get info including the color table */
    ZeroMemory(pbmi, sizeof(ajBuffer));
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biBitCount = 1;
    ok_int(GetDIBits(NULL, hbmp, 0, 0, NULL, pbmi, DIB_PAL_COLORS), 1);

    /* Check a different bit depth */
    pbmi->bmiHeader.biBitCount, cBitsPixel = (cBitsPixel == 1) ? 8 : 1;
    ok_int(GetDIBits(hdc, hbmp, 0, 0, NULL, pbmi, DIB_RGB_COLORS), 1);
    ok_int(pbmi->bmiHeader.biBitCount, (cBitsPixel == 1) ? 8 : 1);

    /* Get the bits */
    SetLastError(0);
    ok_int(GetDIBits(hdc, hbmp, 0, 4, pvBits, pbmi, DIB_PAL_COLORS), 3);
    ok_int(GetDIBits(hdc, hbmp, 3, 7, pvBits, pbmi, DIB_RGB_COLORS), 1);
    ok_err(0);

    pbmi->bmiHeader.biPlanes = 2;
    pbmi->bmiHeader.biClrUsed = 0;
    ok_int(GetDIBits(hdc, hbmp, 0, 4, pvBits, pbmi, DIB_RGB_COLORS), 3);
#endif

    DeleteObject(hbmp);
    ReleaseDC(NULL, hdc);
}