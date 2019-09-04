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
struct wlr_box {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_output {int /*<<< orphan*/  damage; TYPE_1__* wlr_output; scalar_t__ ly; scalar_t__ lx; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct sway_container {scalar_t__ view; TYPE_2__ current; } ;
struct TYPE_3__ {int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_for_each_child (struct sway_container*,int /*<<< orphan*/  (*) (struct sway_container*,struct sway_output*),struct sway_output*) ; 
 int /*<<< orphan*/  damage_child_views_iterator (struct sway_container*,struct sway_output*) ; 
 int /*<<< orphan*/  scale_box (struct wlr_box*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_output_damage_add_box (int /*<<< orphan*/ ,struct wlr_box*) ; 

void output_damage_whole_container(struct sway_output *output,
		struct sway_container *con) {
	// Pad the box by 1px, because the width is a double and might be a fraction
	struct wlr_box box = {
		.x = con->current.x - output->lx - 1,
		.y = con->current.y - output->ly - 1,
		.width = con->current.width + 2,
		.height = con->current.height + 2,
	};
	scale_box(&box, output->wlr_output->scale);
	wlr_output_damage_add_box(output->damage, &box);
	// Damage subsurfaces as well, which may extend outside the box
	if (con->view) {
		damage_child_views_iterator(con, output);
	} else {
		container_for_each_child(con, damage_child_views_iterator, output);
	}
}