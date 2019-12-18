#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wl; } ;
struct TYPE_6__ {TYPE_1__ display; TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_window_t ;
struct TYPE_7__ {int /*<<< orphan*/  toplevel; } ;
typedef  TYPE_3__ vout_window_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  wl_display_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdg_toplevel_unset_fullscreen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UnsetFullscreen(vout_window_t *wnd)
{
    vout_window_sys_t *sys = wnd->sys;

    xdg_toplevel_unset_fullscreen(sys->toplevel);
    wl_display_flush(wnd->display.wl);
}