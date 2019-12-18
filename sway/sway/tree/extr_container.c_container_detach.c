#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int /*<<< orphan*/  node; int /*<<< orphan*/ * fullscreen; } ;
struct sway_container {scalar_t__ fullscreen_mode; int /*<<< orphan*/  node; struct sway_workspace* workspace; struct sway_container* parent; } ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_2__ {int /*<<< orphan*/ * fullscreen_global; } ;

/* Variables and functions */
 scalar_t__ FULLSCREEN_GLOBAL ; 
 scalar_t__ FULLSCREEN_WORKSPACE ; 
 int /*<<< orphan*/  container_for_each_child (struct sway_container*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * container_get_siblings (struct sway_container*) ; 
 int /*<<< orphan*/  container_update_representation (struct sway_container*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *,int) ; 
 int list_find (int /*<<< orphan*/ *,struct sway_container*) ; 
 int /*<<< orphan*/  node_set_dirty (int /*<<< orphan*/ *) ; 
 TYPE_1__* root ; 
 int /*<<< orphan*/  set_workspace ; 
 int /*<<< orphan*/  workspace_update_representation (struct sway_workspace*) ; 

void container_detach(struct sway_container *child) {
	if (child->fullscreen_mode == FULLSCREEN_WORKSPACE) {
		child->workspace->fullscreen = NULL;
	}
	if (child->fullscreen_mode == FULLSCREEN_GLOBAL) {
		root->fullscreen_global = NULL;
	}

	struct sway_container *old_parent = child->parent;
	struct sway_workspace *old_workspace = child->workspace;
	list_t *siblings = container_get_siblings(child);
	if (siblings) {
		int index = list_find(siblings, child);
		if (index != -1) {
			list_del(siblings, index);
		}
	}
	child->parent = NULL;
	child->workspace = NULL;
	container_for_each_child(child, set_workspace, NULL);

	if (old_parent) {
		container_update_representation(old_parent);
		node_set_dirty(&old_parent->node);
	} else if (old_workspace) {
		workspace_update_representation(old_workspace);
		node_set_dirty(&old_workspace->node);
	}
	node_set_dirty(&child->node);
}