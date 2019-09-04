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
struct sway_workspace {int /*<<< orphan*/  node; int /*<<< orphan*/  floating; } ;
struct sway_container {int /*<<< orphan*/  node; struct sway_workspace* workspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_detach (struct sway_container*) ; 
 int /*<<< orphan*/  container_for_each_child (struct sway_container*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  container_handle_fullscreen_reparent (struct sway_container*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct sway_container*) ; 
 int /*<<< orphan*/  node_set_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_workspace ; 

void workspace_add_floating(struct sway_workspace *workspace,
		struct sway_container *con) {
	if (con->workspace) {
		container_detach(con);
	}
	list_add(workspace->floating, con);
	con->workspace = workspace;
	container_for_each_child(con, set_workspace, NULL);
	container_handle_fullscreen_reparent(con);
	node_set_dirty(&workspace->node);
	node_set_dirty(&con->node);
}