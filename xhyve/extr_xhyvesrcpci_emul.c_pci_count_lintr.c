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
struct slotinfo {TYPE_1__* si_intpins; } ;
struct TYPE_4__ {struct slotinfo* slotinfo; } ;
struct TYPE_3__ {scalar_t__ ii_count; } ;

/* Variables and functions */
 int MAXSLOTS ; 
 TYPE_2__** pci_businfo ; 

int
pci_count_lintr(int bus)
{
	int count, slot, pin;
	struct slotinfo *slotinfo;

	count = 0;
	if (pci_businfo[bus] != NULL) {
		for (slot = 0; slot < MAXSLOTS; slot++) {
			slotinfo = &pci_businfo[bus]->slotinfo[slot];
			for (pin = 0; pin < 4; pin++) {
				if (slotinfo->si_intpins[pin].ii_count != 0)
					count++;
			}
		}
	}
	return (count);
}