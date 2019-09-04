#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {int biSize; int biHeight; int biWidth; int biBitCount; int biPlanes; int /*<<< orphan*/  biCompression; } ;
struct TYPE_5__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  scalar_t__ HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  AbortPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  BeginPath (int /*<<< orphan*/ ) ; 
 int CloseFigure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateDIBSection (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int ERROR_CAN_NOT_COMPLETE ; 
 int EndPath (int /*<<< orphan*/ ) ; 
 int FillPath (int /*<<< orphan*/ ) ; 
 int FlattenPath (int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int GetPath (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ PathToRegion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGN_OR ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  RestoreDC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SaveDC (int /*<<< orphan*/ ) ; 
 int SelectClipPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int StrokeAndFillPath (int /*<<< orphan*/ ) ; 
 int StrokePath (int /*<<< orphan*/ ) ; 
 int WidenPath (int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_path_state(void)
{
    BYTE buffer[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
    BITMAPINFO *bi = (BITMAPINFO *)buffer;
    HDC hdc;
    HRGN rgn;
    HBITMAP orig, dib;
    void *bits;
    BOOL ret;

    hdc = CreateCompatibleDC( 0 );
    memset( buffer, 0, sizeof(buffer) );
    bi->bmiHeader.biSize = sizeof(bi->bmiHeader);
    bi->bmiHeader.biHeight = 256;
    bi->bmiHeader.biWidth = 256;
    bi->bmiHeader.biBitCount = 32;
    bi->bmiHeader.biPlanes = 1;
    bi->bmiHeader.biCompression = BI_RGB;
    dib = CreateDIBSection( 0, bi, DIB_RGB_COLORS, (void**)&bits, NULL, 0 );
    orig = SelectObject( hdc, dib );

    BeginPath( hdc );
    LineTo( hdc, 100, 100 );
    ret = WidenPath( hdc );
    ok( !ret, "WidenPath succeeded\n" );

    /* selecting another bitmap doesn't affect the path */
    SelectObject( hdc, orig );
    ret = WidenPath( hdc );
    ok( !ret, "WidenPath succeeded\n" );

    SelectObject( hdc, dib );
    ret = WidenPath( hdc );
    ok( !ret, "WidenPath succeeded\n" );

    ret = EndPath( hdc );
    ok( ret, "EndPath failed error %u\n", GetLastError() );
    ret = WidenPath( hdc );
    ok( ret, "WidenPath failed error %u\n", GetLastError() );

    SelectObject( hdc, orig );
    ret = WidenPath( hdc );
    ok( ret, "WidenPath failed error %u\n", GetLastError() );

    BeginPath( hdc );
    LineTo( hdc, 100, 100 );
    ret = WidenPath( hdc );
    ok( !ret, "WidenPath succeeded\n" );
    SaveDC( hdc );
    SelectObject( hdc, dib );
    ret = EndPath( hdc );
    ok( ret, "EndPath failed error %u\n", GetLastError() );
    ret = WidenPath( hdc );
    ok( ret, "WidenPath failed error %u\n", GetLastError() );

    /* path should be open again after RestoreDC */
    RestoreDC( hdc, -1  );
    ret = WidenPath( hdc );
    ok( !ret, "WidenPath succeeded\n" );
    ret = EndPath( hdc );
    ok( ret, "EndPath failed error %u\n", GetLastError() );

    SaveDC( hdc );
    BeginPath( hdc );
    RestoreDC( hdc, -1  );
    ret = WidenPath( hdc );
    ok( ret, "WidenPath failed error %u\n", GetLastError() );

    /* test all functions with no path at all */
    AbortPath( hdc );
    SetLastError( 0xdeadbeef );
    ret = WidenPath( hdc );
    ok( !ret, "WidenPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = FlattenPath( hdc );
    ok( !ret, "FlattenPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = StrokePath( hdc );
    ok( !ret, "StrokePath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = FillPath( hdc );
    ok( !ret, "FillPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = StrokeAndFillPath( hdc );
    ok( !ret, "StrokeAndFillPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = SelectClipPath( hdc, RGN_OR );
    ok( !ret, "SelectClipPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    rgn = PathToRegion( hdc );
    ok( !rgn, "PathToRegion succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = EndPath( hdc );
    ok( !ret, "SelectClipPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = CloseFigure( hdc );
    ok( !ret, "CloseFigure succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    /* test all functions with an open path */
    AbortPath( hdc );
    BeginPath( hdc );
    SetLastError( 0xdeadbeef );
    ret = WidenPath( hdc );
    ok( !ret, "WidenPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    AbortPath( hdc );
    BeginPath( hdc );
    SetLastError( 0xdeadbeef );
    ret = FlattenPath( hdc );
    ok( !ret, "FlattenPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    AbortPath( hdc );
    BeginPath( hdc );
    SetLastError( 0xdeadbeef );
    ret = StrokePath( hdc );
    ok( !ret, "StrokePath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    AbortPath( hdc );
    BeginPath( hdc );
    SetLastError( 0xdeadbeef );
    ret = FillPath( hdc );
    ok( !ret, "FillPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    AbortPath( hdc );
    BeginPath( hdc );
    SetLastError( 0xdeadbeef );
    ret = StrokeAndFillPath( hdc );
    ok( !ret, "StrokeAndFillPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    AbortPath( hdc );
    BeginPath( hdc );
    Rectangle( hdc, 1, 1, 10, 10 );  /* region needs some contents */
    SetLastError( 0xdeadbeef );
    ret = SelectClipPath( hdc, RGN_OR );
    ok( !ret, "SelectClipPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    AbortPath( hdc );
    BeginPath( hdc );
    Rectangle( hdc, 1, 1, 10, 10 );  /* region needs some contents */
    SetLastError( 0xdeadbeef );
    rgn = PathToRegion( hdc );
    ok( !rgn, "PathToRegion succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    AbortPath( hdc );
    BeginPath( hdc );
    ret = CloseFigure( hdc );
    ok( ret, "CloseFigure failed\n" );

    /* test all functions with a closed path */
    AbortPath( hdc );
    BeginPath( hdc );
    EndPath( hdc );
    ret = WidenPath( hdc );
    ok( ret, "WidenPath failed\n" );
    ok( GetPath( hdc, NULL, NULL, 0 ) != -1, "path deleted\n" );

    AbortPath( hdc );
    BeginPath( hdc );
    EndPath( hdc );
    ret = FlattenPath( hdc );
    ok( ret, "FlattenPath failed\n" );
    ok( GetPath( hdc, NULL, NULL, 0 ) != -1, "path deleted\n" );

    AbortPath( hdc );
    BeginPath( hdc );
    EndPath( hdc );
    ret = StrokePath( hdc );
    ok( ret, "StrokePath failed\n" );
    ok( GetPath( hdc, NULL, NULL, 0 ) == -1, "path not deleted\n" );

    BeginPath( hdc );
    EndPath( hdc );
    ret = FillPath( hdc );
    ok( ret, "FillPath failed\n" );
    ok( GetPath( hdc, NULL, NULL, 0 ) == -1, "path not deleted\n" );

    BeginPath( hdc );
    EndPath( hdc );
    ret = StrokeAndFillPath( hdc );
    ok( ret, "StrokeAndFillPath failed\n" );
    ok( GetPath( hdc, NULL, NULL, 0 ) == -1, "path not deleted\n" );

    BeginPath( hdc );
    Rectangle( hdc, 1, 1, 10, 10 );  /* region needs some contents */
    EndPath( hdc );
    ret = SelectClipPath( hdc, RGN_OR );
    ok( ret, "SelectClipPath failed\n" );
    ok( GetPath( hdc, NULL, NULL, 0 ) == -1, "path not deleted\n" );

    BeginPath( hdc );
    EndPath( hdc );
    SetLastError( 0xdeadbeef );
    ret = SelectClipPath( hdc, RGN_OR );
    ok( !ret, "SelectClipPath succeeded on empty path\n" );
    ok( GetLastError() == 0xdeadbeef, "wrong error %u\n", GetLastError() );
    ok( GetPath( hdc, NULL, NULL, 0 ) == -1, "path not deleted\n" );

    BeginPath( hdc );
    Rectangle( hdc, 1, 1, 10, 10 );  /* region needs some contents */
    EndPath( hdc );
    rgn = PathToRegion( hdc );
    ok( rgn != 0, "PathToRegion failed\n" );
    DeleteObject( rgn );
    ok( GetPath( hdc, NULL, NULL, 0 ) == -1, "path not deleted\n" );

    BeginPath( hdc );
    EndPath( hdc );
    SetLastError( 0xdeadbeef );
    rgn = PathToRegion( hdc );
    ok( !rgn, "PathToRegion succeeded on empty path\n" );
    ok( GetLastError() == 0xdeadbeef, "wrong error %u\n", GetLastError() );
    DeleteObject( rgn );
    ok( GetPath( hdc, NULL, NULL, 0 ) == -1, "path not deleted\n" );

    BeginPath( hdc );
    EndPath( hdc );
    SetLastError( 0xdeadbeef );
    ret = CloseFigure( hdc );
    ok( !ret, "CloseFigure succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    AbortPath( hdc );
    BeginPath( hdc );
    EndPath( hdc );
    SetLastError( 0xdeadbeef );
    ret = EndPath( hdc );
    ok( !ret, "EndPath succeeded\n" );
    ok( GetLastError() == ERROR_CAN_NOT_COMPLETE || broken(GetLastError() == 0xdeadbeef),
        "wrong error %u\n", GetLastError() );

    DeleteDC( hdc );
    DeleteObject( dib );
}