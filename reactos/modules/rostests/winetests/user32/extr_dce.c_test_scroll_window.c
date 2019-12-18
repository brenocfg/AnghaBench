#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetClipBox (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int SW_ERASE ; 
 int SW_INVALIDATE ; 
 int /*<<< orphan*/  ScrollWindow (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ScrollWindowEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  SetViewportExtEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetViewportOrgEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd_owndc ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void test_scroll_window(void)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT clip, rect;

    /* ScrollWindow uses the window DC, ScrollWindowEx doesn't */

    UpdateWindow( hwnd_owndc );
    SetRect( &clip, 25, 25, 50, 50 );
    ScrollWindow( hwnd_owndc, -5, -10, NULL, &clip );
    hdc = BeginPaint( hwnd_owndc, &ps );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 25 && rect.top >= 25 && rect.right <= 50 && rect.bottom <= 50,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    EndPaint( hwnd_owndc, &ps );

    SetViewportExtEx( hdc, 2, 3, NULL );
    SetViewportOrgEx( hdc, 30, 20, NULL );

    ScrollWindow( hwnd_owndc, -5, -10, NULL, &clip );
    hdc = BeginPaint( hwnd_owndc, &ps );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 25 && rect.top >= 25 && rect.right <= 50 && rect.bottom <= 50,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    EndPaint( hwnd_owndc, &ps );

    ScrollWindowEx( hwnd_owndc, -5, -10, NULL, &clip, 0, NULL, SW_INVALIDATE | SW_ERASE );
    hdc = BeginPaint( hwnd_owndc, &ps );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= -5 && rect.top >= 5 && rect.right <= 20 && rect.bottom <= 30,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    EndPaint( hwnd_owndc, &ps );

    SetViewportExtEx( hdc, 1, 1, NULL );
    SetViewportOrgEx( hdc, 0, 0, NULL );

    ScrollWindowEx( hwnd_owndc, -5, -10, NULL, &clip, 0, NULL, SW_INVALIDATE | SW_ERASE );
    hdc = BeginPaint( hwnd_owndc, &ps );
    SetRectEmpty( &rect );
    GetClipBox( hdc, &rect );
    ok( rect.left >= 25 && rect.top >= 25 && rect.right <= 50 && rect.bottom <= 50,
        "invalid clip box %s\n", wine_dbgstr_rect( &rect ));
    EndPaint( hwnd_owndc, &ps );
}