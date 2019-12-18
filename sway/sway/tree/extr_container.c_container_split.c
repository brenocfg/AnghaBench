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
struct sway_seat {int dummy; } ;
struct sway_container {int layout; scalar_t__ fullscreen_mode; int /*<<< orphan*/  node; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  height_fraction; int /*<<< orphan*/  width_fraction; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;

/* Variables and functions */
 scalar_t__ FULLSCREEN_GLOBAL ; 
 int /*<<< orphan*/  container_add_child (struct sway_container*,struct sway_container*) ; 
 struct sway_container* container_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  container_replace (struct sway_container*,struct sway_container*) ; 
 struct sway_seat* input_manager_get_default_seat () ; 
 int /*<<< orphan*/ * seat_get_focus (struct sway_seat*) ; 
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seat_set_raw_focus (struct sway_seat*,int /*<<< orphan*/ *) ; 

struct sway_container *container_split(struct sway_container *child,
		enum sway_container_layout layout) {
	struct sway_seat *seat = input_manager_get_default_seat();
	bool set_focus = (seat_get_focus(seat) == &child->node);

	struct sway_container *cont = container_create(NULL);
	cont->width = child->width;
	cont->height = child->height;
	cont->width_fraction = child->width_fraction;
	cont->height_fraction = child->height_fraction;
	cont->x = child->x;
	cont->y = child->y;
	cont->layout = layout;

	container_replace(child, cont);
	container_add_child(cont, child);

	if (set_focus) {
		seat_set_raw_focus(seat, &cont->node);
		if (cont->fullscreen_mode == FULLSCREEN_GLOBAL) {
			seat_set_focus(seat, &child->node);
		} else {
			seat_set_raw_focus(seat, &child->node);
		}
	}

	return cont;
}