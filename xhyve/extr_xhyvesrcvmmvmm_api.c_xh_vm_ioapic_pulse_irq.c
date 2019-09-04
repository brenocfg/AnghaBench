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
 int vioapic_pulse_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm ; 

int
xh_vm_ioapic_pulse_irq(int irq)
{
	return (vioapic_pulse_irq(vm, irq));
}