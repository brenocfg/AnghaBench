#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sway_workspace {int /*<<< orphan*/  node; struct sway_output* output; } ;
struct sway_output {int /*<<< orphan*/  node; int /*<<< orphan*/  workspaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ ,int) ; 
 int list_find (int /*<<< orphan*/ ,struct sway_workspace*) ; 
 int /*<<< orphan*/  node_set_dirty (int /*<<< orphan*/ *) ; 

void workspace_detach(struct sway_workspace *workspace) {
	struct sway_output *output = workspace->output;
	int index = list_find(output->workspaces, workspace);
	if (index != -1) {
		list_del(output->workspaces, index);
	}
	workspace->output = NULL;

	node_set_dirty(&workspace->node);
	node_set_dirty(&output->node);
}