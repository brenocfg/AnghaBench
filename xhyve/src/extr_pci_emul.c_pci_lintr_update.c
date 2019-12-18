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
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  lock; } ;
struct pci_devinst {TYPE_1__ pi_lintr; } ;

/* Variables and functions */
 scalar_t__ ASSERTED ; 
 scalar_t__ PENDING ; 
 int /*<<< orphan*/  pci_irq_assert (struct pci_devinst*) ; 
 int /*<<< orphan*/  pci_irq_deassert (struct pci_devinst*) ; 
 scalar_t__ pci_lintr_permitted (struct pci_devinst*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pci_lintr_update(struct pci_devinst *pi)
{

	pthread_mutex_lock(&pi->pi_lintr.lock);
	if (pi->pi_lintr.state == ASSERTED && !pci_lintr_permitted(pi)) {
		pci_irq_deassert(pi);
		pi->pi_lintr.state = PENDING;
	} else if (pi->pi_lintr.state == PENDING && pci_lintr_permitted(pi)) {
		pi->pi_lintr.state = ASSERTED;
		pci_irq_assert(pi);
	}
	pthread_mutex_unlock(&pi->pi_lintr.lock);
}