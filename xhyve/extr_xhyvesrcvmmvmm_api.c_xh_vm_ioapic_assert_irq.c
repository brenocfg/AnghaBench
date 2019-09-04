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
 int vioapic_assert_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm ; 

int
xh_vm_ioapic_assert_irq(int irq)
{
	return (vioapic_assert_irq(vm, irq));
}