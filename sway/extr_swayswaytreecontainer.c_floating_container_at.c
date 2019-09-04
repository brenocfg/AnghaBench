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
struct wlr_box {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_workspace {TYPE_3__* floating; } ;
struct sway_output {TYPE_2__* workspaces; } ;
struct sway_container {int /*<<< orphan*/  node; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {TYPE_1__* outputs; } ;
struct TYPE_7__ {int length; struct sway_container** items; } ;
struct TYPE_6__ {int length; struct sway_workspace** items; } ;
struct TYPE_5__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 TYPE_4__* root ; 
 struct sway_container* tiling_container_at (int /*<<< orphan*/ *,double,double,struct wlr_surface**,double*,double*) ; 
 scalar_t__ wlr_box_contains_point (struct wlr_box*,double,double) ; 
 int /*<<< orphan*/  workspace_is_visible (struct sway_workspace*) ; 

__attribute__((used)) static struct sway_container *floating_container_at(double lx, double ly,
		struct wlr_surface **surface, double *sx, double *sy) {
	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		for (int j = 0; j < output->workspaces->length; ++j) {
			struct sway_workspace *ws = output->workspaces->items[j];
			if (!workspace_is_visible(ws)) {
				continue;
			}
			// Items at the end of the list are on top, so iterate the list in
			// reverse.
			for (int k = ws->floating->length - 1; k >= 0; --k) {
				struct sway_container *floater = ws->floating->items[k];
				struct wlr_box box = {
					.x = floater->x,
					.y = floater->y,
					.width = floater->width,
					.height = floater->height,
				};
				if (wlr_box_contains_point(&box, lx, ly)) {
					return tiling_container_at(&floater->node, lx, ly,
							surface, sx, sy);
				}
			}
		}
	}
	return NULL;
}