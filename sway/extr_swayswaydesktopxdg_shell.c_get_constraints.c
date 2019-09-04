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
struct wlr_xdg_toplevel_state {double min_width; double max_width; double min_height; double max_height; } ;
struct sway_view {TYPE_2__* wlr_xdg_surface; } ;
struct TYPE_4__ {TYPE_1__* toplevel; } ;
struct TYPE_3__ {struct wlr_xdg_toplevel_state current; } ;

/* Variables and functions */
 double DBL_MAX ; 
 double DBL_MIN ; 

__attribute__((used)) static void get_constraints(struct sway_view *view, double *min_width,
		double *max_width, double *min_height, double *max_height) {
	struct wlr_xdg_toplevel_state *state =
		&view->wlr_xdg_surface->toplevel->current;
	*min_width = state->min_width > 0 ? state->min_width : DBL_MIN;
	*max_width = state->max_width > 0 ? state->max_width : DBL_MAX;
	*min_height = state->min_height > 0 ? state->min_height : DBL_MIN;
	*max_height = state->max_height > 0 ? state->max_height : DBL_MAX;
}