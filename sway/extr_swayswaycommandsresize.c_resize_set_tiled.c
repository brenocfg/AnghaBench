#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sway_container {scalar_t__ layout; int width; int height; TYPE_1__* workspace; struct sway_container* parent; } ;
struct resize_amount {int amount; scalar_t__ unit; } ;
struct cmd_results {int dummy; } ;
struct TYPE_2__ {int width; int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXIS_HORIZONTAL ; 
 int /*<<< orphan*/  AXIS_VERTICAL ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 scalar_t__ L_HORIZ ; 
 scalar_t__ L_VERT ; 
 scalar_t__ RESIZE_UNIT_DEFAULT ; 
 scalar_t__ RESIZE_UNIT_PPT ; 
 scalar_t__ RESIZE_UNIT_PX ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  container_resize_tiled (struct sway_container*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct cmd_results *resize_set_tiled(struct sway_container *con,
		struct resize_amount *width, struct resize_amount *height) {
	if (width->amount) {
		if (width->unit == RESIZE_UNIT_PPT ||
				width->unit == RESIZE_UNIT_DEFAULT) {
			// Convert to px
			struct sway_container *parent = con->parent;
			while (parent && parent->layout != L_HORIZ) {
				parent = parent->parent;
			}
			if (parent) {
				width->amount = parent->width * width->amount / 100;
			} else {
				width->amount = con->workspace->width * width->amount / 100;
			}
			width->unit = RESIZE_UNIT_PX;
		}
		if (width->unit == RESIZE_UNIT_PX) {
			container_resize_tiled(con, AXIS_HORIZONTAL,
					width->amount - con->width);
		}
	}

	if (height->amount) {
		if (height->unit == RESIZE_UNIT_PPT ||
				height->unit == RESIZE_UNIT_DEFAULT) {
			// Convert to px
			struct sway_container *parent = con->parent;
			while (parent && parent->layout != L_VERT) {
				parent = parent->parent;
			}
			if (parent) {
				height->amount = parent->height * height->amount / 100;
			} else {
				height->amount = con->workspace->height * height->amount / 100;
			}
			height->unit = RESIZE_UNIT_PX;
		}
		if (height->unit == RESIZE_UNIT_PX) {
			container_resize_tiled(con, AXIS_VERTICAL,
					height->amount - con->height);
		}
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}