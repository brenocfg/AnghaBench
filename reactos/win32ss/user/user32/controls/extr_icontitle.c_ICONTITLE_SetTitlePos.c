#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  str ;
typedef  char WCHAR ;
struct TYPE_7__ {int x; int y; } ;
struct TYPE_6__ {int right; int left; int bottom; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int DT_CALCRECT ; 
 int DT_CENTER ; 
 int DT_NOPREFIX ; 
 int DT_SINGLELINE ; 
 int DT_WORDBREAK ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int GetWindowTextW (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXBORDER ; 
 int /*<<< orphan*/  SM_CXICON ; 
 int /*<<< orphan*/  SM_CXICONSPACING ; 
 int /*<<< orphan*/  SM_CYBORDER ; 
 int /*<<< orphan*/  SM_CYICON ; 
 int /*<<< orphan*/  SWP_NOACTIVATE ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bMultiLineTitle ; 
 int /*<<< orphan*/  hIconTitleFont ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 
 int strlenW (char*) ; 

__attribute__((used)) static BOOL ICONTITLE_SetTitlePos( HWND hwnd, HWND owner )
{
    static const WCHAR emptyTitleText[] = {'<','.','.','.','>',0};
    WCHAR str[80];
    HDC hDC;
    HFONT hPrevFont;
    RECT rect;
    INT cx, cy;
    POINT pt;

    int length = GetWindowTextW( owner, str, sizeof(str)/sizeof(WCHAR) );

    while (length && str[length - 1] == ' ') /* remove trailing spaces */
        str[--length] = 0;

    if( !length )
    {
        strcpyW( str, emptyTitleText );
        length = strlenW( str );
    }

    if (!(hDC = GetDC( hwnd ))) return FALSE;

    hPrevFont = SelectObject( hDC, hIconTitleFont );

    SetRect( &rect, 0, 0, GetSystemMetrics(SM_CXICONSPACING) -
             GetSystemMetrics(SM_CXBORDER) * 2,
             GetSystemMetrics(SM_CYBORDER) * 2 );

    DrawTextW( hDC, str, length, &rect, DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK |
               (( bMultiLineTitle ) ? 0 : DT_SINGLELINE) );

    SelectObject( hDC, hPrevFont );
    ReleaseDC( hwnd, hDC );

    cx = rect.right - rect.left +  4 * GetSystemMetrics(SM_CXBORDER);
    cy = rect.bottom - rect.top;

    pt.x = (GetSystemMetrics(SM_CXICON) - cx) / 2;
    pt.y = GetSystemMetrics(SM_CYICON);

    /* point is relative to owner, make it relative to parent */
    MapWindowPoints( owner, GetParent(hwnd), &pt, 1 );

    SetWindowPos( hwnd, owner, pt.x, pt.y, cx, cy, SWP_NOACTIVATE );
    return TRUE;
}