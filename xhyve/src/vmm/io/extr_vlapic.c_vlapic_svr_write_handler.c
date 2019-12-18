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
typedef  int uint32_t ;
struct vlapic {int svr_last; int /*<<< orphan*/  callout; struct LAPIC* apic_page; } ;
struct LAPIC {int svr; } ;

/* Variables and functions */
 int APIC_SVR_ENABLE ; 
 int /*<<< orphan*/  VLAPIC_CTR0 (struct vlapic*,char*) ; 
 int /*<<< orphan*/  VLAPIC_TIMER_LOCK (struct vlapic*) ; 
 int /*<<< orphan*/  VLAPIC_TIMER_UNLOCK (struct vlapic*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlapic_icrtmr_write_handler (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_mask_lvts (struct vlapic*) ; 
 scalar_t__ vlapic_periodic_timer (struct vlapic*) ; 

void
vlapic_svr_write_handler(struct vlapic *vlapic)
{
	struct LAPIC *lapic;
	uint32_t old, new, changed;

	lapic = vlapic->apic_page;

	new = lapic->svr;
	old = vlapic->svr_last;
	vlapic->svr_last = new;

	changed = old ^ new;
	if ((changed & APIC_SVR_ENABLE) != 0) {
		if ((new & APIC_SVR_ENABLE) == 0) {
			/*
			 * The apic is now disabled so stop the apic timer
			 * and mask all the LVT entries.
			 */
			VLAPIC_CTR0(vlapic, "vlapic is software-disabled");
			VLAPIC_TIMER_LOCK(vlapic);
			callout_stop(&vlapic->callout);
			VLAPIC_TIMER_UNLOCK(vlapic);
			vlapic_mask_lvts(vlapic);
		} else {
			/*
			 * The apic is now enabled so restart the apic timer
			 * if it is configured in periodic mode.
			 */
			VLAPIC_CTR0(vlapic, "vlapic is software-enabled");
			if (vlapic_periodic_timer(vlapic))
				vlapic_icrtmr_write_handler(vlapic);
		}
	}
}