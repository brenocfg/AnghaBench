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
struct vhpet {int isr; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int vhpet_timer_ioapic_pin (struct vhpet*,int) ; 
 int /*<<< orphan*/  vioapic_deassert_irq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vhpet_timer_clear_isr(struct vhpet *vhpet, int n)
{
	int pin;

	if (vhpet->isr & (1 << n)) {
		pin = vhpet_timer_ioapic_pin(vhpet, n);
		KASSERT(pin != 0, ("vhpet timer %d irq incorrectly routed", n));
		vioapic_deassert_irq(vhpet->vm, pin);
		vhpet->isr &= ~(1 << n);
	}
}