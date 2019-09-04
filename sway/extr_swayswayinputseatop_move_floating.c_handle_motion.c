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
typedef  int /*<<< orphan*/  uint32_t ;
struct sway_seat {struct seatop_move_floating_event* seatop_data; } ;
struct seatop_move_floating_event {int /*<<< orphan*/  con; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_floating_translate (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  desktop_damage_whole_container (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_motion(struct sway_seat *seat, uint32_t time_msec,
		double dx, double dy) {
	struct seatop_move_floating_event *e = seat->seatop_data;
	desktop_damage_whole_container(e->con);
	container_floating_translate(e->con, dx, dy);
	desktop_damage_whole_container(e->con);
}