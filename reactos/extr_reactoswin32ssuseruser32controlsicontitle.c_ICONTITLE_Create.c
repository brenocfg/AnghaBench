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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWLP_HINSTANCE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ICONTITLE_CLASS_ATOM ; 
 int /*<<< orphan*/  IsWindowEnabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WIN_SetOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WS_BORDER ; 
 int WS_CAPTION ; 
 int WS_CHILD ; 
 int WS_CLIPSIBLINGS ; 
 int WS_DISABLED ; 

HWND ICONTITLE_Create( HWND owner )
{
    HWND hWnd;
    HINSTANCE instance = (HINSTANCE)GetWindowLongPtrA( owner, GWLP_HINSTANCE );
    LONG style = WS_CLIPSIBLINGS;

    if (!IsWindowEnabled(owner)) style |= WS_DISABLED;
    if( GetWindowLongPtrA( owner, GWL_STYLE ) & WS_CHILD )
	hWnd = CreateWindowExA( 0, (LPCSTR)ICONTITLE_CLASS_ATOM, NULL,
                                style | WS_CHILD, 0, 0, 1, 1,
                                GetParent(owner), 0, instance, NULL );
    else
	hWnd = CreateWindowExA( 0, (LPCSTR)ICONTITLE_CLASS_ATOM, NULL,
                                style, 0, 0, 1, 1,
                                owner, 0, instance, NULL );
    WIN_SetOwner( hWnd, owner );  /* MDI depends on this */
    SetWindowLongPtrW( hWnd, GWL_STYLE,
                       GetWindowLongPtrW( hWnd, GWL_STYLE ) & ~(WS_CAPTION | WS_BORDER) );
    return hWnd;
}