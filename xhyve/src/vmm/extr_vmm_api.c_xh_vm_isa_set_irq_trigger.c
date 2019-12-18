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
typedef  enum vm_intr_trigger { ____Placeholder_vm_intr_trigger } vm_intr_trigger ;

/* Variables and functions */
 int vatpic_set_irq_trigger (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vm ; 

int
xh_vm_isa_set_irq_trigger(int atpic_irq, enum vm_intr_trigger trigger)
{
	return (vatpic_set_irq_trigger(vm, atpic_irq, trigger));
}