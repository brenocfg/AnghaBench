#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wlr_output {int dummy; } ;
struct wl_listener {int dummy; } ;
struct sway_layer_surface {TYPE_1__* layer_surface; } ;
struct sway_layer_popup {TYPE_3__* wlr_popup; } ;
struct TYPE_6__ {TYPE_2__* base; } ;
struct TYPE_5__ {int /*<<< orphan*/  surface; } ;
struct TYPE_4__ {struct wlr_output* output; } ;

/* Variables and functions */
 int /*<<< orphan*/  map ; 
 struct sway_layer_popup* popup ; 
 int /*<<< orphan*/  popup_damage (struct sway_layer_popup*,int) ; 
 struct sway_layer_surface* popup_get_layer (struct sway_layer_popup*) ; 
 struct sway_layer_popup* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_surface_send_enter (int /*<<< orphan*/ ,struct wlr_output*) ; 

__attribute__((used)) static void popup_handle_map(struct wl_listener *listener, void *data) {
	struct sway_layer_popup *popup = wl_container_of(listener, popup, map);
	struct sway_layer_surface *layer = popup_get_layer(popup);
	struct wlr_output *wlr_output = layer->layer_surface->output;
	wlr_surface_send_enter(popup->wlr_popup->base->surface, wlr_output);
	popup_damage(popup, true);
}