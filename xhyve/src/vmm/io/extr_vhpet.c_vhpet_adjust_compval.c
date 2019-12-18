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
typedef  int uint32_t ;
struct vhpet {TYPE_1__* timer; } ;
struct TYPE_2__ {scalar_t__ comprate; int compval; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static void
vhpet_adjust_compval(struct vhpet *vhpet, int n, uint32_t counter)
{
	uint32_t compval, comprate, compnext;

	KASSERT(vhpet->timer[n].comprate != 0, ("hpet t%d is not periodic", n));

	compval = vhpet->timer[n].compval;
	comprate = vhpet->timer[n].comprate;

	/*
	 * Calculate the comparator value to be used for the next periodic
	 * interrupt.
	 *
	 * This function is commonly called from the callout handler.
	 * In this scenario the 'counter' is ahead of 'compval'. To find
	 * the next value to program into the accumulator we divide the
	 * number space between 'compval' and 'counter' into 'comprate'
	 * sized units. The 'compval' is rounded up such that is "ahead"
	 * of 'counter'.
	 */
	compnext = compval + ((counter - compval) / comprate + 1) * comprate;

	vhpet->timer[n].compval = compnext;
}