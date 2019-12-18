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

/* Variables and functions */
 int /*<<< orphan*/  LEVEL_TRIGGER ; 
 int /*<<< orphan*/  SCI_INT ; 
 int /*<<< orphan*/  pci_irq_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xh_vm_isa_set_irq_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sci_init(void)
{
	/*
	 * Mark ACPI's SCI as level trigger and bump its use count
	 * in the PIRQ router.
	 */
	pci_irq_use(SCI_INT);
	xh_vm_isa_set_irq_trigger(SCI_INT, LEVEL_TRIGGER);
}