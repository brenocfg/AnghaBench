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
struct TYPE_2__ {int /*<<< orphan*/  (* motion ) (struct sway_seat*,int /*<<< orphan*/ ,double,double) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sway_seat*,int /*<<< orphan*/ ,double,double) ; 

void seatop_motion(struct sway_seat *seat, uint32_t time_msec,
		double dx, double dy) {
	if (seat->seatop_impl->motion) {
		seat->seatop_impl->motion(seat, time_msec, dx, dy);
	}
}