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
struct sway_seat {int /*<<< orphan*/  cursor; struct seatop_move_tiling_event* seatop_data; } ;
struct sway_container {int dummy; } ;
struct seatop_move_tiling_event {int threshold_reached; } ;

/* Variables and functions */
 int /*<<< orphan*/  cursor_set_image (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seatop_begin_move_tiling_threshold (struct sway_seat*,struct sway_container*) ; 

void seatop_begin_move_tiling(struct sway_seat *seat,
		struct sway_container *con) {
	seatop_begin_move_tiling_threshold(seat, con);
	struct seatop_move_tiling_event *e = seat->seatop_data;
	if (e) {
		e->threshold_reached = true;
		cursor_set_image(seat->cursor, "grab", NULL);
	}
}