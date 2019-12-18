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
struct sway_container {scalar_t__ workspace; struct sway_container* parent; int /*<<< orphan*/  children; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_for_each_child (struct sway_container*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  container_handle_fullscreen_reparent (struct sway_container*) ; 
 int /*<<< orphan*/  container_update_representation (struct sway_container*) ; 
 int /*<<< orphan*/  list_insert (int /*<<< orphan*/ ,int,struct sway_container*) ; 
 int /*<<< orphan*/  set_workspace ; 

void container_insert_child(struct sway_container *parent,
		struct sway_container *child, int i) {
	if (child->workspace) {
		container_detach(child);
	}
	list_insert(parent->children, i, child);
	child->parent = parent;
	child->workspace = parent->workspace;
	container_for_each_child(child, set_workspace, NULL);
	container_handle_fullscreen_reparent(child);
	container_update_representation(parent);
}