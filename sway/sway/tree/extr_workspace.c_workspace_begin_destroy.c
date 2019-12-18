#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  destroy; } ;
struct TYPE_5__ {int destroying; TYPE_1__ events; } ;
struct sway_workspace {TYPE_2__ node; scalar_t__ output; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  ipc_event_workspace (int /*<<< orphan*/ *,struct sway_workspace*,char*) ; 
 int /*<<< orphan*/  node_set_dirty (TYPE_2__*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_signal_emit (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  workspace_detach (struct sway_workspace*) ; 

void workspace_begin_destroy(struct sway_workspace *workspace) {
	sway_log(SWAY_DEBUG, "Destroying workspace '%s'", workspace->name);
	ipc_event_workspace(NULL, workspace, "empty"); // intentional
	wl_signal_emit(&workspace->node.events.destroy, &workspace->node);

	if (workspace->output) {
		workspace_detach(workspace);
	}
	workspace->node.destroying = true;
	node_set_dirty(&workspace->node);
}