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
struct TYPE_3__ {int /*<<< orphan*/  tiling; int /*<<< orphan*/  floating; } ;
struct TYPE_4__ {int destroying; scalar_t__ ntxnrefs; } ;
struct sway_workspace {TYPE_1__ current; int /*<<< orphan*/  tiling; int /*<<< orphan*/  floating; int /*<<< orphan*/  output_priority; struct sway_workspace* representation; struct sway_workspace* name; TYPE_2__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_workspace*) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

void workspace_destroy(struct sway_workspace *workspace) {
	if (!sway_assert(workspace->node.destroying,
				"Tried to free workspace which wasn't marked as destroying")) {
		return;
	}
	if (!sway_assert(workspace->node.ntxnrefs == 0, "Tried to free workspace "
				"which is still referenced by transactions")) {
		return;
	}

	free(workspace->name);
	free(workspace->representation);
	list_free_items_and_destroy(workspace->output_priority);
	list_free(workspace->floating);
	list_free(workspace->tiling);
	list_free(workspace->current.floating);
	list_free(workspace->current.tiling);
	free(workspace);
}