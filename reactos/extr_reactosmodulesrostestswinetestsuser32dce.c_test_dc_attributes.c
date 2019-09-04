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
typedef  scalar_t__ INT ;
typedef  scalar_t__ HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int DCX_NORESETATTRS ; 
 int DCX_USESTYLE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetDC (scalar_t__) ; 
 scalar_t__ GetDCEx (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetDeviceCaps (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetROP2 (scalar_t__) ; 
 int /*<<< orphan*/  HORZRES ; 
 int /*<<< orphan*/  NUMCOLORS ; 
 scalar_t__ R2_BLACK ; 
 scalar_t__ R2_WHITE ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,scalar_t__) ; 
 scalar_t__ SetROP2 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERTRES ; 
 scalar_t__ WindowFromDC (scalar_t__) ; 
 scalar_t__ broken (int) ; 
 scalar_t__ hwnd_cache ; 
 scalar_t__ hwnd_classdc ; 
 scalar_t__ hwnd_classdc2 ; 
 scalar_t__ hwnd_owndc ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void test_dc_attributes(void)
{
    HDC hdc, old_hdc;
    HDC hdcs[20];
    INT i, rop, def_rop, caps;
    BOOL found_dc;

    /* test cache DC */

    hdc = GetDC( hwnd_cache );
    def_rop = GetROP2( hdc );

    SetROP2( hdc, R2_WHITE );
    rop = GetROP2( hdc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );

    ok( WindowFromDC( hdc ) == hwnd_cache, "wrong window\n" );
    ReleaseDC( hwnd_cache, hdc );
    ok( WindowFromDC( hdc ) == 0, "wrong window\n" );
    hdc = GetDC( hwnd_cache );
    rop = GetROP2( hdc );
    ok( rop == def_rop, "wrong ROP2 %d after release\n", rop );
    SetROP2( hdc, R2_WHITE );
    ok( WindowFromDC( hdc ) == hwnd_cache, "wrong window\n" );
    ReleaseDC( hwnd_cache, hdc );
    old_hdc = hdc;

    found_dc = FALSE;
    for (i = 0; i < 20; i++)
    {
        hdc = hdcs[i] = GetDCEx( hwnd_cache, 0, DCX_USESTYLE | DCX_NORESETATTRS );
        if (!hdc) break;
        rop = GetROP2( hdc );
        ok( rop == def_rop, "wrong ROP2 %d after release %p/%p\n", rop, old_hdc, hdc );
        if (hdc == old_hdc)
        {
            found_dc = TRUE;
            SetROP2( hdc, R2_WHITE );
        }
    }
    if (!found_dc)
    {
        trace( "hdc %p not found in cache using %p\n", old_hdc, hdcs[0] );
        old_hdc = hdcs[0];
        SetROP2( old_hdc, R2_WHITE );
    }
    while (i > 0) ReleaseDC( hwnd_cache, hdcs[--i] );

    for (i = 0; i < 20; i++)
    {
        hdc = hdcs[i] = GetDCEx( hwnd_cache, 0, DCX_USESTYLE | DCX_NORESETATTRS );
        if (!hdc) break;
        rop = GetROP2( hdc );
        if (hdc == old_hdc)
            ok( rop == R2_WHITE || broken( rop == def_rop),  /* win9x doesn't support DCX_NORESETATTRS */
                "wrong ROP2 %d after release %p/%p\n", rop, old_hdc, hdc );
        else
            ok( rop == def_rop, "wrong ROP2 %d after release %p/%p\n", rop, old_hdc, hdc );
    }
    while (i > 0) ReleaseDC( hwnd_cache, hdcs[--i] );

    for (i = 0; i < 20; i++)
    {
        hdc = hdcs[i] = GetDCEx( hwnd_cache, 0, DCX_USESTYLE );
        if (!hdc) break;
        rop = GetROP2( hdc );
        if (hdc == old_hdc)
        {
            ok( rop == R2_WHITE || broken( rop == def_rop),
                "wrong ROP2 %d after release %p/%p\n", rop, old_hdc, hdc );
            SetROP2( old_hdc, def_rop );
        }
        else
            ok( rop == def_rop, "wrong ROP2 %d after release %p/%p\n", rop, old_hdc, hdc );
    }
    while (i > 0) ReleaseDC( hwnd_cache, hdcs[--i] );

    /* Released cache DCs are 'disabled' */
    rop = SetROP2( old_hdc, R2_BLACK );
    ok( rop == 0, "got %d\n", rop );
    rop = GetROP2( old_hdc );
    ok( rop == 0, "got %d\n", rop );
    caps = GetDeviceCaps( old_hdc, HORZRES );
    ok( caps == 0, "got %d\n", caps );
    caps = GetDeviceCaps( old_hdc, VERTRES );
    ok( caps == 0, "got %d\n", caps );
    caps = GetDeviceCaps( old_hdc, NUMCOLORS );
    ok( caps == 0, "got %d\n", caps );
    ok( WindowFromDC( old_hdc ) == 0, "wrong window\n" );

    hdc = GetDC(0);
    caps = GetDeviceCaps( hdc, HORZRES );
    ok( caps != 0, "got %d\n", caps );
    caps = GetDeviceCaps( hdc, VERTRES );
    ok( caps != 0, "got %d\n", caps );
    caps = GetDeviceCaps( hdc, NUMCOLORS );
    ok( caps != 0, "got %d\n", caps );
    ReleaseDC( 0, hdc );
    caps = GetDeviceCaps( hdc, HORZRES );
    ok( caps == 0, "got %d\n", caps );
    caps = GetDeviceCaps( hdc, VERTRES );
    ok( caps == 0, "got %d\n", caps );
    caps = GetDeviceCaps( hdc, NUMCOLORS );
    ok( caps == 0, "got %d\n", caps );

    /* test own DC */

    hdc = GetDC( hwnd_owndc );
    SetROP2( hdc, R2_WHITE );
    rop = GetROP2( hdc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );

    old_hdc = hdc;
    ok( WindowFromDC( hdc ) == hwnd_owndc, "wrong window\n" );
    ReleaseDC( hwnd_owndc, hdc );
    ok( WindowFromDC( hdc ) == hwnd_owndc, "wrong window\n" );
    hdc = GetDC( hwnd_owndc );
    ok( old_hdc == hdc, "didn't get same DC %p/%p\n", old_hdc, hdc );
    rop = GetROP2( hdc );
    ok( rop == R2_WHITE, "wrong ROP2 %d after release\n", rop );
    ok( WindowFromDC( hdc ) == hwnd_owndc, "wrong window\n" );
    ReleaseDC( hwnd_owndc, hdc );
    rop = GetROP2( hdc );
    ok( rop == R2_WHITE, "wrong ROP2 %d after second release\n", rop );

    /* test class DC */

    hdc = GetDC( hwnd_classdc );
    SetROP2( hdc, R2_WHITE );
    rop = GetROP2( hdc );
    ok( rop == R2_WHITE, "wrong ROP2 %d\n", rop );

    old_hdc = hdc;
    ok( WindowFromDC( hdc ) == hwnd_classdc, "wrong window\n" );
    ReleaseDC( hwnd_classdc, hdc );
    ok( WindowFromDC( hdc ) == hwnd_classdc, "wrong window\n" );
    hdc = GetDC( hwnd_classdc );
    ok( old_hdc == hdc, "didn't get same DC %p/%p\n", old_hdc, hdc );
    rop = GetROP2( hdc );
    ok( rop == R2_WHITE, "wrong ROP2 %d after release\n", rop );
    ok( WindowFromDC( hdc ) == hwnd_classdc, "wrong window\n" );
    ReleaseDC( hwnd_classdc, hdc );
    rop = GetROP2( hdc );
    ok( rop == R2_WHITE, "wrong ROP2 %d after second release\n", rop );

    /* test class DC with 2 windows */

    old_hdc = GetDC( hwnd_classdc );
    SetROP2( old_hdc, R2_BLACK );
    ok( WindowFromDC( old_hdc ) == hwnd_classdc, "wrong window\n" );
    hdc = GetDC( hwnd_classdc2 );
    ok( old_hdc == hdc, "didn't get same DC %p/%p\n", old_hdc, hdc );
    rop = GetROP2( hdc );
    ok( rop == R2_BLACK, "wrong ROP2 %d for other window\n", rop );
    ok( WindowFromDC( hdc ) == hwnd_classdc2, "wrong window\n" );
    ReleaseDC( hwnd_classdc, old_hdc );
    ReleaseDC( hwnd_classdc, hdc );
    ok( WindowFromDC( hdc ) == hwnd_classdc2, "wrong window\n" );
    rop = GetROP2( hdc );
    ok( rop == R2_BLACK, "wrong ROP2 %d after release\n", rop );
}