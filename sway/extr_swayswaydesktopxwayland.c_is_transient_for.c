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
struct wlr_xwayland_surface {struct wlr_xwayland_surface* parent; } ;
struct sway_view {struct wlr_xwayland_surface* wlr_xwayland_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xwayland_view_from_view (struct sway_view*) ; 

__attribute__((used)) static bool is_transient_for(struct sway_view *child,
		struct sway_view *ancestor) {
	if (xwayland_view_from_view(child) == NULL) {
		return false;
	}
	struct wlr_xwayland_surface *surface = child->wlr_xwayland_surface;
	while (surface) {
		if (surface->parent == ancestor->wlr_xwayland_surface) {
			return true;
		}
		surface = surface->parent;
	}
	return false;
}