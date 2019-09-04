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
typedef  int uint8_t ;
struct TYPE_2__ {int reg_a; } ;
struct vrtc {int base_rtctime; int base_uptime; int /*<<< orphan*/  vm; TYPE_1__ rtcdev; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 int RTCSA_TUP ; 
 int /*<<< orphan*/  VM_CTR2 (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ divider_enabled (int) ; 
 int sbinuptime () ; 
 int /*<<< orphan*/  vrtc_callout_check (struct vrtc*,scalar_t__) ; 
 int /*<<< orphan*/  vrtc_callout_reset (struct vrtc*,scalar_t__) ; 
 scalar_t__ vrtc_freq (struct vrtc*) ; 

__attribute__((used)) static void
vrtc_set_reg_a(struct vrtc *vrtc, uint8_t newval)
{
	sbintime_t oldfreq, newfreq;
	uint8_t oldval, changed;

	newval &= ~RTCSA_TUP;
	oldval = vrtc->rtcdev.reg_a;
	oldfreq = vrtc_freq(vrtc);

	if (divider_enabled(oldval) && !divider_enabled(newval)) {
		VM_CTR2(vrtc->vm, "RTC divider held in reset at %#lx/%#llx",
		    vrtc->base_rtctime, vrtc->base_uptime);
	} else if (!divider_enabled(oldval) && divider_enabled(newval)) {
		/*
		 * If the dividers are coming out of reset then update
		 * 'base_uptime' before this happens. This is done to
		 * maintain the illusion that the RTC date/time was frozen
		 * while the dividers were disabled.
		 */
		vrtc->base_uptime = sbinuptime();
		VM_CTR2(vrtc->vm, "RTC divider out of reset at %#lx/%#llx",
		    vrtc->base_rtctime, vrtc->base_uptime);
	} else {
		/* NOTHING */
	}

	vrtc->rtcdev.reg_a = newval;
	changed = oldval ^ newval;
	if (changed) {
		VM_CTR2(vrtc->vm, "RTC reg_a changed from %#x to %#x",
		    oldval, newval);
	}

	/*
	 * Side effect of changes to rate select and divider enable bits.
	 */
	newfreq = vrtc_freq(vrtc);
	if (newfreq != oldfreq)
		vrtc_callout_reset(vrtc, newfreq);
	else
		vrtc_callout_check(vrtc, newfreq);
}