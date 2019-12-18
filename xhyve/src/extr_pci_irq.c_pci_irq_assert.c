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
struct pirq {int active_count; int reg; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int pirq_pin; int /*<<< orphan*/  ioapic_irq; } ;
struct pci_devinst {TYPE_1__ pi_lintr; } ;

/* Variables and functions */
 int PIRQ_IRQ ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int nitems (struct pirq*) ; 
 scalar_t__ pirq_valid_irq (int) ; 
 struct pirq* pirqs ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xh_vm_ioapic_assert_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xh_vm_isa_assert_irq (int,int /*<<< orphan*/ ) ; 

void
pci_irq_assert(struct pci_devinst *pi)
{
	struct pirq *pirq;

	if (pi->pi_lintr.pirq_pin > 0) {
		assert(((unsigned) pi->pi_lintr.pirq_pin) <= nitems(pirqs));
		pirq = &pirqs[pi->pi_lintr.pirq_pin - 1];
		pthread_mutex_lock(&pirq->lock);
		pirq->active_count++;
		if (pirq->active_count == 1 && pirq_valid_irq(pirq->reg)) {
			xh_vm_isa_assert_irq(pirq->reg & PIRQ_IRQ, pi->pi_lintr.ioapic_irq);
			pthread_mutex_unlock(&pirq->lock);
			return;
		}
		pthread_mutex_unlock(&pirq->lock);
	}
	xh_vm_ioapic_assert_irq(pi->pi_lintr.ioapic_irq);
}