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
struct sway_seat {TYPE_1__* seatop_impl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rebase ) (struct sway_seat*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sway_seat*,int /*<<< orphan*/ ) ; 

void seatop_rebase(struct sway_seat *seat, uint32_t time_msec) {
	if (seat->seatop_impl->rebase) {
		seat->seatop_impl->rebase(seat, time_msec);
	}
}