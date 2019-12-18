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
typedef  int /*<<< orphan*/  uint32_t ;
struct wlr_cursor {scalar_t__ y; scalar_t__ x; } ;
struct sway_seat {TYPE_1__* cursor; struct seatop_move_floating_event* seatop_data; } ;
struct seatop_move_floating_event {int /*<<< orphan*/  con; scalar_t__ dy; scalar_t__ dx; } ;
struct TYPE_2__ {struct wlr_cursor* cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_floating_move_to (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  desktop_damage_whole_container (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_motion(struct sway_seat *seat, uint32_t time_msec,
		double dx, double dy) {
	struct seatop_move_floating_event *e = seat->seatop_data;
	struct wlr_cursor *cursor = seat->cursor->cursor;
	desktop_damage_whole_container(e->con);
	container_floating_move_to(e->con, cursor->x - e->dx, cursor->y - e->dy);
	desktop_damage_whole_container(e->con);
}