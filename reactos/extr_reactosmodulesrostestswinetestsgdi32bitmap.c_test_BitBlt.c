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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_6__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  BLACKNESS ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateDIBSection (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateSolidBrush (int) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DSTINVERT ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MERGECOPY ; 
 int /*<<< orphan*/  MERGEPAINT ; 
 int /*<<< orphan*/  NOTSRCCOPY ; 
 int /*<<< orphan*/  NOTSRCERASE ; 
 int /*<<< orphan*/  PATCOPY ; 
 int /*<<< orphan*/  PATINVERT ; 
 int /*<<< orphan*/  PATPAINT ; 
 int /*<<< orphan*/  SRCAND ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SRCERASE ; 
 int /*<<< orphan*/  SRCINVERT ; 
 int /*<<< orphan*/  SRCPAINT ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHITENESS ; 
 int /*<<< orphan*/  check_BitBlt_pixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_BitBlt(void)
{
    HBITMAP bmpDst, bmpSrc;
    HBITMAP oldDst, oldSrc;
    HDC hdcScreen, hdcDst, hdcSrc;
    UINT32 *dstBuffer, *srcBuffer;
    HBRUSH hBrush, hOldBrush;
    BITMAPINFO bitmapInfo;

    memset(&bitmapInfo, 0, sizeof(BITMAPINFO));
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = 1;
    bitmapInfo.bmiHeader.biHeight = 1;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    bitmapInfo.bmiHeader.biSizeImage = sizeof(UINT32);

    hdcScreen = CreateCompatibleDC(0);
    hdcDst = CreateCompatibleDC(hdcScreen);
    hdcSrc = CreateCompatibleDC(hdcDst);

    /* Setup the destination dib section */
    bmpDst = CreateDIBSection(hdcScreen, &bitmapInfo, DIB_RGB_COLORS, (void**)&dstBuffer,
        NULL, 0);
    oldDst = SelectObject(hdcDst, bmpDst);

    hBrush = CreateSolidBrush(0x12345678);
    hOldBrush = SelectObject(hdcDst, hBrush);

    /* Setup the source dib section */
    bmpSrc = CreateDIBSection(hdcScreen, &bitmapInfo, DIB_RGB_COLORS, (void**)&srcBuffer,
        NULL, 0);
    oldSrc = SelectObject(hdcSrc, bmpSrc);

    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, SRCCOPY, 0xFEDCBA98, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, SRCPAINT, 0xFFFFFFFF, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, SRCAND, 0x88888888, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, SRCINVERT, 0x77777777, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, SRCERASE, 0x76543210, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, NOTSRCCOPY, 0x01234567, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, NOTSRCERASE, 0x00000000, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, MERGECOPY, 0x00581210, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, MERGEPAINT, 0x89ABCDEF, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, PATCOPY, 0x00785634, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, PATPAINT, 0x89FBDFFF, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, PATINVERT, 0x89D39BDB, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, DSTINVERT, 0x76543210, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, BLACKNESS, 0x00000000, __LINE__);
    check_BitBlt_pixel(hdcDst, hdcSrc, dstBuffer, srcBuffer, WHITENESS, 0xFFFFFFFF, __LINE__);

    /* Tidy up */
    SelectObject(hdcSrc, oldSrc);
    DeleteObject(bmpSrc);
    DeleteDC(hdcSrc);

    SelectObject(hdcDst, hOldBrush);
    DeleteObject(hBrush);
    SelectObject(hdcDst, oldDst);
    DeleteObject(bmpDst);
    DeleteDC(hdcDst);


    DeleteDC(hdcScreen);
}