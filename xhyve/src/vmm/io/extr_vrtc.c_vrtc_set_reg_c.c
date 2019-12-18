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
typedef  int uint8_t ;
struct rtcdev {int reg_c; } ;
struct vrtc {int /*<<< orphan*/  vm; struct rtcdev rtcdev; } ;

/* Variables and functions */
 int RTCIR_ALARM ; 
 int RTCIR_INT ; 
 int RTCIR_PERIOD ; 
 int RTCIR_UPDATE ; 
 int /*<<< orphan*/  RTC_IRQ ; 
 int /*<<< orphan*/  VM_CTR1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_CTR2 (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ aintr_enabled (struct vrtc*) ; 
 scalar_t__ pintr_enabled (struct vrtc*) ; 
 scalar_t__ uintr_enabled (struct vrtc*) ; 
 int /*<<< orphan*/  vatpic_pulse_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vioapic_pulse_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vrtc_set_reg_c(struct vrtc *vrtc, uint8_t newval)
{
	struct rtcdev *rtc;
	int oldirqf, newirqf;
	uint8_t oldval, changed;

	rtc = &vrtc->rtcdev;
	newval &= RTCIR_ALARM | RTCIR_PERIOD | RTCIR_UPDATE;

	oldirqf = rtc->reg_c & RTCIR_INT;
	if ((aintr_enabled(vrtc) && (newval & RTCIR_ALARM) != 0) ||
	    (pintr_enabled(vrtc) && (newval & RTCIR_PERIOD) != 0) ||
	    (uintr_enabled(vrtc) && (newval & RTCIR_UPDATE) != 0)) {
		newirqf = RTCIR_INT;
	} else {
		newirqf = 0;
	}

	oldval = rtc->reg_c;
	rtc->reg_c = (uint8_t) (newirqf | newval);
	changed = oldval ^ rtc->reg_c;
	if (changed) {
		VM_CTR2(vrtc->vm, "RTC reg_c changed from %#x to %#x",
		    oldval, rtc->reg_c);
	}

	if (!oldirqf && newirqf) {
		VM_CTR1(vrtc->vm, "RTC irq %d asserted", RTC_IRQ);
		vatpic_pulse_irq(vrtc->vm, RTC_IRQ);
		vioapic_pulse_irq(vrtc->vm, RTC_IRQ);
	} else if (oldirqf && !newirqf) {
		VM_CTR1(vrtc->vm, "RTC irq %d deasserted", RTC_IRQ);
	}
}