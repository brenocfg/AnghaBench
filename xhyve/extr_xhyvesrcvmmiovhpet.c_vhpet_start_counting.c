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
struct vhpet {int /*<<< orphan*/  countbase_sbt; int /*<<< orphan*/  countbase; } ;

/* Variables and functions */
 int VHPET_NUM_TIMERS ; 
 int /*<<< orphan*/  sbinuptime () ; 
 int /*<<< orphan*/  vhpet_start_timer (struct vhpet*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vhpet_start_counting(struct vhpet *vhpet)
{
	int i;

	vhpet->countbase_sbt = sbinuptime();
	for (i = 0; i < VHPET_NUM_TIMERS; i++) {
		/*
		 * Restart the timers based on the value of the main counter
		 * when it stopped counting.
		 */
		vhpet_start_timer(vhpet, i, vhpet->countbase,
		    vhpet->countbase_sbt);
	}
}