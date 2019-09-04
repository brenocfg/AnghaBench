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
struct sway_container {int /*<<< orphan*/  workspace; scalar_t__ parent; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_insert_child (scalar_t__,struct sway_container*,int) ; 
 int container_sibling_index (struct sway_container*) ; 
 int /*<<< orphan*/  free (struct sway_container*) ; 
 struct sway_container* malloc (int) ; 
 int /*<<< orphan*/  workspace_insert_tiling (int /*<<< orphan*/ ,struct sway_container*,int) ; 

__attribute__((used)) static void swap_places(struct sway_container *con1,
		struct sway_container *con2) {
	struct sway_container *temp = malloc(sizeof(struct sway_container));
	temp->x = con1->x;
	temp->y = con1->y;
	temp->width = con1->width;
	temp->height = con1->height;
	temp->parent = con1->parent;
	temp->workspace = con1->workspace;

	con1->x = con2->x;
	con1->y = con2->y;
	con1->width = con2->width;
	con1->height = con2->height;

	con2->x = temp->x;
	con2->y = temp->y;
	con2->width = temp->width;
	con2->height = temp->height;

	int temp_index = container_sibling_index(con1);
	if (con2->parent) {
		container_insert_child(con2->parent, con1,
				container_sibling_index(con2));
	} else {
		workspace_insert_tiling(con2->workspace, con1,
				container_sibling_index(con2));
	}
	if (temp->parent) {
		container_insert_child(temp->parent, con2, temp_index);
	} else {
		workspace_insert_tiling(temp->workspace, con2, temp_index);
	}

	free(temp);
}