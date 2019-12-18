#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {TYPE_6__* floating; } ;
struct sway_output {scalar_t__ width; scalar_t__ height; scalar_t__ lx; scalar_t__ ly; TYPE_3__* wlr_output; TYPE_2__* workspaces; } ;
struct sway_container {scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; } ;
struct TYPE_14__ {TYPE_5__* noop_output; TYPE_1__* outputs; } ;
struct TYPE_13__ {int length; struct sway_container** items; } ;
struct TYPE_12__ {TYPE_4__* workspaces; } ;
struct TYPE_11__ {struct sway_workspace** items; scalar_t__ length; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int length; struct sway_workspace** items; } ;
struct TYPE_8__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_floating_resize_and_center (struct sway_container*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ipc_event_workspace (int /*<<< orphan*/ *,struct sway_workspace*,char*) ; 
 int /*<<< orphan*/  output_add_workspace (struct sway_output*,struct sway_workspace*) ; 
 int /*<<< orphan*/  output_sort_workspaces (struct sway_output*) ; 
 TYPE_7__* root ; 
 struct sway_workspace* workspace_create (struct sway_output*,char*) ; 
 int /*<<< orphan*/  workspace_detach (struct sway_workspace*) ; 
 char* workspace_next_name (int /*<<< orphan*/ ) ; 
 struct sway_output* workspace_output_get_highest_available (struct sway_workspace*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void restore_workspaces(struct sway_output *output) {
	// Workspace output priority
	for (int i = 0; i < root->outputs->length; i++) {
		struct sway_output *other = root->outputs->items[i];
		if (other == output) {
			continue;
		}

		for (int j = 0; j < other->workspaces->length; j++) {
			struct sway_workspace *ws = other->workspaces->items[j];
			struct sway_output *highest =
				workspace_output_get_highest_available(ws, NULL);
			if (highest == output) {
				workspace_detach(ws);
				output_add_workspace(output, ws);
				ipc_event_workspace(NULL, ws, "move");
				j--;
			}
		}

		if (other->workspaces->length == 0) {
			char *next = workspace_next_name(other->wlr_output->name);
			struct sway_workspace *ws = workspace_create(other, next);
			free(next);
			ipc_event_workspace(NULL, ws, "init");
		}
	}

	// Saved workspaces
	while (root->noop_output->workspaces->length) {
		struct sway_workspace *ws = root->noop_output->workspaces->items[0];
		workspace_detach(ws);
		output_add_workspace(output, ws);

		// If the floater was made floating while on the NOOP output, its width
		// and height will be zero and it should be reinitialized as a floating
		// container to get the appropriate size and location. Additionally, if
		// the floater is wider or taller than the output or is completely
		// outside of the output's bounds, do the same as the output layout has
		// likely changed and the maximum size needs to be checked and the
		// floater re-centered
		for (int i = 0; i < ws->floating->length; i++) {
			struct sway_container *floater = ws->floating->items[i];
			if (floater->width == 0 || floater->height == 0 ||
					floater->width > output->width ||
					floater->height > output->height ||
					floater->x > output->lx + output->width ||
					floater->y > output->ly + output->height ||
					floater->x + floater->width < output->lx ||
					floater->y + floater->height < output->ly) {
				container_floating_resize_and_center(floater);
			}
		}

		ipc_event_workspace(NULL, ws, "move");
	}

	output_sort_workspaces(output);
}