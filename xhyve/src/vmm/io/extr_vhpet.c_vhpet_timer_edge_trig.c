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
 int HPET_TCNF_INT_TYPE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  vhpet_timer_msi_enabled (struct vhpet*,int) ; 

__attribute__((used)) static __inline bool
vhpet_timer_edge_trig(struct vhpet *vhpet, int n)
{

	KASSERT(!vhpet_timer_msi_enabled(vhpet, n), ("vhpet_timer_edge_trig: "
	    "timer %d is using MSI", n));

	if ((vhpet->timer[n].cap_config & HPET_TCNF_INT_TYPE) == 0)
		return (true);
	else
		return (false);
}