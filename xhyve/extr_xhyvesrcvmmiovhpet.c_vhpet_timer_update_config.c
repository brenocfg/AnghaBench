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
typedef  int uint32_t ;
struct vhpet {int isr; int /*<<< orphan*/  vm; TYPE_1__* timer; } ;
struct TYPE_2__ {int cap_config; scalar_t__ comprate; } ;

/* Variables and functions */
 int HPET_TCAP_RO_MASK ; 
 int HPET_TCNF_32MODE ; 
 scalar_t__ HPET_TCNF_INT_ROUTE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VM_CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VM_CTR2 (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  VM_CTR3 (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  update_register (int*,int,int) ; 
 int /*<<< orphan*/  vhpet_periodic_timer (struct vhpet*,int) ; 
 scalar_t__ vhpet_timer_edge_trig (struct vhpet*,int) ; 
 int /*<<< orphan*/  vhpet_timer_interrupt_enabled (struct vhpet*,int) ; 
 int vhpet_timer_ioapic_pin (struct vhpet*,int) ; 
 scalar_t__ vhpet_timer_msi_enabled (struct vhpet*,int) ; 
 int /*<<< orphan*/  vioapic_deassert_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhyve_abort (char*,int) ; 

__attribute__((used)) static void
vhpet_timer_update_config(struct vhpet *vhpet, int n, uint64_t data,
    uint64_t mask)
{
	bool clear_isr;
	int old_pin, new_pin;
	uint32_t allowed_irqs;
	uint64_t oldval, newval;

	if (vhpet_timer_msi_enabled(vhpet, n) ||
	    vhpet_timer_edge_trig(vhpet, n)) {
		if (vhpet->isr & (1 << n))
			xhyve_abort("vhpet timer %d isr should not be asserted\n", n);
	}
	old_pin = vhpet_timer_ioapic_pin(vhpet, n);
	oldval = vhpet->timer[n].cap_config;

	newval = oldval;
	update_register(&newval, data, mask);
	newval &= ~(HPET_TCAP_RO_MASK | HPET_TCNF_32MODE);
	newval |= oldval & HPET_TCAP_RO_MASK;

	if (newval == oldval)
		return;

	vhpet->timer[n].cap_config = newval;
	VM_CTR2(vhpet->vm, "hpet t%d cap_config set to 0x%016llx", n, newval);

	/*
	 * Validate the interrupt routing in the HPET_TCNF_INT_ROUTE field.
	 * If it does not match the bits set in HPET_TCAP_INT_ROUTE then set
	 * it to the default value of 0.
	 */
	allowed_irqs = vhpet->timer[n].cap_config >> 32;
	new_pin = vhpet_timer_ioapic_pin(vhpet, n);
	if (new_pin != 0 && (allowed_irqs & (1 << new_pin)) == 0) {
		VM_CTR3(vhpet->vm, "hpet t%d configured invalid irq %d, "
		    "allowed_irqs 0x%08x", n, new_pin, allowed_irqs);
		new_pin = 0;
		vhpet->timer[n].cap_config &= ~((uint64_t) HPET_TCNF_INT_ROUTE);
	}

	if (!vhpet_periodic_timer(vhpet, n))
		vhpet->timer[n].comprate = 0;

	/*
	 * If the timer's ISR bit is set then clear it in the following cases:
	 * - interrupt is disabled
	 * - interrupt type is changed from level to edge or fsb.
	 * - interrupt routing is changed
	 *
	 * This is to ensure that this timer's level triggered interrupt does
	 * not remain asserted forever.
	 */
	if (vhpet->isr & (1 << n)) {
		KASSERT(old_pin != 0, ("timer %d isr asserted to ioapic pin %d",
		    n, old_pin));
		if (!vhpet_timer_interrupt_enabled(vhpet, n))
			clear_isr = true;
		else if (vhpet_timer_msi_enabled(vhpet, n))
			clear_isr = true;
		else if (vhpet_timer_edge_trig(vhpet, n))
			clear_isr = true;
		else if (vhpet_timer_ioapic_pin(vhpet, n) != old_pin)
			clear_isr = true;
		else
			clear_isr = false;

		if (clear_isr) {
			VM_CTR1(vhpet->vm, "hpet t%d isr cleared due to "
			    "configuration change", n);
			vioapic_deassert_irq(vhpet->vm, old_pin);
			vhpet->isr &= ~(1 << n);
		}
	}
}