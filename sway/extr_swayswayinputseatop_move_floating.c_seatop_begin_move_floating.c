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
struct sway_seat {int /*<<< orphan*/  wlr_seat; int /*<<< orphan*/  cursor; struct seatop_move_floating_event* seatop_data; int /*<<< orphan*/ * seatop_impl; } ;
struct sway_container {int dummy; } ;
struct seatop_move_floating_event {struct sway_container* con; } ;

/* Variables and functions */
 struct seatop_move_floating_event* calloc (int,int) ; 
 int /*<<< orphan*/  container_raise_floating (struct sway_container*) ; 
 int /*<<< orphan*/  cursor_set_image (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seatop_end (struct sway_seat*) ; 
 int /*<<< orphan*/  seatop_impl ; 
 int /*<<< orphan*/  wlr_seat_pointer_clear_focus (int /*<<< orphan*/ ) ; 

void seatop_begin_move_floating(struct sway_seat *seat,
		struct sway_container *con) {
	seatop_end(seat);

	struct seatop_move_floating_event *e =
		calloc(1, sizeof(struct seatop_move_floating_event));
	if (!e) {
		return;
	}
	e->con = con;

	seat->seatop_impl = &seatop_impl;
	seat->seatop_data = e;

	container_raise_floating(con);

	cursor_set_image(seat->cursor, "grab", NULL);
	wlr_seat_pointer_clear_focus(seat->wlr_seat);
}