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
struct slotinfo {TYPE_1__* si_funcs; } ;
struct businfo {struct slotinfo* slotinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fi_devi; } ;

/* Variables and functions */
 int MAXFUNCS ; 
 struct businfo** pci_businfo ; 

__attribute__((used)) static int
pci_emul_is_mfdev(int bus, int slot)
{
	struct businfo *bi;
	struct slotinfo *si;
	int f, numfuncs;

	numfuncs = 0;
	if ((bi = pci_businfo[bus]) != NULL) {
		si = &bi->slotinfo[slot];
		for (f = 0; f < MAXFUNCS; f++) {
			if (si->si_funcs[f].fi_devi != NULL) {
				numfuncs++;
			}
		}
	}
	return (numfuncs > 1);
}