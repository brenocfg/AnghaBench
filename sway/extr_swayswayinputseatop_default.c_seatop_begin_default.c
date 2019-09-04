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
struct sway_seat {struct seatop_default_event* seatop_data; int /*<<< orphan*/ * seatop_impl; } ;
struct seatop_default_event {int dummy; } ;

/* Variables and functions */
 struct seatop_default_event* calloc (int,int) ; 
 int /*<<< orphan*/  seatop_end (struct sway_seat*) ; 
 int /*<<< orphan*/  seatop_impl ; 
 int /*<<< orphan*/  seatop_rebase (struct sway_seat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_assert (struct seatop_default_event*,char*) ; 

void seatop_begin_default(struct sway_seat *seat) {
	seatop_end(seat);

	struct seatop_default_event *e =
		calloc(1, sizeof(struct seatop_default_event));
	sway_assert(e, "Unable to allocate seatop_default_event");
	seat->seatop_impl = &seatop_impl;
	seat->seatop_data = e;

	seatop_rebase(seat, 0);
}