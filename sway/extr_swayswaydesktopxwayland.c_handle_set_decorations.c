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
struct wlr_xwayland_surface {scalar_t__ decorations; } ;
struct wl_listener {int dummy; } ;
struct sway_view {struct wlr_xwayland_surface* wlr_xwayland_surface; } ;
struct sway_xwayland_view {struct sway_view view; } ;

/* Variables and functions */
 scalar_t__ WLR_XWAYLAND_SURFACE_DECORATIONS_ALL ; 
 int /*<<< orphan*/  set_decorations ; 
 int /*<<< orphan*/  view_update_csd_from_client (struct sway_view*,int) ; 
 struct sway_xwayland_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sway_xwayland_view* xwayland_view ; 

__attribute__((used)) static void handle_set_decorations(struct wl_listener *listener, void *data) {
	struct sway_xwayland_view *xwayland_view =
		wl_container_of(listener, xwayland_view, set_decorations);
	struct sway_view *view = &xwayland_view->view;
	struct wlr_xwayland_surface *xsurface = view->wlr_xwayland_surface;

	bool csd = xsurface->decorations != WLR_XWAYLAND_SURFACE_DECORATIONS_ALL;
	view_update_csd_from_client(view, csd);
}