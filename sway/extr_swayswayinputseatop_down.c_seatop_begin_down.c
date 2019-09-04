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
typedef  int /*<<< orphan*/  uint32_t ;
struct sway_seat {struct seatop_down_event* seatop_data; int /*<<< orphan*/ * seatop_impl; TYPE_2__* cursor; } ;
struct sway_container {int dummy; } ;
struct seatop_down_event {int ref_con_lx; int ref_con_ly; int /*<<< orphan*/  ref_ly; int /*<<< orphan*/  ref_lx; struct sway_container* con; } ;
struct TYPE_4__ {TYPE_1__* cursor; } ;
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 struct seatop_down_event* calloc (int,int) ; 
 int /*<<< orphan*/  container_raise_floating (struct sway_container*) ; 
 int /*<<< orphan*/  seatop_end (struct sway_seat*) ; 
 int /*<<< orphan*/  seatop_impl ; 

void seatop_begin_down(struct sway_seat *seat, struct sway_container *con,
		uint32_t time_msec, int sx, int sy) {
	seatop_end(seat);

	struct seatop_down_event *e =
		calloc(1, sizeof(struct seatop_down_event));
	if (!e) {
		return;
	}
	e->con = con;
	e->ref_lx = seat->cursor->cursor->x;
	e->ref_ly = seat->cursor->cursor->y;
	e->ref_con_lx = sx;
	e->ref_con_ly = sy;

	seat->seatop_impl = &seatop_impl;
	seat->seatop_data = e;

	container_raise_floating(con);
}