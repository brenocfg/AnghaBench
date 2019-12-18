#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wl_listener {int dummy; } ;
struct wl_client {int dummy; } ;
struct sway_seat {struct wl_client* exclusive_client; } ;
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
struct sway_layer_surface {TYPE_2__* layer_surface; int /*<<< orphan*/  link; TYPE_1__ output_destroy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * output; int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 struct sway_layer_surface* find_any_layer_by_client (struct wl_client*,int /*<<< orphan*/ *) ; 
 struct sway_seat* input_manager_get_default_seat () ; 
 int /*<<< orphan*/  output_destroy ; 
 int /*<<< orphan*/  seat_set_focus_layer (struct sway_seat*,TYPE_2__*) ; 
 struct sway_layer_surface* sway_layer ; 
 struct sway_layer_surface* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 struct wl_client* wl_resource_get_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_layer_surface_v1_close (TYPE_2__*) ; 

__attribute__((used)) static void handle_output_destroy(struct wl_listener *listener, void *data) {
	struct sway_layer_surface *sway_layer =
		wl_container_of(listener, sway_layer, output_destroy);
	// Determine if this layer is being used by an exclusive client. If it is,
	// try and find another layer owned by this client to pass focus to.
	struct sway_seat *seat = input_manager_get_default_seat();
	struct wl_client *client =
		wl_resource_get_client(sway_layer->layer_surface->resource);
	bool set_focus = seat->exclusive_client == client;

	wl_list_remove(&sway_layer->output_destroy.link);
	wl_list_remove(&sway_layer->link);
	wl_list_init(&sway_layer->link);

	if (set_focus) {
		struct sway_layer_surface *layer =
			find_any_layer_by_client(client, sway_layer->layer_surface->output);
		if (layer) {
			seat_set_focus_layer(seat, layer->layer_surface);
		}
	}

	sway_layer->layer_surface->output = NULL;
	wlr_layer_surface_v1_close(sway_layer->layer_surface);
}