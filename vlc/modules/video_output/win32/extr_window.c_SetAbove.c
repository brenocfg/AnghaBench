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
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_window_t ;
struct TYPE_5__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_2__ vout_window_sys_t ;
typedef  enum vout_window_state { ____Placeholder_vout_window_state } vout_window_state ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GetSystemMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowLong (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HWND_BOTTOM ; 
 int /*<<< orphan*/  HWND_NOTOPMOST ; 
 int /*<<< orphan*/  HWND_TOPMOST ; 
 int /*<<< orphan*/  IDM_TOGGLE_ON_TOP ; 
 int MFS_CHECKED ; 
 int MFS_UNCHECKED ; 
 int MF_BYCOMMAND ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  VOUT_WINDOW_STATE_ABOVE 130 
#define  VOUT_WINDOW_STATE_BELOW 129 
#define  VOUT_WINDOW_STATE_NORMAL 128 
 int WS_EX_TOPMOST ; 

__attribute__((used)) static void SetAbove( vout_window_t *wnd, enum vout_window_state state )
{
    vout_window_sys_t *sys = wnd->sys;
    switch (state) {
    case VOUT_WINDOW_STATE_NORMAL:
        if ((GetWindowLong(sys->hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST))
        {
            HMENU hMenu = GetSystemMenu(sys->hwnd, FALSE);
            CheckMenuItem(hMenu, IDM_TOGGLE_ON_TOP, MF_BYCOMMAND | MFS_UNCHECKED);
            SetWindowPos(sys->hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
        }
        break;
    case VOUT_WINDOW_STATE_ABOVE:
        if (!(GetWindowLong(sys->hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST))
        {
            HMENU hMenu = GetSystemMenu(sys->hwnd, FALSE);
            CheckMenuItem(hMenu, IDM_TOGGLE_ON_TOP, MF_BYCOMMAND | MFS_CHECKED);
            SetWindowPos(sys->hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        }
        break;
    case VOUT_WINDOW_STATE_BELOW:
        SetWindowPos(sys->hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        break;

    }
}