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
struct sway_container {scalar_t__ fullscreen_mode; int /*<<< orphan*/  node; scalar_t__ workspace; struct sway_container* parent; int /*<<< orphan*/  children; } ;

/* Variables and functions */
 scalar_t__ FULLSCREEN_NONE ; 
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_for_each_child (struct sway_container*,int /*<<< orphan*/  (*) (struct sway_container*,int*),int*) ; 
 int /*<<< orphan*/  container_handle_fullscreen_reparent (struct sway_container*) ; 
 int /*<<< orphan*/  container_update_representation (struct sway_container*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct sway_container*) ; 
 int /*<<< orphan*/  node_set_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_fullscreen_iterator (struct sway_container*,int*) ; 
 int /*<<< orphan*/  set_workspace (struct sway_container*,int*) ; 

void container_add_child(struct sway_container *parent,
		struct sway_container *child) {
	if (child->workspace) {
		container_detach(child);
	}
	list_add(parent->children, child);
	child->parent = parent;
	child->workspace = parent->workspace;
	container_for_each_child(child, set_workspace, NULL);
	bool fullscreen = child->fullscreen_mode != FULLSCREEN_NONE ||
		parent->fullscreen_mode != FULLSCREEN_NONE;
	set_fullscreen_iterator(child, &fullscreen);
	container_for_each_child(child, set_fullscreen_iterator, &fullscreen);
	container_handle_fullscreen_reparent(child);
	container_update_representation(parent);
	node_set_dirty(&child->node);
	node_set_dirty(&parent->node);
}