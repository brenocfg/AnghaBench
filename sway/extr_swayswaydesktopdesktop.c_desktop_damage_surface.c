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
struct wlr_surface {int dummy; } ;
struct wlr_box {scalar_t__ y; scalar_t__ x; } ;
struct sway_output {int /*<<< orphan*/  wlr_output; } ;
struct TYPE_4__ {int /*<<< orphan*/  output_layout; TYPE_1__* outputs; } ;
struct TYPE_3__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  output_damage_surface (struct sway_output*,scalar_t__,scalar_t__,struct wlr_surface*,int) ; 
 TYPE_2__* root ; 
 struct wlr_box* wlr_output_layout_get_box (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void desktop_damage_surface(struct wlr_surface *surface, double lx, double ly,
		bool whole) {
	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		struct wlr_box *output_box = wlr_output_layout_get_box(
			root->output_layout, output->wlr_output);
		output_damage_surface(output, lx - output_box->x,
			ly - output_box->y, surface, whole);
	}
}