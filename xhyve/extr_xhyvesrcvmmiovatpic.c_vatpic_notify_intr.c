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
struct vatpic {int /*<<< orphan*/  vm; struct atpic* atpic; } ;
struct atpic {int intr_raised; int /*<<< orphan*/  service; int /*<<< orphan*/  request; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVT_LINT0 ; 
 int /*<<< orphan*/  VATPIC_CTR3 (struct vatpic*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATPIC_CTR4 (struct vatpic*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_set_local_intr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int vatpic_get_highest_irrpin (struct atpic*) ; 
 int /*<<< orphan*/  vatpic_set_pinstate (struct vatpic*,int,int) ; 
 int /*<<< orphan*/  vioapic_pulse_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vatpic_notify_intr(struct vatpic *vatpic)
{
	struct atpic *atpic;
	int pin;

	/*
	 * First check the slave.
	 */
	atpic = &vatpic->atpic[1];
	if (!atpic->intr_raised &&
	    (pin = vatpic_get_highest_irrpin(atpic)) != -1) {
		VATPIC_CTR4(vatpic, "atpic slave notify pin = %d "
		    "(imr 0x%x irr 0x%x isr 0x%x)", pin,
		    atpic->mask, atpic->request, atpic->service);

		/*
		 * Cascade the request from the slave to the master.
		 */
		atpic->intr_raised = true;
		vatpic_set_pinstate(vatpic, 2, true);
		vatpic_set_pinstate(vatpic, 2, false);
	} else {
		VATPIC_CTR3(vatpic, "atpic slave no eligible interrupts "
		    "(imr 0x%x irr 0x%x isr 0x%x)",
		    atpic->mask, atpic->request, atpic->service);
	}

	/*
	 * Then check the master.
	 */
	atpic = &vatpic->atpic[0];
	if (!atpic->intr_raised &&
	    (pin = vatpic_get_highest_irrpin(atpic)) != -1) {
		VATPIC_CTR4(vatpic, "atpic master notify pin = %d "
		    "(imr 0x%x irr 0x%x isr 0x%x)", pin,
		    atpic->mask, atpic->request, atpic->service);

		/*
		 * From Section 3.6.2, "Interrupt Modes", in the
		 * MPtable Specification, Version 1.4
		 *
		 * PIC interrupts are routed to both the Local APIC
		 * and the I/O APIC to support operation in 1 of 3
		 * modes.
		 *
		 * 1. Legacy PIC Mode: the PIC effectively bypasses
		 * all APIC components.  In this mode the local APIC is
		 * disabled and LINT0 is reconfigured as INTR to
		 * deliver the PIC interrupt directly to the CPU.
		 *
		 * 2. Virtual Wire Mode: the APIC is treated as a
		 * virtual wire which delivers interrupts from the PIC
		 * to the CPU.  In this mode LINT0 is programmed as
		 * ExtINT to indicate that the PIC is the source of
		 * the interrupt.
		 *
		 * 3. Virtual Wire Mode via I/O APIC: PIC interrupts are
		 * fielded by the I/O APIC and delivered to the appropriate
		 * CPU.  In this mode the I/O APIC input 0 is programmed
		 * as ExtINT to indicate that the PIC is the source of the
		 * interrupt.
		 */
		atpic->intr_raised = true;
		lapic_set_local_intr(vatpic->vm, -1, APIC_LVT_LINT0);
		vioapic_pulse_irq(vatpic->vm, 0);
	} else {
		VATPIC_CTR3(vatpic, "atpic master no eligible interrupts "
		    "(imr 0x%x irr 0x%x isr 0x%x)",
		    atpic->mask, atpic->request, atpic->service);
	}
}