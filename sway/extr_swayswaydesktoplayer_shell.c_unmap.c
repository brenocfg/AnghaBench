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
struct wlr_output {struct sway_output* data; } ;
struct sway_seat {TYPE_2__* focused_layer; } ;
struct sway_output {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_layer_surface {TYPE_2__* layer_surface; TYPE_1__ geo; } ;
struct TYPE_4__ {int /*<<< orphan*/  surface; struct wlr_output* output; } ;

/* Variables and functions */
 int /*<<< orphan*/  cursor_rebase_all () ; 
 struct sway_seat* input_manager_current_seat () ; 
 int /*<<< orphan*/  output_damage_surface (struct sway_output*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seat_set_focus_layer (struct sway_seat*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unmap(struct sway_layer_surface *sway_layer) {
	struct wlr_output *wlr_output = sway_layer->layer_surface->output;
	if (wlr_output == NULL) {
		return;
	}
	struct sway_output *output = wlr_output->data;
	if (output == NULL) {
		return;
	}
	output_damage_surface(output, sway_layer->geo.x, sway_layer->geo.y,
		sway_layer->layer_surface->surface, true);

	struct sway_seat *seat = input_manager_current_seat();
	if (seat->focused_layer == sway_layer->layer_surface) {
		seat_set_focus_layer(seat, NULL);
	}

	cursor_rebase_all();
}