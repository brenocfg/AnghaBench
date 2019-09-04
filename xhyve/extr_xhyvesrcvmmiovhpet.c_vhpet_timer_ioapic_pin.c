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
struct TYPE_2__ {int cap_config; } ;

/* Variables and functions */
 int HPET_TCNF_INT_ROUTE ; 
 scalar_t__ vhpet_timer_msi_enabled (struct vhpet*,int) ; 

__attribute__((used)) static __inline int
vhpet_timer_ioapic_pin(struct vhpet *vhpet, int n)
{
	/*
	 * If the timer is configured to use MSI then treat it as if the
	 * timer is not connected to the ioapic.
	 */
	if (vhpet_timer_msi_enabled(vhpet, n))
		return (0);

	return ((vhpet->timer[n].cap_config & HPET_TCNF_INT_ROUTE) >> 9);
}