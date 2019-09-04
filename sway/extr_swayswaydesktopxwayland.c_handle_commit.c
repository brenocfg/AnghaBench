#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlr_xwayland_surface {TYPE_1__* surface; } ;
struct wlr_surface_state {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct wlr_box {scalar_t__ width; scalar_t__ height; } ;
struct wl_listener {int dummy; } ;
struct sway_view {struct wlr_box geometry; struct sway_container* container; struct wlr_xwayland_surface* wlr_xwayland_surface; } ;
struct sway_xwayland_view {struct sway_view view; } ;
struct TYPE_4__ {scalar_t__ instruction; } ;
struct sway_container {scalar_t__ surface_width; scalar_t__ surface_height; TYPE_2__ node; } ;
struct TYPE_3__ {struct wlr_surface_state current; } ;

/* Variables and functions */
 int /*<<< orphan*/  commit ; 
 int /*<<< orphan*/  desktop_damage_view (struct sway_view*) ; 
 int /*<<< orphan*/  get_geometry (struct sway_view*,struct wlr_box*) ; 
 int /*<<< orphan*/  memcpy (struct wlr_box*,struct wlr_box*,int) ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 int /*<<< orphan*/  transaction_notify_view_ready_by_size (struct sway_view*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  view_damage_from (struct sway_view*) ; 
 int /*<<< orphan*/  view_update_size (struct sway_view*,scalar_t__,scalar_t__) ; 
 struct sway_xwayland_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sway_xwayland_view* xwayland_view ; 

__attribute__((used)) static void handle_commit(struct wl_listener *listener, void *data) {
	struct sway_xwayland_view *xwayland_view =
		wl_container_of(listener, xwayland_view, commit);
	struct sway_view *view = &xwayland_view->view;
	struct wlr_xwayland_surface *xsurface = view->wlr_xwayland_surface;
	struct wlr_surface_state *state = &xsurface->surface->current;

	if (view->container->node.instruction) {
		get_geometry(view, &view->geometry);
		transaction_notify_view_ready_by_size(view,
				state->width, state->height);
	} else {
		struct wlr_box new_geo;
		get_geometry(view, &new_geo);
		struct sway_container *con = view->container;

		if ((new_geo.width != con->surface_width ||
					new_geo.height != con->surface_height)) {
			// The view has unexpectedly sent a new size
			// eg. The Firefox "Save As" dialog when downloading a file
			desktop_damage_view(view);
			view_update_size(view, new_geo.width, new_geo.height);
			memcpy(&view->geometry, &new_geo, sizeof(struct wlr_box));
			desktop_damage_view(view);
			transaction_commit_dirty();
		} else {
			memcpy(&view->geometry, &new_geo, sizeof(struct wlr_box));
		}
	}

	view_damage_from(view);
}