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
struct wlr_box {double width; double height; } ;
struct sway_container {double width; double height; double content_width; double content_height; int /*<<< orphan*/  view; int /*<<< orphan*/  workspace; } ;

/* Variables and functions */
 struct wlr_box* calloc (int,int) ; 
 int /*<<< orphan*/  container_set_geometry_from_content (struct sway_container*) ; 
 int /*<<< orphan*/  floating_calculate_constraints (int*,int*,int*,int*) ; 
 double fmax (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmin (double,int) ; 
 int /*<<< orphan*/  free (struct wlr_box*) ; 
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  workspace_get_box (int /*<<< orphan*/ ,struct wlr_box*) ; 

void container_floating_set_default_size(struct sway_container *con) {
	if (!sway_assert(con->workspace, "Expected a container on a workspace")) {
		return;
	}

	int min_width, max_width, min_height, max_height;
	floating_calculate_constraints(&min_width, &max_width,
			&min_height, &max_height);
	struct wlr_box *box = calloc(1, sizeof(struct wlr_box));
	workspace_get_box(con->workspace, box);

	double width = fmax(min_width, fmin(box->width * 0.5, max_width));
	double height = fmax(min_height, fmin(box->height * 0.75, max_height));
	if (!con->view) {
		con->width = width;
		con->height = height;
	} else {
		con->content_width = width;
		con->content_height = height;
		container_set_geometry_from_content(con);
	}

	free(box);
}