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
struct wlr_xdg_surface {scalar_t__ role; scalar_t__ toplevel; } ;
struct sway_view {struct wlr_xdg_surface* wlr_xdg_surface; } ;

/* Variables and functions */
 scalar_t__ WLR_XDG_SURFACE_ROLE_TOPLEVEL ; 
 int /*<<< orphan*/  wlr_xdg_toplevel_send_close (struct wlr_xdg_surface*) ; 
 int /*<<< orphan*/ * xdg_shell_view_from_view (struct sway_view*) ; 

__attribute__((used)) static void _close(struct sway_view *view) {
	if (xdg_shell_view_from_view(view) == NULL) {
		return;
	}
	struct wlr_xdg_surface *surface = view->wlr_xdg_surface;
	if (surface->role == WLR_XDG_SURFACE_ROLE_TOPLEVEL
			&& surface->toplevel) {
		wlr_xdg_toplevel_send_close(surface);
	}
}