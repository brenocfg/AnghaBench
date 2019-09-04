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
struct wlr_surface {int dummy; } ;
struct sway_workspace {int /*<<< orphan*/  node; } ;
struct sway_seat {int dummy; } ;
struct sway_container {scalar_t__ view; } ;

/* Variables and functions */
 scalar_t__ container_is_floating_or_child (struct sway_container*) ; 
 struct sway_container* floating_container_at (double,double,struct wlr_surface**,double*,double*) ; 
 struct sway_seat* input_manager_current_seat () ; 
 struct sway_container* seat_get_focused_container (struct sway_seat*) ; 
 struct sway_container* surface_at_view (struct sway_container*,double,double,struct wlr_surface**,double*,double*) ; 
 scalar_t__ surface_is_popup (struct wlr_surface*) ; 
 struct sway_container* tiling_container_at (int /*<<< orphan*/ *,double,double,struct wlr_surface**,double*,double*) ; 

struct sway_container *container_at(struct sway_workspace *workspace,
		double lx, double ly,
		struct wlr_surface **surface, double *sx, double *sy) {
	struct sway_container *c;

	struct sway_seat *seat = input_manager_current_seat();
	struct sway_container *focus = seat_get_focused_container(seat);
	bool is_floating = focus && container_is_floating_or_child(focus);
	// Focused view's popups
	if (focus && focus->view) {
		c = surface_at_view(focus, lx, ly, surface, sx, sy);
		if (c && surface_is_popup(*surface)) {
			return c;
		}
		*surface = NULL;
	}
	// Floating
	if ((c = floating_container_at(lx, ly, surface ,sx ,sy))) {
		return c;
	}
	// Tiling (focused)
	if (focus && focus->view && !is_floating) {
		if ((c = surface_at_view(focus, lx, ly, surface, sx, sy))) {
			return c;
		}
	}
	// Tiling (non-focused)
	if ((c = tiling_container_at(&workspace->node, lx, ly, surface, sx, sy))) {
		return c;
	}
	return NULL;
}