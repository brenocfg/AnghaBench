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
struct wlr_xdg_popup {int dummy; } ;
struct wlr_box {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_output {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_layer_surface {TYPE_3__ geo; TYPE_2__* layer_surface; } ;
struct sway_layer_popup {struct wlr_xdg_popup* wlr_popup; } ;
struct TYPE_5__ {TYPE_1__* output; } ;
struct TYPE_4__ {struct sway_output* data; } ;

/* Variables and functions */
 struct sway_layer_surface* popup_get_layer (struct sway_layer_popup*) ; 
 int /*<<< orphan*/  wlr_xdg_popup_unconstrain_from_box (struct wlr_xdg_popup*,struct wlr_box*) ; 

__attribute__((used)) static void popup_unconstrain(struct sway_layer_popup *popup) {
	struct sway_layer_surface *layer = popup_get_layer(popup);
	struct wlr_xdg_popup *wlr_popup = popup->wlr_popup;

	struct sway_output *output = layer->layer_surface->output->data;

	// the output box expressed in the coordinate system of the toplevel parent
	// of the popup
	struct wlr_box output_toplevel_sx_box = {
		.x = -layer->geo.x,
		.y = -layer->geo.y,
		.width = output->width,
		.height = output->height,
	};

	wlr_xdg_popup_unconstrain_from_box(wlr_popup, &output_toplevel_sx_box);
}