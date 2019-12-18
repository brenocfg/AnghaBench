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
typedef  int uint64_t ;
struct vhpet {TYPE_1__* timer; } ;
struct TYPE_2__ {int const cap_config; } ;

/* Variables and functions */
 int HPET_TCAP_FSB_INT_DEL ; 
 int HPET_TCNF_FSB_EN ; 

__attribute__((used)) static __inline bool
vhpet_timer_msi_enabled(struct vhpet *vhpet, int n)
{
	const uint64_t msi_enable = HPET_TCAP_FSB_INT_DEL | HPET_TCNF_FSB_EN;

	if ((vhpet->timer[n].cap_config & msi_enable) == msi_enable)
		return (true);
	else
		return (false);
}