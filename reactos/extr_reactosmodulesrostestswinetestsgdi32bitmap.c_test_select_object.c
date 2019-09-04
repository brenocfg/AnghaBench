#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  depths ;
typedef  int /*<<< orphan*/  bm ;
struct TYPE_4__ {int bmType; int bmWidth; int bmHeight; int bmWidthBytes; int bmBitsPixel; int bmPlanes; int bmBits; } ;
typedef  int INT ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  int DWORD ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 scalar_t__ CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateCompatibleBitmap (scalar_t__,int,int) ; 
 scalar_t__ CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 scalar_t__ GetDC (int /*<<< orphan*/ ) ; 
 int GetDeviceCaps (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetObjectW (scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  PLANES ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SelectObject (scalar_t__,scalar_t__) ; 
 int get_bitmap_stride (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_select_object(void)
{
    HDC hdc;
    HBITMAP hbm, hbm_old;
    INT planes, bpp, i;
    DWORD depths[] = {8, 15, 16, 24, 32};
    BITMAP bm;
    DWORD bytes;

    hdc = GetDC(0);
    ok(hdc != 0, "GetDC(0) failed\n");
    hbm = CreateCompatibleBitmap(hdc, 10, 10);
    ok(hbm != 0, "CreateCompatibleBitmap failed\n");

    hbm_old = SelectObject(hdc, hbm);
    ok(hbm_old == 0, "SelectObject should fail\n");

    DeleteObject(hbm);
    ReleaseDC(0, hdc);

    hdc = CreateCompatibleDC(0);
    ok(hdc != 0, "GetDC(0) failed\n");
    hbm = CreateCompatibleBitmap(hdc, 10, 10);
    ok(hbm != 0, "CreateCompatibleBitmap failed\n");

    hbm_old = SelectObject(hdc, hbm);
    ok(hbm_old != 0, "SelectObject failed\n");
    hbm_old = SelectObject(hdc, hbm_old);
    ok(hbm_old == hbm, "SelectObject failed\n");

    DeleteObject(hbm);

    /* test an 1-bpp bitmap */
    planes = GetDeviceCaps(hdc, PLANES);
    bpp = 1;

    hbm = CreateBitmap(10, 10, planes, bpp, NULL);
    ok(hbm != 0, "CreateBitmap failed\n");

    hbm_old = SelectObject(hdc, hbm);
    ok(hbm_old != 0, "SelectObject failed\n");
    hbm_old = SelectObject(hdc, hbm_old);
    ok(hbm_old == hbm, "SelectObject failed\n");

    DeleteObject(hbm);

    for(i = 0; i < sizeof(depths)/sizeof(depths[0]); i++) {
        /* test a color bitmap to dc bpp matching */
        planes = GetDeviceCaps(hdc, PLANES);
        bpp = GetDeviceCaps(hdc, BITSPIXEL);

        hbm = CreateBitmap(10, 10, planes, depths[i], NULL);
        ok(hbm != 0, "CreateBitmap failed\n");

        hbm_old = SelectObject(hdc, hbm);
        if(depths[i] == bpp ||
          (bpp == 16 && depths[i] == 15)        /* 16 and 15 bpp are compatible */
          ) {
            ok(hbm_old != 0, "SelectObject failed, BITSPIXEL: %d, created depth: %d\n", bpp, depths[i]);
            SelectObject(hdc, hbm_old);
        } else {
            ok(hbm_old == 0, "SelectObject should fail. BITSPIXELS: %d, created depth: %d\n", bpp, depths[i]);
        }

        memset(&bm, 0xAA, sizeof(bm));
        bytes = GetObjectW(hbm, sizeof(bm), &bm);
        ok(bytes == sizeof(bm), "GetObject returned %d\n", bytes);
        ok(bm.bmType == 0, "wrong bmType %d\n", bm.bmType);
        ok(bm.bmWidth == 10, "wrong bmWidth %d\n", bm.bmWidth);
        ok(bm.bmHeight == 10, "wrong bmHeight %d\n", bm.bmHeight);
        ok(bm.bmWidthBytes == get_bitmap_stride(bm.bmWidth, bm.bmBitsPixel), "wrong bmWidthBytes %d\n", bm.bmWidthBytes);
        ok(bm.bmPlanes == planes, "wrong bmPlanes %u\n", bm.bmPlanes);
        if(depths[i] == 15) {
            ok(bm.bmBitsPixel == 16, "wrong bmBitsPixel %d(15 bpp special)\n", bm.bmBitsPixel);
        } else {
            ok(bm.bmBitsPixel == depths[i], "wrong bmBitsPixel %d\n", bm.bmBitsPixel);
        }
        ok(!bm.bmBits, "wrong bmBits %p\n", bm.bmBits);

        DeleteObject(hbm);
    }

    DeleteDC(hdc);
}