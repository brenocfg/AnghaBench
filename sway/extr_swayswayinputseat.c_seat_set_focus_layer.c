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
struct wlr_layer_surface_v1 {scalar_t__ layer; int /*<<< orphan*/  surface; } ;
struct sway_seat {struct wlr_layer_surface_v1* focused_layer; } ;
struct sway_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 scalar_t__ ZWLR_LAYER_SHELL_V1_LAYER_TOP ; 
 TYPE_1__* root ; 
 struct sway_node* seat_get_focus_inactive (struct sway_seat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,struct sway_node*) ; 
 int /*<<< orphan*/  seat_set_focus_surface (struct sway_seat*,int /*<<< orphan*/ ,int) ; 

void seat_set_focus_layer(struct sway_seat *seat,
		struct wlr_layer_surface_v1 *layer) {
	if (!layer && seat->focused_layer) {
		seat->focused_layer = NULL;
		struct sway_node *previous = seat_get_focus_inactive(seat, &root->node);
		if (previous) {
			// Hack to get seat to re-focus the return value of get_focus
			seat_set_focus(seat, NULL);
			seat_set_focus(seat, previous);
		}
		return;
	} else if (!layer || seat->focused_layer == layer) {
		return;
	}
	seat_set_focus_surface(seat, layer->surface, true);
	if (layer->layer >= ZWLR_LAYER_SHELL_V1_LAYER_TOP) {
		seat->focused_layer = layer;
	}
}