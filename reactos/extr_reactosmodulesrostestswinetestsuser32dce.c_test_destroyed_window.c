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
typedef  int HDC ;

/* Variables and functions */
 int DCX_CACHE ; 
 int DCX_USESTYLE ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int GetDC (scalar_t__) ; 
 int GetDCEx (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int GetROP2 (int) ; 
 int R2_WHITE ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int) ; 
 int /*<<< orphan*/  SetROP2 (int,int) ; 
 scalar_t__ WindowFromDC (int) ; 
 scalar_t__ hwnd_cache ; 
 scalar_t__ hwnd_classdc ; 
 scalar_t__ hwnd_classdc2 ; 
 scalar_t__ hwnd_owndc ; 
 scalar_t__ hwnd_parent ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_destroyed_window(void)
{
    HDC dc, old_dc;
    HDC hdcs[30];
    int i, rop;

    dc = GetDC( hwnd_cache );
    SetROP2( dc, R2_WHITE );
    rop = GetROP2( dc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );
    ok( WindowFromDC( dc ) == hwnd_cache, "wrong window\n" );
    old_dc = dc;

    DestroyWindow( hwnd_cache );
    rop = GetROP2( dc );
    ok( rop == 0, "wrong ROP2 %d\n", rop );
    ok( WindowFromDC( dc ) == 0, "wrong window\n" );
    ok( !ReleaseDC( hwnd_cache, dc ), "ReleaseDC succeeded\n" );
    dc = GetDC( hwnd_cache );
    ok( !dc, "Got a non-NULL DC (%p) for a destroyed window\n", dc );

    for (i = 0; i < 30; i++)
    {
        dc = hdcs[i] = GetDCEx( hwnd_parent, 0, DCX_CACHE | DCX_USESTYLE );
        if (dc == old_dc) break;
    }
    ok( i < 30, "DC for destroyed window not reused\n" );
    while (i > 0) ReleaseDC( hwnd_parent, hdcs[--i] );

    dc = GetDC( hwnd_classdc );
    SetROP2( dc, R2_WHITE );
    rop = GetROP2( dc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );
    ok( WindowFromDC( dc ) == hwnd_classdc, "wrong window\n" );
    old_dc = dc;

    dc = GetDC( hwnd_classdc2 );
    ok( old_dc == dc, "wrong DC\n" );
    rop = GetROP2( dc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );
    ok( WindowFromDC( dc ) == hwnd_classdc2, "wrong window\n" );
    DestroyWindow( hwnd_classdc2 );

    rop = GetROP2( dc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );
    ok( WindowFromDC( dc ) == 0, "wrong window\n" );
    ok( !ReleaseDC( hwnd_classdc2, dc ), "ReleaseDC succeeded\n" );
    dc = GetDC( hwnd_classdc2 );
    ok( !dc, "Got a non-NULL DC (%p) for a destroyed window\n", dc );

    dc = GetDC( hwnd_classdc );
    ok( dc != 0, "Got NULL DC\n" );
    rop = GetROP2( dc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );
    ok( WindowFromDC( dc ) == hwnd_classdc, "wrong window\n" );
    DestroyWindow( hwnd_classdc );

    rop = GetROP2( dc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );
    ok( WindowFromDC( dc ) == 0, "wrong window\n" );
    ok( !ReleaseDC( hwnd_classdc, dc ), "ReleaseDC succeeded\n" );
    dc = GetDC( hwnd_classdc );
    ok( !dc, "Got a non-NULL DC (%p) for a destroyed window\n", dc );

    dc = GetDC( hwnd_owndc );
    ok( dc != 0, "Got NULL DC\n" );
    rop = GetROP2( dc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );
    ok( WindowFromDC( dc ) == hwnd_owndc, "wrong window\n" );
    DestroyWindow( hwnd_owndc );

    rop = GetROP2( dc );
    ok( rop == 0, "wrong ROP2 %d\n", rop );
    ok( WindowFromDC( dc ) == 0, "wrong window\n" );
    ok( !ReleaseDC( hwnd_owndc, dc ), "ReleaseDC succeeded\n" );
    dc = GetDC( hwnd_owndc );
    ok( !dc, "Got a non-NULL DC (%p) for a destroyed window\n", dc );

    DestroyWindow( hwnd_parent );
}