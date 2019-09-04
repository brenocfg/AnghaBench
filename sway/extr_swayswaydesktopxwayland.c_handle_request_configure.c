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
struct wlr_xwayland_surface_configure_event {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct wlr_xwayland_surface {int /*<<< orphan*/  mapped; } ;
struct wl_listener {int dummy; } ;
struct sway_view {TYPE_2__* container; int /*<<< orphan*/  natural_height; int /*<<< orphan*/  natural_width; struct wlr_xwayland_surface* wlr_xwayland_surface; } ;
struct sway_xwayland_view {struct sway_view view; } ;
struct TYPE_4__ {int /*<<< orphan*/  content_height; int /*<<< orphan*/  content_width; int /*<<< orphan*/  content_y; int /*<<< orphan*/  content_x; } ;
struct TYPE_5__ {TYPE_1__ current; int /*<<< orphan*/  node; int /*<<< orphan*/  content_height; int /*<<< orphan*/  content_width; int /*<<< orphan*/  content_y; int /*<<< orphan*/  content_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  configure (struct sway_view*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  container_floating_resize_and_center (TYPE_2__*) ; 
 scalar_t__ container_is_floating (TYPE_2__*) ; 
 int /*<<< orphan*/  node_set_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_configure ; 
 struct sway_xwayland_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_xwayland_surface_configure (struct wlr_xwayland_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sway_xwayland_view* xwayland_view ; 

__attribute__((used)) static void handle_request_configure(struct wl_listener *listener, void *data) {
	struct sway_xwayland_view *xwayland_view =
		wl_container_of(listener, xwayland_view, request_configure);
	struct wlr_xwayland_surface_configure_event *ev = data;
	struct sway_view *view = &xwayland_view->view;
	struct wlr_xwayland_surface *xsurface = view->wlr_xwayland_surface;
	if (!xsurface->mapped) {
		wlr_xwayland_surface_configure(xsurface, ev->x, ev->y,
			ev->width, ev->height);
		return;
	}
	if (container_is_floating(view->container)) {
		// Respect minimum and maximum sizes
		view->natural_width = ev->width;
		view->natural_height = ev->height;
		container_floating_resize_and_center(view->container);

		configure(view, view->container->content_x,
				view->container->content_y,
				view->container->content_width,
				view->container->content_height);
		node_set_dirty(&view->container->node);
	} else {
		configure(view, view->container->current.content_x,
				view->container->current.content_y,
				view->container->current.content_width,
				view->container->current.content_height);
	}
}