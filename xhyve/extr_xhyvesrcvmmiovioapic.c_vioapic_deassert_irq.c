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
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQSTATE_DEASSERT ; 
 int vioapic_set_irqstate (struct vm*,int,int /*<<< orphan*/ ) ; 

int
vioapic_deassert_irq(struct vm *vm, int irq)
{

	return (vioapic_set_irqstate(vm, irq, IRQSTATE_DEASSERT));
}