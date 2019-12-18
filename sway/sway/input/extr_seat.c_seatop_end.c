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
struct sway_seat {TYPE_1__* seatop_impl; int /*<<< orphan*/ * seatop_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* end ) (struct sway_seat*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sway_seat*) ; 

void seatop_end(struct sway_seat *seat) {
	if (seat->seatop_impl && seat->seatop_impl->end) {
		seat->seatop_impl->end(seat);
	}
	free(seat->seatop_data);
	seat->seatop_data = NULL;
	seat->seatop_impl = NULL;
}