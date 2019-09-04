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
struct vatpic {struct atpic* atpic; } ;
struct atpic {int ready; } ;
typedef  enum irqstate { ____Placeholder_irqstate } irqstate ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQSTATE_ASSERT 130 
#define  IRQSTATE_DEASSERT 129 
#define  IRQSTATE_PULSE 128 
 int /*<<< orphan*/  VATPIC_LOCK (struct vatpic*) ; 
 int /*<<< orphan*/  VATPIC_UNLOCK (struct vatpic*) ; 
 int /*<<< orphan*/  vatpic_set_pinstate (struct vatpic*,int,int) ; 
 struct vatpic* vm_atpic (struct vm*) ; 

__attribute__((used)) static int
vatpic_set_irqstate(struct vm *vm, int irq, enum irqstate irqstate)
{
	struct vatpic *vatpic;
	struct atpic *atpic;

	if (irq < 0 || irq > 15)
		return (EINVAL);

	vatpic = vm_atpic(vm);
	atpic = &vatpic->atpic[irq >> 3];

	if (atpic->ready == false)
		return (0);

	VATPIC_LOCK(vatpic);
	switch (irqstate) {
	case IRQSTATE_ASSERT:
		vatpic_set_pinstate(vatpic, irq, true);
		break;
	case IRQSTATE_DEASSERT:
		vatpic_set_pinstate(vatpic, irq, false);
		break;
	case IRQSTATE_PULSE:
		vatpic_set_pinstate(vatpic, irq, true);
		vatpic_set_pinstate(vatpic, irq, false);
		break;
	}
	VATPIC_UNLOCK(vatpic);

	return (0);
}