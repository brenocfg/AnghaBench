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
struct wlr_surface {int dummy; } ;
struct sway_seat {struct sway_cursor* cursor; struct seatop_default_event* seatop_data; } ;
struct sway_cursor {TYPE_1__* cursor; } ;
struct seatop_default_event {int /*<<< orphan*/  previous_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  cursor_do_rebase (struct sway_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_surface*,double,double) ; 
 int /*<<< orphan*/  node_at_coords (struct sway_seat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlr_surface**,double*,double*) ; 

__attribute__((used)) static void handle_rebase(struct sway_seat *seat, uint32_t time_msec) {
	struct seatop_default_event *e = seat->seatop_data;
	struct sway_cursor *cursor = seat->cursor;
	struct wlr_surface *surface = NULL;
	double sx = 0.0, sy = 0.0;
	e->previous_node = node_at_coords(seat,
			cursor->cursor->x, cursor->cursor->y, &surface, &sx, &sy);
	cursor_do_rebase(cursor, time_msec, e->previous_node, surface, sx, sy);
}