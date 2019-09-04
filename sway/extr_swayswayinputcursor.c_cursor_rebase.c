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
struct sway_cursor {int /*<<< orphan*/  seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_current_time_msec () ; 
 int /*<<< orphan*/  seatop_rebase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cursor_rebase(struct sway_cursor *cursor) {
	uint32_t time_msec = get_current_time_msec();
	seatop_rebase(cursor->seat, time_msec);
}