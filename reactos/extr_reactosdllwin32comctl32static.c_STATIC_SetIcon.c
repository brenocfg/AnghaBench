#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HICON ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HICON_GWL_OFFSET ; 
 int SS_CENTERIMAGE ; 
 int SS_ICON ; 
 int SS_REALSIZECONTROL ; 
 int SS_TYPEMASK ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOZORDER ; 
 scalar_t__ SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  get_icon_size (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static HICON STATIC_SetIcon( HWND hwnd, HICON hicon, DWORD style )
{
    HICON prevIcon;
    SIZE size;

    if ((style & SS_TYPEMASK) != SS_ICON) return 0;
    if (hicon && !get_icon_size( hicon, &size ))
    {
        WARN("hicon != 0, but invalid\n");
        return 0;
    }
    prevIcon = (HICON)SetWindowLongPtrW( hwnd, HICON_GWL_OFFSET, (LONG_PTR)hicon );
    if (hicon && !(style & SS_CENTERIMAGE) && !(style & SS_REALSIZECONTROL))
    {
        /* Windows currently doesn't implement SS_RIGHTJUST */
        /*
        if ((style & SS_RIGHTJUST) != 0)
        {
            RECT wr;
            GetWindowRect(hwnd, &wr);
            SetWindowPos( hwnd, 0, wr.right - info->nWidth, wr.bottom - info->nHeight,
                          info->nWidth, info->nHeight, SWP_NOACTIVATE | SWP_NOZORDER );
        }
        else */
        {
            SetWindowPos( hwnd, 0, 0, 0, size.cx, size.cy, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER );
        }
    }
    return prevIcon;
}