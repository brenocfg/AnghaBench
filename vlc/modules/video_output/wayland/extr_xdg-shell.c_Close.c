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
struct TYPE_7__ {int /*<<< orphan*/ * wl; } ;
struct TYPE_9__ {TYPE_2__ display; TYPE_1__ handle; TYPE_4__* sys; } ;
typedef  TYPE_3__ vout_window_t ;
struct TYPE_10__ {int /*<<< orphan*/  registry; int /*<<< orphan*/  compositor; int /*<<< orphan*/ * shm; int /*<<< orphan*/  wm_base; int /*<<< orphan*/  surface; int /*<<< orphan*/  toplevel; int /*<<< orphan*/ * cursor_theme; int /*<<< orphan*/ * cursor_surface; int /*<<< orphan*/ * deco_manager; int /*<<< orphan*/ * deco; int /*<<< orphan*/  outputs; int /*<<< orphan*/  seats; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; } ;
typedef  TYPE_4__ vout_window_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  output_list_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seat_destroy_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_compositor_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_cursor_theme_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_display_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_registry_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_shm_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdg_surface_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdg_toplevel_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdg_wm_base_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zxdg_decoration_manager_v1_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zxdg_toplevel_decoration_v1_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close(vout_window_t *wnd)
{
    vout_window_sys_t *sys = wnd->sys;

    vlc_cancel(sys->thread);
    vlc_join(sys->thread, NULL);

    vlc_mutex_destroy(&sys->lock);
    seat_destroy_all(&sys->seats);
    output_list_destroy(sys->outputs);
#ifdef XDG_SHELL
    if (sys->deco != NULL)
        zxdg_toplevel_decoration_v1_destroy(sys->deco);
    if (sys->deco_manager != NULL)
        zxdg_decoration_manager_v1_destroy(sys->deco_manager);
#endif
    if (sys->cursor_surface != NULL)
        wl_surface_destroy(sys->cursor_surface);
    if (sys->cursor_theme != NULL)
        wl_cursor_theme_destroy(sys->cursor_theme);
    xdg_toplevel_destroy(sys->toplevel);
    xdg_surface_destroy(sys->surface);
    xdg_wm_base_destroy(sys->wm_base);
    wl_surface_destroy(wnd->handle.wl);
    if (sys->shm != NULL)
        wl_shm_destroy(sys->shm);
    wl_compositor_destroy(sys->compositor);
    wl_registry_destroy(sys->registry);
    wl_display_disconnect(wnd->display.wl);
    free(sys);
}