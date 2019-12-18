#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_window_t ;
struct TYPE_14__ {int length; } ;
struct TYPE_11__ {int /*<<< orphan*/  hwnd; int /*<<< orphan*/  i_window_style; TYPE_8__ window_placement; } ;
typedef  TYPE_2__ vout_window_sys_t ;
typedef  int /*<<< orphan*/  WINDOWPLACEMENT ;
struct TYPE_13__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_12__ {int cbSize; TYPE_6__ rcMonitor; } ;
typedef  TYPE_3__ MONITORINFO ;
typedef  int /*<<< orphan*/  HMONITOR ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetMonitorInfo (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GetWindowLong (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowPlacement (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  MONITOR_DEFAULTTONEAREST ; 
 int /*<<< orphan*/  MonitorFromWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECTHeight (TYPE_6__) ; 
 int /*<<< orphan*/  RECTWidth (TYPE_6__) ; 
 int SWP_FRAMECHANGED ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowLong (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int WS_CLIPCHILDREN ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 

__attribute__((used)) static void SetFullscreen(vout_window_t *wnd, const char *id)
{
    VLC_UNUSED(id);
    msg_Dbg(wnd, "entering fullscreen mode");
    vout_window_sys_t *sys = wnd->sys;

    sys->window_placement.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(sys->hwnd, &sys->window_placement);

    sys->i_window_style = GetWindowLong(sys->hwnd, GWL_STYLE);

    /* Change window style, no borders and no title bar */
    SetWindowLong(sys->hwnd, GWL_STYLE, WS_CLIPCHILDREN | WS_VISIBLE);

    /* Retrieve current window position so fullscreen will happen
     * on the right screen */
    HMONITOR hmon = MonitorFromWindow(sys->hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi;
    mi.cbSize = sizeof(MONITORINFO);
    if (GetMonitorInfo(hmon, &mi))
        SetWindowPos(sys->hwnd, 0,
                     mi.rcMonitor.left,
                     mi.rcMonitor.top,
                     RECTWidth(mi.rcMonitor),
                     RECTHeight(mi.rcMonitor),
                     SWP_NOZORDER|SWP_FRAMECHANGED);
}