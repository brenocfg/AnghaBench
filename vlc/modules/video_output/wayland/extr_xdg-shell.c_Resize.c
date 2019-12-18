#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  wl; } ;
struct TYPE_9__ {TYPE_2__ display; TYPE_4__* sys; } ;
typedef  TYPE_3__ vout_window_t ;
struct TYPE_7__ {unsigned int width; unsigned int height; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_1__ set; int /*<<< orphan*/  toplevel; } ;
typedef  TYPE_4__ vout_window_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ReportSize (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_display_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdg_toplevel_set_max_size (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  xdg_toplevel_set_min_size (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void Resize(vout_window_t *wnd, unsigned width, unsigned height)
{
    vout_window_sys_t *sys = wnd->sys;

#ifdef XDG_SHELL
    /* The minimum size must be smaller or equal to the maximum size
     * at _all_ times. This gets a bit cumbersome. */
    xdg_toplevel_set_min_size(sys->toplevel, 0, 0);
    xdg_toplevel_set_max_size(sys->toplevel, width, height);
    xdg_toplevel_set_min_size(sys->toplevel, width, height);
#endif

    vlc_mutex_lock(&sys->lock);
    sys->set.width = width;
    sys->set.height = height;
    ReportSize(wnd);
    vlc_mutex_unlock(&sys->lock);
    wl_display_flush(wnd->display.wl);
}