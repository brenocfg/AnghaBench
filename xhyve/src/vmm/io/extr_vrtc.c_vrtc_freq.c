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
struct TYPE_2__ {int reg_a; } ;
struct vrtc {TYPE_1__ rtcdev; } ;
typedef  int sbintime_t ;

/* Variables and functions */
#define  SBT_1S 128 
 scalar_t__ aintr_enabled (struct vrtc*) ; 
 scalar_t__ divider_enabled (int) ; 
 scalar_t__ pintr_enabled (struct vrtc*) ; 
 scalar_t__ uintr_enabled (struct vrtc*) ; 
 scalar_t__ update_enabled (struct vrtc*) ; 

__attribute__((used)) static sbintime_t
vrtc_freq(struct vrtc *vrtc)
{
	int ratesel;

	static sbintime_t pf[16] = {
		0,
		SBT_1S / 256,
		SBT_1S / 128,
		SBT_1S / 8192,
		SBT_1S / 4096,
		SBT_1S / 2048,
		SBT_1S / 1024,
		SBT_1S / 512,
		SBT_1S / 256,
		SBT_1S / 128,
		SBT_1S / 64,
		SBT_1S / 32,
		SBT_1S / 16,
		SBT_1S / 8,
		SBT_1S / 4,
		SBT_1S / 2,
	};

	/*
	 * If both periodic and alarm interrupts are enabled then use the
	 * periodic frequency to drive the callout. The minimum periodic
	 * frequency (2 Hz) is higher than the alarm frequency (1 Hz) so
	 * piggyback the alarm on top of it. The same argument applies to
	 * the update interrupt.
	 */
	if (pintr_enabled(vrtc) && divider_enabled(vrtc->rtcdev.reg_a)) {
		ratesel = vrtc->rtcdev.reg_a & 0xf;
		return (pf[ratesel]);
	} else if (aintr_enabled(vrtc) && update_enabled(vrtc)) {
		return (SBT_1S);
	} else if (uintr_enabled(vrtc) && update_enabled(vrtc)) {
		return (SBT_1S);
	} else {
		return (0);
	}
}