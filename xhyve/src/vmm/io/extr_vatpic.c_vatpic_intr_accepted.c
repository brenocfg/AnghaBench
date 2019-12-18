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
struct vm {int dummy; } ;
struct vatpic {TYPE_1__* atpic; } ;
struct TYPE_2__ {int irq_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VATPIC_LOCK (struct vatpic*) ; 
 int /*<<< orphan*/  VATPIC_UNLOCK (struct vatpic*) ; 
 int /*<<< orphan*/  vatpic_notify_intr (struct vatpic*) ; 
 int /*<<< orphan*/  vatpic_pin_accepted (TYPE_1__*,int) ; 
 struct vatpic* vm_atpic (struct vm*) ; 

void
vatpic_intr_accepted(struct vm *vm, int vector)
{
	struct vatpic *vatpic;
	int pin;

	vatpic = vm_atpic(vm);

	VATPIC_LOCK(vatpic);

	pin = vector & 0x7;

	if ((vector & ~0x7) == vatpic->atpic[1].irq_base) {
		vatpic_pin_accepted(&vatpic->atpic[1], pin);
		/*
		 * If this vector originated from the slave,
		 * accept the cascaded interrupt too.
		 */
		vatpic_pin_accepted(&vatpic->atpic[0], 2);
	} else {
		vatpic_pin_accepted(&vatpic->atpic[0], pin);
	}

	vatpic_notify_intr(vatpic);

	VATPIC_UNLOCK(vatpic);
}