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
struct sway_container {int /*<<< orphan*/  workspace; scalar_t__ parent; int /*<<< orphan*/  height_fraction; int /*<<< orphan*/  width_fraction; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_insert_child (scalar_t__,struct sway_container*,int) ; 
 int container_is_floating (struct sway_container*) ; 
 int container_sibling_index (struct sway_container*) ; 
 int /*<<< orphan*/  free (struct sway_container*) ; 
 struct sway_container* malloc (int) ; 
 int /*<<< orphan*/  workspace_add_floating (int /*<<< orphan*/ ,struct sway_container*) ; 
 int /*<<< orphan*/  workspace_insert_tiling (int /*<<< orphan*/ ,struct sway_container*,int) ; 

__attribute__((used)) static void swap_places(struct sway_container *con1,
		struct sway_container *con2) {
	struct sway_container *temp = malloc(sizeof(struct sway_container));
	temp->x = con1->x;
	temp->y = con1->y;
	temp->width = con1->width;
	temp->height = con1->height;
	temp->width_fraction = con1->width_fraction;
	temp->height_fraction = con1->height_fraction;
	temp->parent = con1->parent;
	temp->workspace = con1->workspace;
	bool temp_floating = container_is_floating(con1);

	con1->x = con2->x;
	con1->y = con2->y;
	con1->width = con2->width;
	con1->height = con2->height;
	con1->width_fraction = con2->width_fraction;
	con1->height_fraction = con2->height_fraction;

	con2->x = temp->x;
	con2->y = temp->y;
	con2->width = temp->width;
	con2->height = temp->height;
	con2->width_fraction = temp->width_fraction;
	con2->height_fraction = temp->height_fraction;

	int temp_index = container_sibling_index(con1);
	if (con2->parent) {
		container_insert_child(con2->parent, con1,
				container_sibling_index(con2));
	} else if (container_is_floating(con2)) {
		workspace_add_floating(con2->workspace, con1);
	} else {
		workspace_insert_tiling(con2->workspace, con1,
				container_sibling_index(con2));
	}
	if (temp->parent) {
		container_insert_child(temp->parent, con2, temp_index);
	} else if (temp_floating) {
		workspace_add_floating(temp->workspace, con2);
	} else {
		workspace_insert_tiling(temp->workspace, con2, temp_index);
	}

	free(temp);
}