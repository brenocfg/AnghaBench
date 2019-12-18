#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int biSize; int biWidth; int biHeight; int biPlanes; int /*<<< orphan*/  biCompression; int /*<<< orphan*/  biBitCount; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {TYPE_2__ bmiHeader; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_clipping(void)
{
    HBITMAP bmpDst;
    HBITMAP bmpSrc;
    HRGN hRgn;
    LPVOID bits;
    BOOL result;

    HDC hdcDst = CreateCompatibleDC( NULL );
    HDC hdcSrc = CreateCompatibleDC( NULL );

    BITMAPINFO bmpinfo={{0}};
    bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpinfo.bmiHeader.biWidth = 100;
    bmpinfo.bmiHeader.biHeight = 100;
    bmpinfo.bmiHeader.biPlanes = 1;
    bmpinfo.bmiHeader.biBitCount = GetDeviceCaps( hdcDst, BITSPIXEL );
    bmpinfo.bmiHeader.biCompression = BI_RGB;

    bmpDst = CreateDIBSection( hdcDst, &bmpinfo, DIB_RGB_COLORS, &bits, NULL, 0 );
    ok(bmpDst != NULL, "Couldn't create destination bitmap\n");
    SelectObject( hdcDst, bmpDst );

    bmpSrc = CreateDIBSection( hdcSrc, &bmpinfo, DIB_RGB_COLORS, &bits, NULL, 0 );
    ok(bmpSrc != NULL, "Couldn't create source bitmap\n");
    SelectObject( hdcSrc, bmpSrc );

    result = BitBlt( hdcDst, 0, 0, 100, 100, hdcSrc, 100, 100, SRCCOPY );
    ok(result, "BitBlt failed\n");

    hRgn = CreateRectRgn( 0,0,0,0 );
    SelectClipRgn( hdcDst, hRgn );

    result = BitBlt( hdcDst, 0, 0, 100, 100, hdcSrc, 0, 0, SRCCOPY );
    ok(result, "BitBlt failed\n");

    DeleteObject( bmpDst );
    DeleteObject( bmpSrc );
    DeleteObject( hRgn );
    DeleteDC( hdcDst );
    DeleteDC( hdcSrc );
}