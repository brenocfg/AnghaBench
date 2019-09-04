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
struct vhpet {int /*<<< orphan*/  countbase; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int VHPET_NUM_TIMERS ; 
 int /*<<< orphan*/  vhpet_stop_timer (struct vhpet*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vhpet_stop_counting(struct vhpet *vhpet, uint32_t counter, sbintime_t now)
{
	int i;

	vhpet->countbase = counter;
	for (i = 0; i < VHPET_NUM_TIMERS; i++)
		vhpet_stop_timer(vhpet, i, now);
}