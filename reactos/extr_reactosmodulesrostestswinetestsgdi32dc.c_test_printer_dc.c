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
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 int BitBlt (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CLR_INVALID ; 
 int /*<<< orphan*/  CloseEnhMetaFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateEnhMetaFileA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DT_RASDISPLAY ; 
 scalar_t__ DT_RASPRINTER ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetDeviceCaps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TECHNOLOGY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * create_printer_dc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_postscript_printer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_device_caps (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void test_printer_dc(void)
{
    HDC memdc, display_memdc, enhmf_dc;
    HBITMAP orig, bmp;
    DWORD ret;
    HDC hdc, hdc_200;

    hdc = create_printer_dc(100, FALSE);
    hdc_200 = create_printer_dc(200, FALSE);

    if (!hdc || !hdc_200) return;

    test_device_caps( hdc, hdc_200, "printer dc", is_postscript_printer(hdc) ? 2 : 1 );
    DeleteDC( hdc_200 );

    hdc_200 = create_printer_dc(200, TRUE);
    test_device_caps( hdc, hdc_200, "printer dc", is_postscript_printer(hdc) ? 2 : 1 );
    DeleteDC( hdc_200 );

    memdc = CreateCompatibleDC( hdc );
    display_memdc = CreateCompatibleDC( 0 );

    ok( memdc != NULL, "CreateCompatibleDC failed for printer\n" );
    ok( display_memdc != NULL, "CreateCompatibleDC failed for screen\n" );

    ret = GetDeviceCaps( hdc, TECHNOLOGY );
    ok( ret == DT_RASPRINTER, "wrong type %u\n", ret );

    ret = GetDeviceCaps( memdc, TECHNOLOGY );
    ok( ret == DT_RASPRINTER, "wrong type %u\n", ret );

    ret = GetDeviceCaps( display_memdc, TECHNOLOGY );
    ok( ret == DT_RASDISPLAY, "wrong type %u\n", ret );

    bmp = CreateBitmap( 100, 100, 1, GetDeviceCaps( hdc, BITSPIXEL ), NULL );
    orig = SelectObject( memdc, bmp );
    ok( orig != NULL, "SelectObject failed\n" );
    ok( BitBlt( hdc, 10, 10, 20, 20, memdc, 0, 0, SRCCOPY ), "BitBlt failed\n" );

    test_device_caps( memdc, hdc, "printer dc", 1 );

    ok( !SelectObject( display_memdc, bmp ), "SelectObject succeeded\n" );
    SelectObject( memdc, orig );
    DeleteObject( bmp );

    bmp = CreateBitmap( 100, 100, 1, 1, NULL );
    orig = SelectObject( display_memdc, bmp );
    ok( orig != NULL, "SelectObject failed\n" );
    ok( !SelectObject( memdc, bmp ), "SelectObject succeeded\n" );
    ok( BitBlt( hdc, 10, 10, 20, 20, display_memdc, 0, 0, SRCCOPY ), "BitBlt failed\n" );
    ok( BitBlt( memdc, 10, 10, 20, 20, display_memdc, 0, 0, SRCCOPY ), "BitBlt failed\n" );
    ok( BitBlt( display_memdc, 10, 10, 20, 20, memdc, 0, 0, SRCCOPY ), "BitBlt failed\n" );

    ret = GetPixel( hdc, 0, 0 );
    ok( ret == CLR_INVALID, "wrong pixel value %x\n", ret );

    enhmf_dc = CreateEnhMetaFileA( hdc, NULL, NULL, NULL );
    ok(enhmf_dc != 0, "CreateEnhMetaFileA failed\n");
    test_device_caps( enhmf_dc, hdc, "enhmetafile printer dc", 1 );
    DeleteEnhMetaFile( CloseEnhMetaFile( enhmf_dc ));

    enhmf_dc = CreateEnhMetaFileA( hdc, NULL, NULL, NULL );
    ok(enhmf_dc != 0, "CreateEnhMetaFileA failed\n");
    test_device_caps( enhmf_dc, hdc, "enhmetafile printer dc", 1 );
    DeleteEnhMetaFile( CloseEnhMetaFile( enhmf_dc ));

    DeleteDC( memdc );
    DeleteDC( display_memdc );
    DeleteDC( hdc );
    DeleteObject( bmp );
}