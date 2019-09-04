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
typedef  scalar_t__ uint64_t ;
struct pci_devinst {TYPE_1__* pi_bar; struct pci_devemu* pi_d; } ;
struct pci_devemu {scalar_t__ (* pe_barread ) (int,struct pci_devinst*,int,scalar_t__,int) ;int /*<<< orphan*/  (* pe_barwrite ) (int,struct pci_devinst*,int,scalar_t__,int,scalar_t__) ;} ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ addr; scalar_t__ size; } ;

/* Variables and functions */
 int MEM_F_WRITE ; 
 scalar_t__ PCIBAR_MEM32 ; 
 scalar_t__ PCIBAR_MEM64 ; 
 int PCI_BARMAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int,struct pci_devinst*,int,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int,struct pci_devinst*,int,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int,struct pci_devinst*,int,scalar_t__,int,scalar_t__) ; 
 scalar_t__ stub4 (int,struct pci_devinst*,int,scalar_t__,int) ; 
 int stub5 (int,struct pci_devinst*,int,scalar_t__,int) ; 
 scalar_t__ stub6 (int,struct pci_devinst*,int,scalar_t__,int) ; 

__attribute__((used)) static int
pci_emul_mem_handler(int vcpu, int dir, uint64_t addr,
		     int size, uint64_t *val, void *arg1, long arg2)
{
	struct pci_devinst *pdi = arg1;
	struct pci_devemu *pe = pdi->pi_d;
	uint64_t offset;
	int bidx = (int) arg2;

	assert(bidx <= PCI_BARMAX);
	assert((pdi->pi_bar[bidx].type == PCIBAR_MEM32) ||
		(pdi->pi_bar[bidx].type == PCIBAR_MEM64));
	assert((addr >= pdi->pi_bar[bidx].addr) &&
		((addr + ((uint64_t) size)) <=
			(pdi->pi_bar[bidx].addr + pdi->pi_bar[bidx].size)));

	offset = addr - pdi->pi_bar[bidx].addr;

	if (dir == MEM_F_WRITE) {
		if (size == 8) {
			(*pe->pe_barwrite)(vcpu, pdi, bidx, offset, 4, *val & 0xffffffff);
			(*pe->pe_barwrite)(vcpu, pdi, bidx, offset + 4, 4, *val >> 32);
		} else {
			(*pe->pe_barwrite)(vcpu, pdi, bidx, offset, size, *val);
		}
	} else {
		if (size == 8) {
			*val = (*pe->pe_barread)(vcpu, pdi, bidx, offset, 4);
			*val |= (*pe->pe_barread)(vcpu, pdi, bidx, offset + 4, 4) << 32;
		} else {
			*val = (*pe->pe_barread)(vcpu, pdi, bidx, offset, size);
		}
	}

	return (0);
}