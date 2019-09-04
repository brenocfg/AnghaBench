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
struct sway_seat {int /*<<< orphan*/  wlr_seat; struct seatop_move_tiling_event* seatop_data; int /*<<< orphan*/ * seatop_impl; TYPE_1__* cursor; } ;
struct sway_container {int dummy; } ;
struct seatop_move_tiling_event {int /*<<< orphan*/  ref_ly; int /*<<< orphan*/  ref_lx; struct sway_container* con; } ;
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_3__ {TYPE_2__* cursor; } ;

/* Variables and functions */
 struct seatop_move_tiling_event* calloc (int,int) ; 
 int /*<<< orphan*/  container_raise_floating (struct sway_container*) ; 
 int /*<<< orphan*/  seatop_end (struct sway_seat*) ; 
 int /*<<< orphan*/  seatop_impl ; 
 int /*<<< orphan*/  wlr_seat_pointer_clear_focus (int /*<<< orphan*/ ) ; 

void seatop_begin_move_tiling_threshold(struct sway_seat *seat,
		struct sway_container *con) {
	seatop_end(seat);

	struct seatop_move_tiling_event *e =
		calloc(1, sizeof(struct seatop_move_tiling_event));
	if (!e) {
		return;
	}
	e->con = con;
	e->ref_lx = seat->cursor->cursor->x;
	e->ref_ly = seat->cursor->cursor->y;

	seat->seatop_impl = &seatop_impl;
	seat->seatop_data = e;

	container_raise_floating(con);
	wlr_seat_pointer_clear_focus(seat->wlr_seat);
}