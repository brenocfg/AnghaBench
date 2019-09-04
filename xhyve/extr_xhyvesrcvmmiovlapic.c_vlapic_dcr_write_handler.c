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
struct vlapic {int /*<<< orphan*/  timer_period_bt; int /*<<< orphan*/  timer_freq_bt; struct LAPIC* apic_page; } ;
struct LAPIC {int /*<<< orphan*/  icr_timer; int /*<<< orphan*/  dcr_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ2BT (unsigned int,int /*<<< orphan*/ *) ; 
 int VLAPIC_BUS_FREQ ; 
 int /*<<< orphan*/  VLAPIC_CTR2 (struct vlapic*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VLAPIC_TIMER_LOCK (struct vlapic*) ; 
 int /*<<< orphan*/  VLAPIC_TIMER_UNLOCK (struct vlapic*) ; 
 int /*<<< orphan*/  bintime_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vlapic_timer_divisor (int /*<<< orphan*/ ) ; 

void
vlapic_dcr_write_handler(struct vlapic *vlapic)
{
	struct LAPIC *lapic;
	int divisor;
	
	lapic = vlapic->apic_page;
	VLAPIC_TIMER_LOCK(vlapic);

	divisor = vlapic_timer_divisor(lapic->dcr_timer);
	VLAPIC_CTR2(vlapic, "vlapic dcr_timer=%#x, divisor=%d",
	    lapic->dcr_timer, divisor);

	/*
	 * Update the timer frequency and the timer period.
	 *
	 * XXX changes to the frequency divider will not take effect until
	 * the timer is reloaded.
	 */
	FREQ2BT(((unsigned) (VLAPIC_BUS_FREQ / divisor)), &vlapic->timer_freq_bt);
	vlapic->timer_period_bt = vlapic->timer_freq_bt;
	bintime_mul(&vlapic->timer_period_bt, lapic->icr_timer);

	VLAPIC_TIMER_UNLOCK(vlapic);
}