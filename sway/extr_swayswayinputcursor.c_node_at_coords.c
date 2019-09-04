#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wlr_surface {int dummy; } ;
struct wlr_output {struct sway_output* data; } ;
struct sway_node {int dummy; } ;
struct sway_workspace {struct sway_node node; TYPE_4__* fullscreen; TYPE_2__* floating; } ;
struct sway_seat {int dummy; } ;
struct sway_output {int /*<<< orphan*/ * layers; int /*<<< orphan*/  configured; } ;
struct sway_container {struct sway_node node; } ;
struct TYPE_8__ {struct sway_node node; } ;
struct TYPE_7__ {TYPE_1__* fullscreen_global; int /*<<< orphan*/  output_layout; } ;
struct TYPE_6__ {int length; struct sway_container** items; } ;
struct TYPE_5__ {struct sway_node node; } ;

/* Variables and functions */
 size_t ZWLR_LAYER_SHELL_V1_LAYER_BACKGROUND ; 
 size_t ZWLR_LAYER_SHELL_V1_LAYER_BOTTOM ; 
 size_t ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY ; 
 size_t ZWLR_LAYER_SHELL_V1_LAYER_TOP ; 
 struct sway_container* container_at (struct sway_workspace*,double,double,struct wlr_surface**,double*,double*) ; 
 scalar_t__ container_is_transient_for (struct sway_container*,TYPE_4__*) ; 
 struct wlr_surface* layer_surface_at (struct sway_output*,int /*<<< orphan*/ *,double,double,double*,double*) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 TYPE_3__* root ; 
 struct sway_container* tiling_container_at (struct sway_node*,double,double,struct wlr_surface**,double*,double*) ; 
 struct wlr_output* wlr_output_layout_output_at (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  wlr_output_layout_output_coords (int /*<<< orphan*/ ,struct wlr_output*,double*,double*) ; 

struct sway_node *node_at_coords(
		struct sway_seat *seat, double lx, double ly,
		struct wlr_surface **surface, double *sx, double *sy) {
	// check for unmanaged views first
#if HAVE_XWAYLAND
	struct wl_list *unmanaged = &root->xwayland_unmanaged;
	struct sway_xwayland_unmanaged *unmanaged_surface;
	wl_list_for_each_reverse(unmanaged_surface, unmanaged, link) {
		struct wlr_xwayland_surface *xsurface =
			unmanaged_surface->wlr_xwayland_surface;

		double _sx = lx - unmanaged_surface->lx;
		double _sy = ly - unmanaged_surface->ly;
		if (wlr_surface_point_accepts_input(xsurface->surface, _sx, _sy)) {
			*surface = xsurface->surface;
			*sx = _sx;
			*sy = _sy;
			return NULL;
		}
	}
#endif
	// find the output the cursor is on
	struct wlr_output *wlr_output = wlr_output_layout_output_at(
			root->output_layout, lx, ly);
	if (wlr_output == NULL) {
		return NULL;
	}
	struct sway_output *output = wlr_output->data;
	if (!output || !output->configured) {
		// output is being destroyed or is being configured
		return NULL;
	}
	double ox = lx, oy = ly;
	wlr_output_layout_output_coords(root->output_layout, wlr_output, &ox, &oy);

	if (root->fullscreen_global) {
		// Try fullscreen container
		struct sway_container *con = tiling_container_at(
				&root->fullscreen_global->node, lx, ly, surface, sx, sy);
		if (con) {
			return &con->node;
		}
		return NULL;
	}

	// find the focused workspace on the output for this seat
	struct sway_workspace *ws = output_get_active_workspace(output);
	if (!ws) {
		return NULL;
	}

	if ((*surface = layer_surface_at(output,
				&output->layers[ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY],
				ox, oy, sx, sy))) {
		return NULL;
	}
	if (ws->fullscreen) {
		// Try transient containers
		for (int i = 0; i < ws->floating->length; ++i) {
			struct sway_container *floater = ws->floating->items[i];
			if (container_is_transient_for(floater, ws->fullscreen)) {
				struct sway_container *con = tiling_container_at(
						&floater->node, lx, ly, surface, sx, sy);
				if (con) {
					return &con->node;
				}
			}
		}
		// Try fullscreen container
		struct sway_container *con =
			tiling_container_at(&ws->fullscreen->node, lx, ly, surface, sx, sy);
		if (con) {
			return &con->node;
		}
		return NULL;
	}
	if ((*surface = layer_surface_at(output,
				&output->layers[ZWLR_LAYER_SHELL_V1_LAYER_TOP],
				ox, oy, sx, sy))) {
		return NULL;
	}

	struct sway_container *c;
	if ((c = container_at(ws, lx, ly, surface, sx, sy))) {
		return &c->node;
	}

	if ((*surface = layer_surface_at(output,
				&output->layers[ZWLR_LAYER_SHELL_V1_LAYER_BOTTOM],
				ox, oy, sx, sy))) {
		return NULL;
	}
	if ((*surface = layer_surface_at(output,
				&output->layers[ZWLR_LAYER_SHELL_V1_LAYER_BACKGROUND],
				ox, oy, sx, sy))) {
		return NULL;
	}

	return &ws->node;
}