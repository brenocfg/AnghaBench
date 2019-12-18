#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wlr_xwayland_surface {int /*<<< orphan*/  fullscreen; TYPE_3__* surface; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * data; scalar_t__ override_redirect; } ;
struct wl_listener {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  notify; } ;
struct sway_view {int /*<<< orphan*/  natural_height; int /*<<< orphan*/  natural_width; } ;
struct sway_xwayland_view {TYPE_2__ commit; int /*<<< orphan*/  destroy; struct sway_view view; } ;
struct sway_xwayland_unmanaged {int /*<<< orphan*/  map; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit; } ;
struct TYPE_6__ {TYPE_1__ events; } ;

/* Variables and functions */
 struct sway_xwayland_unmanaged* create_unmanaged (struct wlr_xwayland_surface*) ; 
 int /*<<< orphan*/  handle_commit ; 
 int /*<<< orphan*/  handle_destroy (int /*<<< orphan*/ *,struct sway_view*) ; 
 int /*<<< orphan*/  map ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 int /*<<< orphan*/  unmanaged_handle_map (int /*<<< orphan*/ *,struct wlr_xwayland_surface*) ; 
 int /*<<< orphan*/  view_map (struct sway_view*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct sway_xwayland_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 struct sway_xwayland_view* xwayland_view ; 

__attribute__((used)) static void handle_map(struct wl_listener *listener, void *data) {
	struct sway_xwayland_view *xwayland_view =
		wl_container_of(listener, xwayland_view, map);
	struct wlr_xwayland_surface *xsurface = data;
	struct sway_view *view = &xwayland_view->view;

	if (xsurface->override_redirect) {
		// This window used not to have the override redirect flag and has it
		// now. Switch to unmanaged.
		handle_destroy(&xwayland_view->destroy, view);
		xsurface->data = NULL;
		struct sway_xwayland_unmanaged *unmanaged = create_unmanaged(xsurface);
		unmanaged_handle_map(&unmanaged->map, xsurface);
		return;
	}

	view->natural_width = xsurface->width;
	view->natural_height = xsurface->height;

	// Wire up the commit listener here, because xwayland map/unmap can change
	// the underlying wlr_surface
	wl_signal_add(&xsurface->surface->events.commit, &xwayland_view->commit);
	xwayland_view->commit.notify = handle_commit;

	// Put it back into the tree
	view_map(view, xsurface->surface, xsurface->fullscreen, NULL, false);

	transaction_commit_dirty();
}