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
typedef  int uint64_t ;
struct pci_devinst {TYPE_1__* pi_bar; } ;
struct TYPE_2__ {scalar_t__ type; int addr; } ;

/* Variables and functions */
#define  PCIBAR_IO 131 
#define  PCIBAR_MEM32 130 
#define  PCIBAR_MEM64 129 
#define  PCIBAR_MEMHI64 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int memen (struct pci_devinst*) ; 
 int porten (struct pci_devinst*) ; 
 int /*<<< orphan*/  register_bar (struct pci_devinst*,int) ; 
 int /*<<< orphan*/  unregister_bar (struct pci_devinst*,int) ; 

__attribute__((used)) static void
update_bar_address(struct  pci_devinst *pi, uint64_t addr, int idx, int type)
{
	int decode;

	if (pi->pi_bar[idx].type == PCIBAR_IO)
		decode = porten(pi);
	else
		decode = memen(pi);

	if (decode)
		unregister_bar(pi, idx);

	switch (type) {
	case PCIBAR_IO:
	case PCIBAR_MEM32:
		pi->pi_bar[idx].addr = addr;
		break;
	case PCIBAR_MEM64:
		pi->pi_bar[idx].addr &= ~0xffffffffUL;
		pi->pi_bar[idx].addr |= addr;
		break;
	case PCIBAR_MEMHI64:
		pi->pi_bar[idx].addr &= 0xffffffff;
		pi->pi_bar[idx].addr |= addr;
		break;
	default:
		assert(0);
	}

	if (decode)
		register_bar(pi, idx);
}