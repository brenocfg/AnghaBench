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
typedef  int /*<<< orphan*/  bitmapInfo ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {int biSize; int biWidth; int biHeight; int biBitCount; int biPlanes; int biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_6__ {TYPE_1__ bmiHeader; } ;
typedef  scalar_t__ HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 int /*<<< orphan*/  BI_RGB ; 
 scalar_t__ CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateDIBSection (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DSS_NORMAL ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetDeviceCaps (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SelectObject (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_DrawState_Color (scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  check_DrawState_Size (scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_DrawState(void)
{
    BITMAPINFO bitmapInfo;
    HDC hdcDst = NULL;
    HBITMAP bmpDst = NULL;
    HBITMAP bmpOld = NULL;
    void *bits = 0;

    hdcDst = CreateCompatibleDC(0);
    ok(hdcDst != 0, "CreateCompatibleDC(0) failed to return a valid DC\n");
    if (!hdcDst)
        return;

    if(GetDeviceCaps(hdcDst, BITSPIXEL) <= 8)
    {
        skip("Windows will distort DrawIconEx colors at 8-bpp and less due to palettizing.\n");
        goto cleanup;
    }

    memset(&bitmapInfo, 0, sizeof(bitmapInfo));
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = 3;
    bitmapInfo.bmiHeader.biHeight = 3;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    bitmapInfo.bmiHeader.biSizeImage = sizeof(UINT32);
    bmpDst = CreateDIBSection(hdcDst, &bitmapInfo, DIB_RGB_COLORS, &bits, NULL, 0);
    ok (bmpDst && bits, "CreateDIBSection failed to return a valid bitmap and buffer\n");
    if (!bmpDst || !bits)
        goto cleanup;
    bmpOld = SelectObject(hdcDst, bmpDst);

    /* potential flags to test with DrawState are: */
    /* DSS_DISABLED embosses the icon */
    /* DSS_MONO draw Icon using a brush as parameter 5 */
    /* DSS_NORMAL draw Icon without any modifications */
    /* DSS_UNION draw the Icon dithered */

    check_DrawState_Size(hdcDst, FALSE, 0x00A0B0C0, 32, 0, DSS_NORMAL, __LINE__);
    check_DrawState_Color(hdcDst, FALSE, 0x00A0B0C0, 32, 0, DSS_NORMAL, 0x00FFFFFF, 0x00C0B0A0, 0x00C0B0A0, __LINE__);

cleanup:
    if(bmpOld)
        SelectObject(hdcDst, bmpOld);
    if(bmpDst)
        DeleteObject(bmpDst);
    if(hdcDst)
        DeleteDC(hdcDst);
}