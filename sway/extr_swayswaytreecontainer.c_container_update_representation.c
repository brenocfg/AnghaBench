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
struct sway_container {scalar_t__ workspace; struct sway_container* parent; int /*<<< orphan*/ * formatted_title; int /*<<< orphan*/  children; int /*<<< orphan*/  layout; int /*<<< orphan*/  view; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 size_t container_build_representation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  container_calculate_title_height (struct sway_container*) ; 
 int /*<<< orphan*/  container_update_title_textures (struct sway_container*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  workspace_update_representation (scalar_t__) ; 

void container_update_representation(struct sway_container *con) {
	if (!con->view) {
		size_t len = container_build_representation(con->layout,
				con->children, NULL);
		free(con->formatted_title);
		con->formatted_title = calloc(len + 1, sizeof(char));
		if (!sway_assert(con->formatted_title,
					"Unable to allocate title string")) {
			return;
		}
		container_build_representation(con->layout, con->children,
				con->formatted_title);
		container_calculate_title_height(con);
		container_update_title_textures(con);
	}
	if (con->parent) {
		container_update_representation(con->parent);
	} else if (con->workspace) {
		workspace_update_representation(con->workspace);
	}
}