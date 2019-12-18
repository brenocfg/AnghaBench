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
struct sway_workspace {TYPE_2__* workspaces; struct sway_workspace* output; } ;
struct sway_output {TYPE_2__* workspaces; struct sway_output* output; } ;
struct TYPE_4__ {int length; struct sway_workspace** items; } ;
struct TYPE_3__ {TYPE_2__* outputs; } ;

/* Variables and functions */
 int list_find (TYPE_2__*,struct sway_workspace*) ; 
 TYPE_1__* root ; 
 int wrap (int,int) ; 

__attribute__((used)) static struct sway_workspace *workspace_prev_next_impl(
		struct sway_workspace *workspace, int dir) {
	struct sway_output *output = workspace->output;
	int index = list_find(output->workspaces, workspace);
	int new_index = index + dir;

	if (new_index >= 0 && new_index < output->workspaces->length) {
		return output->workspaces->items[new_index];
	}

	// Look on a different output
	int output_index = list_find(root->outputs, output);
	new_index = wrap(output_index + dir, root->outputs->length);
	output = root->outputs->items[new_index];

	if (dir == 1) {
		return output->workspaces->items[0];
	} else {
		return output->workspaces->items[output->workspaces->length - 1];
	}
}