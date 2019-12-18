#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct slotinfo {TYPE_1__* si_intpins; } ;
struct TYPE_4__ {int /*<<< orphan*/  pin; } ;
struct pci_devinst {size_t pi_bus; size_t pi_slot; TYPE_2__ pi_lintr; } ;
struct businfo {struct slotinfo* slotinfo; } ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_3__ {int ii_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_INTPIN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct businfo** pci_businfo ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pci_lintr_request(struct pci_devinst *pi)
{
	struct businfo *bi;
	struct slotinfo *si;
	int bestpin, bestcount, pin;

	bi = pci_businfo[pi->pi_bus];
	assert(bi != NULL);

	/*
	 * Just allocate a pin from our slot.  The pin will be
	 * assigned IRQs later when interrupts are routed.
	 */
	si = &bi->slotinfo[pi->pi_slot];
	bestpin = 0;
	bestcount = si->si_intpins[0].ii_count;
	for (pin = 1; pin < 4; pin++) {
		if (si->si_intpins[pin].ii_count < bestcount) {
			bestpin = pin;
			bestcount = si->si_intpins[pin].ii_count;
		}
	}

	si->si_intpins[bestpin].ii_count++;
	pi->pi_lintr.pin = (int8_t) (bestpin + 1);
	pci_set_cfgdata8(pi, PCIR_INTPIN, ((uint8_t) (bestpin + 1)));
}