#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bmi ;
typedef  int /*<<< orphan*/  bm ;
struct TYPE_9__ {int bmHeight; int /*<<< orphan*/  bmWidth; } ;
struct TYPE_7__ {int biSize; int biHeight; int biPlanes; int biBitCount; int /*<<< orphan*/  biCompression; int /*<<< orphan*/  biWidth; } ;
struct TYPE_8__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int DWORD ;
typedef  TYPE_2__ BITMAPINFO ;
typedef  TYPE_3__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int GetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int GetObjectA (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_match (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_LoadImageBitmap(const char * test_desc, HBITMAP hbm)
{
    BITMAP bm;
    BITMAPINFO bmi;
    DWORD ret, pixel = 0;
    HDC hdc = GetDC(NULL);

    ret = GetObjectA(hbm, sizeof(bm), &bm);
    ok(ret == sizeof(bm), "GetObject returned %d\n", ret);

    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = bm.bmWidth;
    bmi.bmiHeader.biHeight = bm.bmHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount= 24;
    bmi.bmiHeader.biCompression= BI_RGB;
    ret = GetDIBits(hdc, hbm, 0, bm.bmHeight, &pixel, &bmi, DIB_RGB_COLORS);
    ok(ret == bm.bmHeight, "%s: %d lines were converted, not %d\n", test_desc, ret, bm.bmHeight);

    ok(color_match(pixel, 0x00ffffff), "%s: Pixel is 0x%08x\n", test_desc, pixel);

    ReleaseDC(NULL, hdc);
}