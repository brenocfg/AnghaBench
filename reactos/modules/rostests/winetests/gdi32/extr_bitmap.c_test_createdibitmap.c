#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bmih ;
typedef  int /*<<< orphan*/  bm ;
struct TYPE_9__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; scalar_t__ biSizeImage; void* biCompression; } ;
struct TYPE_10__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; TYPE_1__ bmiHeader; void* biCompression; } ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int DWORD ;
typedef  TYPE_2__ BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 void* BI_RGB ; 
 int /*<<< orphan*/  CBM_INIT ; 
 int /*<<< orphan*/ * CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateDIBitmap (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_bitmap_info (int /*<<< orphan*/ *,int,TYPE_2__*) ; 

__attribute__((used)) static void test_createdibitmap(void)
{
    HDC hdc, hdcmem;
    BITMAPINFOHEADER bmih;
    BITMAPINFO bm;
    HBITMAP hbm, hbm_colour, hbm_old;
    INT screen_depth;
    DWORD pixel;

    hdc = GetDC(0);
    screen_depth = GetDeviceCaps(hdc, BITSPIXEL);
    memset(&bmih, 0, sizeof(bmih));
    bmih.biSize = sizeof(bmih);
    bmih.biWidth = 10;
    bmih.biHeight = 10;
    bmih.biPlanes = 1;
    bmih.biBitCount = 32;
    bmih.biCompression = BI_RGB;

    hbm = CreateDIBitmap(hdc, NULL, CBM_INIT, NULL, NULL, 0);
    ok(hbm == NULL, "CreateDIBitmap should fail\n");
    hbm = CreateDIBitmap(hdc, NULL, 0, NULL, NULL, 0);
    ok(hbm == NULL, "CreateDIBitmap should fail\n");

    /* First create an un-initialised bitmap.  The depth of the bitmap
       should match that of the hdc and not that supplied in bmih.
    */

    /* First try 32 bits */
    hbm = CreateDIBitmap(hdc, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, screen_depth, &bmih);
    DeleteObject(hbm);
    
    /* Then 16 */
    bmih.biBitCount = 16;
    hbm = CreateDIBitmap(hdc, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, screen_depth, &bmih);
    DeleteObject(hbm);

    /* Then 1 */
    bmih.biBitCount = 1;
    hbm = CreateDIBitmap(hdc, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, screen_depth, &bmih);
    DeleteObject(hbm);

    /* Now with a monochrome dc we expect a monochrome bitmap */
    hdcmem = CreateCompatibleDC(hdc);

    /* First try 32 bits */
    bmih.biBitCount = 32;
    hbm = CreateDIBitmap(hdcmem, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, 1, &bmih);
    DeleteObject(hbm);
    
    /* Then 16 */
    bmih.biBitCount = 16;
    hbm = CreateDIBitmap(hdcmem, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, 1, &bmih);
    DeleteObject(hbm);
    
    /* Then 1 */
    bmih.biBitCount = 1;
    hbm = CreateDIBitmap(hdcmem, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, 1, &bmih);
    DeleteObject(hbm);

    /* Now select a polychrome bitmap into the dc and we expect
       screen_depth bitmaps again */
    hbm_colour = CreateCompatibleBitmap(hdc, bmih.biWidth, bmih.biHeight);
    test_bitmap_info(hbm_colour, screen_depth, &bmih);
    hbm_old = SelectObject(hdcmem, hbm_colour);

    /* First try 32 bits */
    bmih.biBitCount = 32;
    hbm = CreateDIBitmap(hdcmem, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, screen_depth, &bmih);
    DeleteObject(hbm);
    
    /* Then 16 */
    bmih.biBitCount = 16;
    hbm = CreateDIBitmap(hdcmem, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, screen_depth, &bmih);
    DeleteObject(hbm);
    
    /* Then 1 */
    bmih.biBitCount = 1;
    hbm = CreateDIBitmap(hdcmem, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, screen_depth, &bmih);
    DeleteObject(hbm);

    SelectObject(hdcmem, hbm_old);
    DeleteObject(hbm_colour);
    DeleteDC(hdcmem);

    bmih.biBitCount = 32;
    hbm = CreateDIBitmap(0, &bmih, 0, NULL, NULL, 0);
    ok(hbm != NULL, "CreateDIBitmap failed\n");
    test_bitmap_info(hbm, 1, &bmih);
    DeleteObject(hbm);

    /* Test how formats are converted */
    pixel = 0xffffffff;
    bmih.biBitCount = 1;
    bmih.biWidth = 1;
    bmih.biHeight = 1;

    memset(&bm, 0, sizeof(bm));
    bm.bmiHeader.biSize = sizeof(bm.bmiHeader);
    bm.bmiHeader.biWidth = 1;
    bm.bmiHeader.biHeight = 1;
    bm.bmiHeader.biPlanes = 1;
    bm.bmiHeader.biBitCount= 24;
    bm.bmiHeader.biCompression= BI_RGB;
    bm.bmiHeader.biSizeImage = 0;
    hbm = CreateDIBitmap(hdc, &bmih, CBM_INIT, &pixel, &bm, DIB_RGB_COLORS);
    ok(hbm != NULL, "CreateDIBitmap failed\n");

    pixel = 0xdeadbeef;
    bm.bmiHeader.biBitCount= 32;
    GetDIBits(hdc, hbm, 0, 1, &pixel, &bm, DIB_RGB_COLORS);
    ok(pixel == 0x00ffffff, "Reading a 32 bit pixel from a DDB returned %08x\n", pixel);
    DeleteObject(hbm);

    ReleaseDC(0, hdc);
}