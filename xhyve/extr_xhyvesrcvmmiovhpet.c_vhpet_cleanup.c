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
struct vhpet {TYPE_1__* timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 int VHPET_NUM_TIMERS ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct vhpet*) ; 

void
vhpet_cleanup(struct vhpet *vhpet)
{
	int i;

	for (i = 0; i < VHPET_NUM_TIMERS; i++)
		callout_drain(&vhpet->timer[i].callout);

	free(vhpet);
}