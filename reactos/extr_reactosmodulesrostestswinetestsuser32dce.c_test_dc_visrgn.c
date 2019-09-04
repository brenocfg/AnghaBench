#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  scalar_t__ HRGN ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 scalar_t__ CreateRectRgnIndirect (TYPE_1__*) ; 
 int DCX_EXCLUDERGN ; 
 int DCX_INTERSECTRGN ; 
 int DCX_NORESETATTRS ; 
 int DCX_USESTYLE ; 
 scalar_t__ ERROR ; 
 int EqualRect (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetClipBox (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDCEx (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ GetRgnBox (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  hwnd_cache ; 
 int /*<<< orphan*/  hwnd_classdc ; 
 int /*<<< orphan*/  hwnd_classdc2 ; 
 int /*<<< orphan*/  hwnd_owndc ; 
 int /*<<< orphan*/  hwnd_parent ; 
 int /*<<< orphan*/  hwnd_parentdc ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void test_dc_visrgn(void)
{
    HDC old_hdc, hdc;
    HRGN hrgn, hrgn2;
    RECT rect, parent_rect;

    /* cache DC */

    SetRect( &rect, 10, 10, 20, 20 );
    MapWindowPoints( hwnd_cache, 0, (POINT *)&rect, 2 );
    hrgn = CreateRectRgnIndirect( &rect );
    hdc = GetDCEx( hwnd_cache, hrgn, DCX_INTERSECTRGN | DCX_USESTYLE );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 10 && rect.top >= 10 && rect.right <= 20 && rect.bottom <= 20,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );
    ReleaseDC( hwnd_cache, hdc );
    ok( GetRgnBox( hrgn, &rect ) == ERROR, "region must no longer be valid\n" );

    /* cache DC with NORESETATTRS */

    SetRect( &rect, 10, 10, 20, 20 );
    MapWindowPoints( hwnd_cache, 0, (POINT *)&rect, 2 );
    hrgn = CreateRectRgnIndirect( &rect );
    hdc = GetDCEx( hwnd_cache, hrgn, DCX_INTERSECTRGN | DCX_USESTYLE | DCX_NORESETATTRS );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 10 && rect.top >= 10 && rect.right <= 20 && rect.bottom <= 20,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );
    ReleaseDC( hwnd_cache, hdc );
    ok( GetRgnBox( hrgn, &rect ) == ERROR, "region must no longer be valid\n" );
    hdc = GetDCEx( hwnd_cache, 0, DCX_USESTYLE | DCX_NORESETATTRS );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( !(rect.left >= 10 && rect.top >= 10 && rect.right <= 20 && rect.bottom <= 20),
        "clip box should have been reset %s\n", wine_dbgstr_rect( &rect ));
    ReleaseDC( hwnd_cache, hdc );

    /* window DC */

    SetRect( &rect, 10, 10, 20, 20 );
    MapWindowPoints( hwnd_owndc, 0, (POINT *)&rect, 2 );
    hrgn = CreateRectRgnIndirect( &rect );
    hdc = GetDCEx( hwnd_owndc, hrgn, DCX_INTERSECTRGN | DCX_USESTYLE );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 10 && rect.top >= 10 && rect.right <= 20 && rect.bottom <= 20,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );
    ReleaseDC( hwnd_owndc, hdc );
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 10 && rect.top >= 10 && rect.right <= 20 && rect.bottom <= 20,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    hdc = GetDCEx( hwnd_owndc, 0, DCX_USESTYLE );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 10 && rect.top >= 10 && rect.right <= 20 && rect.bottom <= 20,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );
    ReleaseDC( hwnd_owndc, hdc );
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );

    SetRect( &rect, 20, 20, 30, 30 );
    MapWindowPoints( hwnd_owndc, 0, (POINT *)&rect, 2 );
    hrgn2 = CreateRectRgnIndirect( &rect );
    hdc = GetDCEx( hwnd_owndc, hrgn2, DCX_INTERSECTRGN | DCX_USESTYLE );
    ok( GetRgnBox( hrgn, &rect ) == ERROR, "region must no longer be valid\n" );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 20 && rect.top >= 20 && rect.right <= 30 && rect.bottom <= 30,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    ok( GetRgnBox( hrgn2, &rect ) != ERROR, "region2 must still be valid\n" );
    ReleaseDC( hwnd_owndc, hdc );
    ok( GetRgnBox( hrgn2, &rect ) != ERROR, "region2 must still be valid\n" );
    hdc = GetDCEx( hwnd_owndc, 0, DCX_EXCLUDERGN | DCX_USESTYLE );
    ok( GetRgnBox( hrgn2, &rect ) == ERROR, "region must no longer be valid\n" );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( !(rect.left >= 20 && rect.top >= 20 && rect.right <= 30 && rect.bottom <= 30),
        "clip box should have been reset %s\n", wine_dbgstr_rect( &rect ));
    ReleaseDC( hwnd_owndc, hdc );

    /* class DC */

    SetRect( &rect, 10, 10, 20, 20 );
    MapWindowPoints( hwnd_classdc, 0, (POINT *)&rect, 2 );
    hrgn = CreateRectRgnIndirect( &rect );
    hdc = GetDCEx( hwnd_classdc, hrgn, DCX_INTERSECTRGN | DCX_USESTYLE );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 10 && rect.top >= 10 && rect.right <= 20 && rect.bottom <= 20,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );
    ReleaseDC( hwnd_classdc, hdc );
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 10 && rect.top >= 10 && rect.right <= 20 && rect.bottom <= 20,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));

    hdc = GetDCEx( hwnd_classdc, 0, DCX_USESTYLE );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 10 && rect.top >= 10 && rect.right <= 20 && rect.bottom <= 20,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );
    ReleaseDC( hwnd_classdc, hdc );
    ok( GetRgnBox( hrgn, &rect ) != ERROR, "region must still be valid\n" );

    SetRect( &rect, 20, 20, 30, 30 );
    MapWindowPoints( hwnd_classdc, 0, (POINT *)&rect, 2 );
    hrgn2 = CreateRectRgnIndirect( &rect );
    hdc = GetDCEx( hwnd_classdc, hrgn2, DCX_INTERSECTRGN | DCX_USESTYLE );
    ok( GetRgnBox( hrgn, &rect ) == ERROR, "region must no longer be valid\n" );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 20 && rect.top >= 20 && rect.right <= 30 && rect.bottom <= 30,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    ok( GetRgnBox( hrgn2, &rect ) != ERROR, "region2 must still be valid\n" );

    old_hdc = hdc;
    hdc = GetDCEx( hwnd_classdc2, 0, DCX_USESTYLE );
    ok( old_hdc == hdc, "did not get the same hdc %p/%p\n", old_hdc, hdc );
    ok( GetRgnBox( hrgn2, &rect ) != ERROR, "region2 must still be valid\n" );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( !(rect.left >= 20 && rect.top >= 20 && rect.right <= 30 && rect.bottom <= 30),
        "clip box should have been reset %s\n", wine_dbgstr_rect( &rect ));
    ReleaseDC( hwnd_classdc2, hdc );
    ok( GetRgnBox( hrgn2, &rect ) != ERROR, "region2 must still be valid\n" );
    hdc = GetDCEx( hwnd_classdc2, 0, DCX_EXCLUDERGN | DCX_USESTYLE );
    ok( GetRgnBox( hrgn2, &rect ) != ERROR, "region2 must still be valid\n" );
    ok( !(rect.left >= 20 && rect.top >= 20 && rect.right <= 30 && rect.bottom <= 30),
        "clip box must have been reset %s\n", wine_dbgstr_rect( &rect ));
    ReleaseDC( hwnd_classdc2, hdc );

    /* parent DC */
    hdc = GetDC( hwnd_parentdc );
    GetClipBox( hdc, &rect );
    ReleaseDC( hwnd_parentdc, hdc );

    hdc = GetDC( hwnd_parent );
    GetClipBox( hdc, &parent_rect );
    ReleaseDC( hwnd_parent, hdc );

    ok( EqualRect( &rect, &parent_rect ), "rect = %s, expected %s\n", wine_dbgstr_rect( &rect ),
        wine_dbgstr_rect( &parent_rect ));
}