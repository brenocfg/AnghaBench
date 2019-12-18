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
struct sway_container {scalar_t__ workspace; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_for_each_child (struct sway_container*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * container_get_siblings (struct sway_container*) ; 
 int /*<<< orphan*/  container_handle_fullscreen_reparent (struct sway_container*) ; 
 int /*<<< orphan*/  container_update_representation (struct sway_container*) ; 
 int list_find (int /*<<< orphan*/ *,struct sway_container*) ; 
 int /*<<< orphan*/  list_insert (int /*<<< orphan*/ *,int,struct sway_container*) ; 
 int /*<<< orphan*/  set_workspace ; 

void container_add_sibling(struct sway_container *fixed,
		struct sway_container *active, bool after) {
	if (active->workspace) {
		container_detach(active);
	}
	list_t *siblings = container_get_siblings(fixed);
	int index = list_find(siblings, fixed);
	list_insert(siblings, index + after, active);
	active->parent = fixed->parent;
	active->workspace = fixed->workspace;
	container_for_each_child(active, set_workspace, NULL);
	container_handle_fullscreen_reparent(active);
	container_update_representation(active);
}