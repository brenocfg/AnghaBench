#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_window_t ;
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_7__ {int /*<<< orphan*/  hwnd; TYPE_5__ window_placement; int /*<<< orphan*/  i_window_style; } ;
typedef  TYPE_2__ vout_window_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SetWindowLong (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPlacement (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 

__attribute__((used)) static void UnsetFullscreen(vout_window_t *wnd)
{
    msg_Dbg(wnd, "leaving fullscreen mode");
    vout_window_sys_t *sys = wnd->sys;

    /* return to normal window for non embedded vout */
    if (sys->window_placement.length)
    {
        SetWindowLong(sys->hwnd, GWL_STYLE, sys->i_window_style);
        SetWindowPlacement(sys->hwnd, &sys->window_placement);
        sys->window_placement.length = 0;
    }
    ShowWindow(sys->hwnd, SW_SHOWNORMAL);
}