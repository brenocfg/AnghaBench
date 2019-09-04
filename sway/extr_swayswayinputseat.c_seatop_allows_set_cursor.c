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
struct sway_seat {TYPE_1__* seatop_impl; } ;
struct TYPE_2__ {int allow_set_cursor; } ;

/* Variables and functions */

bool seatop_allows_set_cursor(struct sway_seat *seat) {
	return seat->seatop_impl->allow_set_cursor;
}