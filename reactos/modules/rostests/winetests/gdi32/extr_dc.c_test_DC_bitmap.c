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
typedef  int /*<<< orphan*/  descr ;
struct TYPE_4__ {int nSize; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int DWORD ;
typedef  int COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 int CLR_INVALID ; 
 int /*<<< orphan*/ * CreateBitmap (int,int,int,int,int*) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int DescribePixelFormat (int /*<<< orphan*/ *,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int GetDeviceCaps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetPixel (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_DC_bitmap(void)
{
    PIXELFORMATDESCRIPTOR descr;
    HDC hdc, hdcmem;
    DWORD bits[64];
    HBITMAP hbmp, oldhbmp;
    COLORREF col;
    int i, bitspixel;
    int ret, ret2;

    /* fill bitmap data with b&w pattern */
    for( i = 0; i < 64; i++) bits[i] = i & 1 ? 0 : 0xffffff;

    hdc = GetDC(0);
    ok( hdc != NULL, "CreateDC rets %p\n", hdc);
    bitspixel = GetDeviceCaps( hdc, BITSPIXEL);
    /* create a memory dc */
    hdcmem = CreateCompatibleDC( hdc);
    ok( hdcmem != NULL, "CreateCompatibleDC rets %p\n", hdcmem);

    /* test DescribePixelFormat with descr == NULL */
    ret2 = DescribePixelFormat(hdcmem, 0, sizeof(descr), NULL);
    ok(ret2 > 0, "expected ret2 > 0, got %d\n", ret2);
    ret = DescribePixelFormat(hdcmem, 1, sizeof(descr), NULL);
    ok(ret == ret2, "expected ret == %d, got %d\n", ret2, ret);
    ret = DescribePixelFormat(hdcmem, 0x10000, sizeof(descr), NULL);
    ok(ret == ret2, "expected ret == %d, got %d\n", ret2, ret);

    /* test DescribePixelFormat with descr != NULL */
    memset(&descr, 0, sizeof(descr));
    ret = DescribePixelFormat(hdcmem, 0, sizeof(descr), &descr);
    ok(ret == 0, "expected ret == 0, got %d\n", ret);
    ok(descr.nSize == 0, "expected descr.nSize == 0, got %d\n", descr.nSize);

    memset(&descr, 0, sizeof(descr));
    ret = DescribePixelFormat(hdcmem, 1, sizeof(descr), &descr);
    ok(ret == ret2, "expected ret == %d, got %d\n", ret2, ret);
    ok(descr.nSize == sizeof(descr), "expected desc.nSize == sizeof(descr), got %d\n", descr.nSize);

    memset(&descr, 0, sizeof(descr));
    ret = DescribePixelFormat(hdcmem, 0x10000, sizeof(descr), &descr);
    ok(ret == 0, "expected ret == 0, got %d\n", ret);
    ok(descr.nSize == 0, "expected descr.nSize == 0, got %d\n", descr.nSize);

    /* test monochrome bitmap: should always work */
    hbmp = CreateBitmap(32, 32, 1, 1, bits);
    ok( hbmp != NULL, "CreateBitmap returns %p\n", hbmp);
    oldhbmp = SelectObject( hdcmem, hbmp);
    ok( oldhbmp != NULL, "SelectObject returned NULL\n" ); /* a memdc always has a bitmap selected */
    col = GetPixel( hdcmem, 0, 0);
    ok( col == 0xffffff, "GetPixel returned %08x, expected 00ffffff\n", col);
    col = GetPixel( hdcmem, 1, 1);
    ok( col == 0x000000, "GetPixel returned %08x, expected 00000000\n", col);
    col = GetPixel( hdcmem, 100, 1);
    ok( col == CLR_INVALID, "GetPixel returned %08x, expected ffffffff\n", col);
    SelectObject( hdcmem, oldhbmp);
    DeleteObject( hbmp);

    /* test with 2 bits color depth, not likely to succeed */
    hbmp = CreateBitmap(16, 16, 1, 2, bits);
    ok( hbmp != NULL, "CreateBitmap returns %p\n", hbmp);
    oldhbmp = SelectObject( hdcmem, hbmp);
    if( bitspixel != 2)
        ok( !oldhbmp, "SelectObject of a bitmap with 2 bits/pixel should return  NULL\n");
    if( oldhbmp) SelectObject( hdcmem, oldhbmp);
    DeleteObject( hbmp);

    /* test with 16 bits color depth, might succeed */
    hbmp = CreateBitmap(6, 6, 1, 16, bits);
    ok( hbmp != NULL, "CreateBitmap returns %p\n", hbmp);
    oldhbmp = SelectObject( hdcmem, hbmp);
    if( bitspixel == 16) {
        ok( oldhbmp != NULL, "SelectObject returned NULL\n" );
        col = GetPixel( hdcmem, 0, 0);
        ok( col == 0xffffff,
            "GetPixel of a bitmap with 16 bits/pixel returned %08x, expected 00ffffff\n", col);
        col = GetPixel( hdcmem, 1, 1);
        ok( col == 0x000000,
            "GetPixel of a bitmap with 16 bits/pixel returned returned %08x, expected 00000000\n", col);
    }
    if( oldhbmp) SelectObject( hdcmem, oldhbmp);
    DeleteObject( hbmp);

    /* test with 32 bits color depth, probably succeed */
    hbmp = CreateBitmap(4, 4, 1, 32, bits);
    ok( hbmp != NULL, "CreateBitmap returns %p\n", hbmp);
    oldhbmp = SelectObject( hdcmem, hbmp);
    if( bitspixel == 32) {
        ok( oldhbmp != NULL, "SelectObject returned NULL\n" );
        col = GetPixel( hdcmem, 0, 0);
        ok( col == 0xffffff,
            "GetPixel of a bitmap with 32 bits/pixel returned %08x, expected 00ffffff\n", col);
        col = GetPixel( hdcmem, 1, 1);
        ok( col == 0x000000,
            "GetPixel of a bitmap with 32 bits/pixel returned returned %08x, expected 00000000\n", col);
    }
    if( oldhbmp) SelectObject( hdcmem, oldhbmp);
    DeleteObject( hbmp);
    ReleaseDC( 0, hdc );
}