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
struct sway_seat {int dummy; } ;
struct sway_node {int dummy; } ;
struct sway_container {int x; int width; int y; int height; struct sway_node node; TYPE_2__* workspace; } ;
typedef  enum wlr_direction { ____Placeholder_wlr_direction } wlr_direction ;
struct TYPE_4__ {TYPE_1__* floating; } ;
struct TYPE_3__ {int length; struct sway_container** items; } ;

/* Variables and functions */
 double DBL_MAX ; 
 int WLR_DIRECTION_LEFT ; 
 int WLR_DIRECTION_RIGHT ; 
 int WLR_DIRECTION_UP ; 

__attribute__((used)) static struct sway_node *node_get_in_direction_floating(
		struct sway_container *con, struct sway_seat *seat,
		enum wlr_direction dir) {
	double ref_lx = con->x + con->width / 2;
	double ref_ly = con->y + con->height / 2;
	double closest_distance = DBL_MAX;
	struct sway_container *closest_con = NULL;

	if (!con->workspace) {
		return NULL;
	}

	for (int i = 0; i < con->workspace->floating->length; i++) {
		struct sway_container *floater = con->workspace->floating->items[i];
		if (floater == con) {
			continue;
		}
		float distance = dir == WLR_DIRECTION_LEFT || dir == WLR_DIRECTION_RIGHT
			? (floater->x + floater->width / 2) - ref_lx
			: (floater->y + floater->height / 2) - ref_ly;
		if (dir == WLR_DIRECTION_LEFT || dir == WLR_DIRECTION_UP) {
			distance = -distance;
		}
		if (distance < 0) {
			continue;
		}
		if (distance < closest_distance) {
			closest_distance = distance;
			closest_con = floater;
		}
	}

	return closest_con ? &closest_con->node : NULL;
}