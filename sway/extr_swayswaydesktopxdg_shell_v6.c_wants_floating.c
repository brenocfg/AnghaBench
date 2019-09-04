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
struct wlr_xdg_toplevel_v6_state {scalar_t__ min_width; scalar_t__ min_height; scalar_t__ max_width; scalar_t__ max_height; } ;
struct wlr_xdg_toplevel_v6 {scalar_t__ parent; struct wlr_xdg_toplevel_v6_state current; } ;
struct sway_view {TYPE_1__* wlr_xdg_surface_v6; } ;
struct TYPE_2__ {struct wlr_xdg_toplevel_v6* toplevel; } ;

/* Variables and functions */

__attribute__((used)) static bool wants_floating(struct sway_view *view) {
	struct wlr_xdg_toplevel_v6 *toplevel =
		view->wlr_xdg_surface_v6->toplevel;
	struct wlr_xdg_toplevel_v6_state *state = &toplevel->current;
	return (state->min_width != 0 && state->min_height != 0
		&& (state->min_width == state->max_width
		|| state->min_height == state->max_height))
		|| toplevel->parent;
}