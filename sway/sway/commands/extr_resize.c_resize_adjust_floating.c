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
typedef  scalar_t__ uint32_t ;
struct sway_container {int width; int height; int x; int y; int content_x; int content_y; int content_width; int content_height; } ;
struct resize_amount {int amount; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_container* container; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 scalar_t__ AXIS_HORIZONTAL ; 
 scalar_t__ AXIS_VERTICAL ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 scalar_t__ WLR_EDGE_LEFT ; 
 scalar_t__ WLR_EDGE_TOP ; 
 int /*<<< orphan*/  arrange_container (struct sway_container*) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  floating_calculate_constraints (int*,int*,int*,int*) ; 
 scalar_t__ is_horizontal (scalar_t__) ; 

__attribute__((used)) static struct cmd_results *resize_adjust_floating(uint32_t axis,
		struct resize_amount *amount) {
	struct sway_container *con = config->handler_context.container;
	int grow_width = 0, grow_height = 0;

	if (is_horizontal(axis)) {
		grow_width = amount->amount;
	} else {
		grow_height = amount->amount;
	}

	// Make sure we're not adjusting beyond floating min/max size
	int min_width, max_width, min_height, max_height;
	floating_calculate_constraints(&min_width, &max_width,
			&min_height, &max_height);
	if (con->width + grow_width < min_width) {
		grow_width = min_width - con->width;
	} else if (con->width + grow_width > max_width) {
		grow_width = max_width - con->width;
	}
	if (con->height + grow_height < min_height) {
		grow_height = min_height - con->height;
	} else if (con->height + grow_height > max_height) {
		grow_height = max_height - con->height;
	}
	int grow_x = 0, grow_y = 0;

	if (axis == AXIS_HORIZONTAL) {
		grow_x = -grow_width / 2;
	} else if (axis == AXIS_VERTICAL) {
		grow_y = -grow_height / 2;
	} else if (axis == WLR_EDGE_TOP) {
		grow_y = -grow_height;
	} else if (axis == WLR_EDGE_LEFT) {
		grow_x = -grow_width;
	}
	if (grow_x == 0 && grow_y == 0) {
		return cmd_results_new(CMD_INVALID, "Cannot resize any further");
	}
	con->x += grow_x;
	con->y += grow_y;
	con->width += grow_width;
	con->height += grow_height;

	con->content_x += grow_x;
	con->content_y += grow_y;
	con->content_width += grow_width;
	con->content_height += grow_height;

	arrange_container(con);

	return cmd_results_new(CMD_SUCCESS, NULL);
}