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
struct wlr_box {int width; int height; scalar_t__ y; scalar_t__ x; } ;
struct sway_workspace {scalar_t__ width; scalar_t__ height; scalar_t__ y; scalar_t__ x; TYPE_1__* output; } ;
struct sway_container {scalar_t__ width; scalar_t__ height; scalar_t__ content_width; scalar_t__ content_height; int border_top; int border_bottom; int border_left; int border_right; scalar_t__ content_y; scalar_t__ content_x; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  view; struct sway_workspace* workspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  output_layout; } ;
struct TYPE_3__ {int /*<<< orphan*/  wlr_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_set_geometry_from_content (struct sway_container*) ; 
 int /*<<< orphan*/  floating_natural_resize (struct sway_container*) ; 
 TYPE_2__* root ; 
 struct wlr_box* wlr_output_layout_get_box (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void container_floating_resize_and_center(struct sway_container *con) {
	struct sway_workspace *ws = con->workspace;
	if (!ws) {
		// On scratchpad, just resize
		floating_natural_resize(con);
		return;
	}

	struct wlr_box *ob = wlr_output_layout_get_box(root->output_layout,
			ws->output->wlr_output);
	if (!ob) {
		// On NOOP output. Will be called again when moved to an output
		con->x = 0;
		con->y = 0;
		con->width = 0;
		con->height = 0;
		return;
	}

	floating_natural_resize(con);
	if (!con->view) {
		if (con->width > ws->width || con->height > ws->height) {
			con->x = ob->x + (ob->width - con->width) / 2;
			con->y = ob->y + (ob->height - con->height) / 2;
		} else {
			con->x = ws->x + (ws->width - con->width) / 2;
			con->y = ws->y + (ws->height - con->height) / 2;
		}
	} else {
		if (con->content_width > ws->width
				|| con->content_height > ws->height) {
			con->content_x = ob->x + (ob->width - con->content_width) / 2;
			con->content_y = ob->y + (ob->height - con->content_height) / 2;
		} else {
			con->content_x = ws->x + (ws->width - con->content_width) / 2;
			con->content_y = ws->y + (ws->height - con->content_height) / 2;
		}

		// If the view's border is B_NONE then these properties are ignored.
		con->border_top = con->border_bottom = true;
		con->border_left = con->border_right = true;

		container_set_geometry_from_content(con);
	}
}