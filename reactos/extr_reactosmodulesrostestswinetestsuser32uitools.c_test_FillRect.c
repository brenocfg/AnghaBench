#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bits ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBRUSH ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_BRUSH ; 
 int /*<<< orphan*/ * CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int GetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_FillRect(void)
{
    HDC hdc, hdcmem;
    DWORD bits[64];
    HBITMAP hbmp, oldhbmp;
    COLORREF col;
    HBRUSH old_brush;
    RECT r;

    /* fill bitmap data with white */
    memset(bits, 0xff, sizeof(bits));

    hdc = GetDC(0);
    ok( hdc != NULL, "CreateDC rets %p\n", hdc);
    /* create a memory dc */
    hdcmem = CreateCompatibleDC(hdc);
    ok(hdcmem != NULL, "CreateCompatibleDC rets %p\n", hdcmem);
    /* test monochrome bitmap: should always work */
    hbmp = CreateBitmap(32, 32, 1, 1, bits);
    ok(hbmp != NULL, "CreateBitmap returns %p\n", hbmp);
    oldhbmp = SelectObject(hdcmem, hbmp);
    ok(oldhbmp != NULL, "SelectObject returned NULL\n"); /* a memdc always has a bitmap selected */
    col = GetPixel(hdcmem, 0, 0);
    ok( col == 0xffffff, "GetPixel returned %08x, expected 0xffffff\n", col);

    /* select black brush */
    old_brush = SelectObject(hdcmem, GetStockObject(BLACK_BRUSH));
    SetRect(&r, 0, 0, 5, 5);
    FillRect(hdcmem, &r, 0);
    SelectObject(hdcmem, old_brush);
    /* bitmap filled with last selected brush */
    col = GetPixel(hdcmem, 0, 0);
    ok(col == 0, "GetPixel returned %08x, expected 0\n", col);

    SelectObject(hdcmem, oldhbmp);
    DeleteObject(hbmp);
    DeleteDC(hdcmem);
    ReleaseDC(0, hdc);
}