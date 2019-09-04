#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  header ;
struct TYPE_14__ {int biSize; int /*<<< orphan*/  biHeight; scalar_t__ biSizeImage; } ;
struct TYPE_12__ {int /*<<< orphan*/  hGlobal; } ;
struct TYPE_13__ {int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; TYPE_1__ u; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int DWORD ;
typedef  TYPE_3__ BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 int /*<<< orphan*/  abs (int /*<<< orphan*/ ) ; 
 int bitmap_info_size (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT synthesize_dib( HBITMAP bm, STGMEDIUM *med )
{
    HDC hdc = GetDC( 0 );
    BITMAPINFOHEADER header;
    BITMAPINFO *bmi;
    HRESULT hr = E_FAIL;
    DWORD header_size;

    memset( &header, 0, sizeof(header) );
    header.biSize = sizeof(header);
    if (!GetDIBits( hdc, bm, 0, 0, NULL, (BITMAPINFO *)&header, DIB_RGB_COLORS )) goto done;

    header_size = bitmap_info_size( (BITMAPINFO *)&header, DIB_RGB_COLORS );
    if (!(med->u.hGlobal = GlobalAlloc( GMEM_MOVEABLE, header_size + header.biSizeImage ))) goto done;
    bmi = GlobalLock( med->u.hGlobal );
    memset( bmi, 0, header_size );
    memcpy( bmi, &header, header.biSize );
    GetDIBits( hdc, bm, 0, abs(header.biHeight), (char *)bmi + header_size, bmi, DIB_RGB_COLORS );
    GlobalUnlock( med->u.hGlobal );
    med->tymed = TYMED_HGLOBAL;
    med->pUnkForRelease = NULL;
    hr = S_OK;

done:
    ReleaseDC( 0, hdc );
    return hr;
}