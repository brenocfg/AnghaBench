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
struct vatpic {int* elc; } ;
typedef  enum vm_intr_trigger { ____Placeholder_vm_intr_trigger } vm_intr_trigger ;

/* Variables and functions */
 int EINVAL ; 
 int LEVEL_TRIGGER ; 
 int /*<<< orphan*/  VATPIC_LOCK (struct vatpic*) ; 
 int /*<<< orphan*/  VATPIC_UNLOCK (struct vatpic*) ; 
 struct vatpic* vm_atpic (struct vm*) ; 

int
vatpic_set_irq_trigger(struct vm *vm, int irq, enum vm_intr_trigger trigger)
{
	struct vatpic *vatpic;

	if (irq < 0 || irq > 15)
		return (EINVAL);

	/*
	 * See comment in vatpic_elc_handler.  These IRQs must be
	 * edge triggered.
	 */
	if (trigger == LEVEL_TRIGGER) {
		switch (irq) {
		case 0:
		case 1:
		case 2:
		case 8:
		case 13:
			return (EINVAL);
		}
	}

	vatpic = vm_atpic(vm);

	VATPIC_LOCK(vatpic);

	if (trigger == LEVEL_TRIGGER)
		vatpic->elc[irq >> 3] |=  1 << (irq & 0x7);
	else
		vatpic->elc[irq >> 3] &=  ~(1 << (irq & 0x7));

	VATPIC_UNLOCK(vatpic);

	return (0);
}