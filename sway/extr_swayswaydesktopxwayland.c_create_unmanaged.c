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
struct TYPE_3__ {int /*<<< orphan*/  destroy; int /*<<< orphan*/  unmap; int /*<<< orphan*/  map; int /*<<< orphan*/  request_configure; } ;
struct wlr_xwayland_surface {TYPE_1__ events; } ;
struct TYPE_4__ {int /*<<< orphan*/  notify; } ;
struct sway_xwayland_unmanaged {TYPE_2__ destroy; TYPE_2__ unmap; TYPE_2__ map; TYPE_2__ request_configure; struct wlr_xwayland_surface* wlr_xwayland_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct sway_xwayland_unmanaged* calloc (int,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unmanaged_handle_destroy ; 
 int /*<<< orphan*/  unmanaged_handle_map ; 
 int /*<<< orphan*/  unmanaged_handle_request_configure ; 
 int /*<<< orphan*/  unmanaged_handle_unmap ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static struct sway_xwayland_unmanaged *create_unmanaged(
		struct wlr_xwayland_surface *xsurface) {
	struct sway_xwayland_unmanaged *surface =
		calloc(1, sizeof(struct sway_xwayland_unmanaged));
	if (surface == NULL) {
		sway_log(SWAY_ERROR, "Allocation failed");
		return NULL;
	}

	surface->wlr_xwayland_surface = xsurface;

	wl_signal_add(&xsurface->events.request_configure,
		&surface->request_configure);
	surface->request_configure.notify = unmanaged_handle_request_configure;
	wl_signal_add(&xsurface->events.map, &surface->map);
	surface->map.notify = unmanaged_handle_map;
	wl_signal_add(&xsurface->events.unmap, &surface->unmap);
	surface->unmap.notify = unmanaged_handle_unmap;
	wl_signal_add(&xsurface->events.destroy, &surface->destroy);
	surface->destroy.notify = unmanaged_handle_destroy;

	return surface;
}