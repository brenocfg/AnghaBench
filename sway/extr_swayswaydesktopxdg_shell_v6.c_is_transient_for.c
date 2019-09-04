#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wlr_xdg_surface_v6 {scalar_t__ role; TYPE_1__* toplevel; } ;
struct sway_view {struct wlr_xdg_surface_v6* wlr_xdg_surface_v6; } ;
struct TYPE_2__ {struct wlr_xdg_surface_v6* parent; } ;

/* Variables and functions */
 scalar_t__ WLR_XDG_SURFACE_V6_ROLE_TOPLEVEL ; 
 int /*<<< orphan*/ * xdg_shell_v6_view_from_view (struct sway_view*) ; 

__attribute__((used)) static bool is_transient_for(struct sway_view *child,
		struct sway_view *ancestor) {
	if (xdg_shell_v6_view_from_view(child) == NULL) {
		return false;
	}
	struct wlr_xdg_surface_v6 *surface = child->wlr_xdg_surface_v6;
	while (surface && surface->role == WLR_XDG_SURFACE_V6_ROLE_TOPLEVEL) {
		if (surface->toplevel->parent == ancestor->wlr_xdg_surface_v6) {
			return true;
		}
		surface = surface->toplevel->parent;
	}
	return false;
}