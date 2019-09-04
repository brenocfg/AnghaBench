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
struct sway_container {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  seat_set_focus (struct sway_seat*,int /*<<< orphan*/ *) ; 

void seat_set_focus_container(struct sway_seat *seat,
		struct sway_container *con) {
	seat_set_focus(seat, con ? &con->node : NULL);
}