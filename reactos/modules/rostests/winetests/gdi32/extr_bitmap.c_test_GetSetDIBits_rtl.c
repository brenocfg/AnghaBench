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
typedef  int /*<<< orphan*/  bits_1 ;
struct TYPE_5__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int /*<<< orphan*/  biCompression; } ;
struct TYPE_6__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int GetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAYOUT_LTR ; 
 int /*<<< orphan*/  LAYOUT_RTL ; 
 int /*<<< orphan*/  RGB (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pSetLayout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetSetDIBits_rtl(void)
{
    HDC hdc, hdc_mem;
    HBITMAP bitmap, orig_bitmap;
    BITMAPINFO info;
    int ret;
    DWORD bits_1[8 * 8], bits_2[8 * 8];

    if(!pSetLayout)
    {
        win_skip("Don't have SetLayout\n");
        return;
    }

    hdc = GetDC( NULL );
    hdc_mem = CreateCompatibleDC( hdc );
    pSetLayout( hdc_mem, LAYOUT_LTR );

    bitmap = CreateCompatibleBitmap( hdc, 8, 8 );
    orig_bitmap = SelectObject( hdc_mem, bitmap );
    SetPixel( hdc_mem, 0, 0, RGB(0xff, 0, 0) );
    SelectObject( hdc_mem, orig_bitmap );

    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth = 8;
    info.bmiHeader.biHeight = 8;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;

    /* First show that GetDIBits ignores the layout mode. */

    ret = GetDIBits( hdc_mem, bitmap, 0, 8, bits_1, &info, DIB_RGB_COLORS );
    ok(ret == 8, "got %d\n", ret);
    ok(bits_1[56] == 0xff0000, "got %08x\n", bits_1[56]); /* check we have a red pixel */

    pSetLayout( hdc_mem, LAYOUT_RTL );

    ret = GetDIBits( hdc_mem, bitmap, 0, 8, bits_2, &info, DIB_RGB_COLORS );
    ok(ret == 8, "got %d\n", ret);

    ok(!memcmp( bits_1, bits_2, sizeof(bits_1) ), "bits differ\n");

    /* Now to show that SetDIBits also ignores the mode, we perform a SetDIBits
       followed by a GetDIBits and show that the bits remain unchanged. */

    pSetLayout( hdc_mem, LAYOUT_LTR );

    ret = SetDIBits( hdc_mem, bitmap, 0, 8, bits_1, &info, DIB_RGB_COLORS );
    ok(ret == 8, "got %d\n", ret);
    ret = GetDIBits( hdc_mem, bitmap, 0, 8, bits_2, &info, DIB_RGB_COLORS );
    ok(ret == 8, "got %d\n", ret);
    ok(!memcmp( bits_1, bits_2, sizeof(bits_1) ), "bits differ\n");

    pSetLayout( hdc_mem, LAYOUT_RTL );

    ret = SetDIBits( hdc_mem, bitmap, 0, 8, bits_1, &info, DIB_RGB_COLORS );
    ok(ret == 8, "got %d\n", ret);
    ret = GetDIBits( hdc_mem, bitmap, 0, 8, bits_2, &info, DIB_RGB_COLORS );
    ok(ret == 8, "got %d\n", ret);
    ok(!memcmp( bits_1, bits_2, sizeof(bits_1) ), "bits differ\n");

    DeleteObject( bitmap );
    DeleteDC( hdc_mem );
    ReleaseDC( NULL, hdc );
}