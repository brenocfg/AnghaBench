#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* floating; } ;
struct sway_workspace {TYPE_5__ current; } ;
struct TYPE_9__ {TYPE_2__* workspaces; } ;
struct sway_output {TYPE_3__ current; } ;
struct sway_container {scalar_t__ fullscreen_mode; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_12__ {TYPE_1__* outputs; } ;
struct TYPE_10__ {int length; struct sway_container** items; } ;
struct TYPE_8__ {int length; struct sway_workspace** items; } ;
struct TYPE_7__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 scalar_t__ FULLSCREEN_NONE ; 
 int /*<<< orphan*/  render_floating_container (struct sway_output*,int /*<<< orphan*/ *,struct sway_container*) ; 
 TYPE_6__* root ; 
 int /*<<< orphan*/  workspace_is_visible (struct sway_workspace*) ; 

__attribute__((used)) static void render_floating(struct sway_output *soutput,
		pixman_region32_t *damage) {
	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		for (int j = 0; j < output->current.workspaces->length; ++j) {
			struct sway_workspace *ws = output->current.workspaces->items[j];
			if (!workspace_is_visible(ws)) {
				continue;
			}
			for (int k = 0; k < ws->current.floating->length; ++k) {
				struct sway_container *floater = ws->current.floating->items[k];
				if (floater->fullscreen_mode != FULLSCREEN_NONE) {
					continue;
				}
				render_floating_container(soutput, damage, floater);
			}
		}
	}
}