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
struct wlr_box {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_workspace {int dummy; } ;
struct sway_output {TYPE_1__* workspaces; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  ly; int /*<<< orphan*/  lx; int /*<<< orphan*/  wlr_output; } ;
struct TYPE_6__ {scalar_t__ reloading; } ;
struct TYPE_5__ {int /*<<< orphan*/  output_layout; } ;
struct TYPE_4__ {int length; struct sway_workspace** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  arrange_workspace (struct sway_workspace*) ; 
 TYPE_3__* config ; 
 TYPE_2__* root ; 
 struct wlr_box* wlr_output_layout_get_box (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void arrange_output(struct sway_output *output) {
	if (config->reloading) {
		return;
	}
	const struct wlr_box *output_box = wlr_output_layout_get_box(
			root->output_layout, output->wlr_output);
	output->lx = output_box->x;
	output->ly = output_box->y;
	output->width = output_box->width;
	output->height = output_box->height;

	for (int i = 0; i < output->workspaces->length; ++i) {
		struct sway_workspace *workspace = output->workspaces->items[i];
		arrange_workspace(workspace);
	}
}