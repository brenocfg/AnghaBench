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
struct wlr_output {struct sway_output* data; } ;
struct TYPE_2__ {size_t layer; } ;
struct wlr_layer_surface_v1 {int /*<<< orphan*/  surface; TYPE_1__ current; struct wlr_output* output; } ;
struct wlr_box {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct wl_listener {int dummy; } ;
struct sway_output {int /*<<< orphan*/ * layers; } ;
struct sway_layer_surface {size_t layer; struct wlr_box geo; int /*<<< orphan*/  link; struct wlr_layer_surface_v1* layer_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  arrange_layers (struct sway_output*) ; 
 struct sway_layer_surface* layer ; 
 scalar_t__ memcmp (struct wlr_box*,struct wlr_box*,int) ; 
 int /*<<< orphan*/  output_damage_surface (struct sway_output*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  surface_commit ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_layer_surface* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_surface_commit(struct wl_listener *listener, void *data) {
	struct sway_layer_surface *layer =
		wl_container_of(listener, layer, surface_commit);
	struct wlr_layer_surface_v1 *layer_surface = layer->layer_surface;
	struct wlr_output *wlr_output = layer_surface->output;
	if (wlr_output == NULL) {
		return;
	}

	struct sway_output *output = wlr_output->data;
	struct wlr_box old_geo = layer->geo;
	arrange_layers(output);

	bool geo_changed =
		memcmp(&old_geo, &layer->geo, sizeof(struct wlr_box)) != 0;
	bool layer_changed = layer->layer != layer_surface->current.layer;
	if (layer_changed) {
		wl_list_remove(&layer->link);
		wl_list_insert(&output->layers[layer_surface->current.layer],
			&layer->link);
		layer->layer = layer_surface->current.layer;
	}
	if (geo_changed || layer_changed) {
		output_damage_surface(output, old_geo.x, old_geo.y,
			layer_surface->surface, true);
		output_damage_surface(output, layer->geo.x, layer->geo.y,
			layer_surface->surface, true);
	} else {
		output_damage_surface(output, layer->geo.x, layer->geo.y,
			layer_surface->surface, false);
	}

	transaction_commit_dirty();
}