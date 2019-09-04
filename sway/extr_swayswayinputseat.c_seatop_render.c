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
struct sway_output {int dummy; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* render ) (struct sway_seat*,struct sway_output*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sway_seat*,struct sway_output*,int /*<<< orphan*/ *) ; 

void seatop_render(struct sway_seat *seat, struct sway_output *output,
		pixman_region32_t *damage) {
	if (seat->seatop_impl->render) {
		seat->seatop_impl->render(seat, output, damage);
	}
}