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
struct wlr_xwayland_surface_configure_event {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct wlr_xwayland_surface {int dummy; } ;
struct wl_listener {int dummy; } ;
struct sway_xwayland_unmanaged {struct wlr_xwayland_surface* wlr_xwayland_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  request_configure ; 
 struct sway_xwayland_unmanaged* surface ; 
 struct sway_xwayland_unmanaged* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_xwayland_surface_configure (struct wlr_xwayland_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmanaged_handle_request_configure(struct wl_listener *listener,
		void *data) {
	struct sway_xwayland_unmanaged *surface =
		wl_container_of(listener, surface, request_configure);
	struct wlr_xwayland_surface *xsurface = surface->wlr_xwayland_surface;
	struct wlr_xwayland_surface_configure_event *ev = data;
	wlr_xwayland_surface_configure(xsurface, ev->x, ev->y,
		ev->width, ev->height);
}