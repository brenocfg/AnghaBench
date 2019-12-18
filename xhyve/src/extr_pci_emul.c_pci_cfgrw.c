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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct slotinfo {TYPE_1__* si_funcs; } ;
struct pci_devinst {TYPE_2__* pi_bar; struct pci_devemu* pi_d; } ;
struct pci_devemu {int (* pe_cfgread ) (int,struct pci_devinst*,int,int,int*) ;scalar_t__ (* pe_cfgwrite ) (int,struct pci_devinst*,int,int,int) ;} ;
struct businfo {struct slotinfo* slotinfo; } ;
struct TYPE_4__ {int size; int type; int addr; } ;
struct TYPE_3__ {struct pci_devinst* fi_devi; } ;

/* Variables and functions */
 int CFGREAD (struct pci_devinst*,int,int) ; 
 int /*<<< orphan*/  CFGWRITE (struct pci_devinst*,int,int,int) ; 
#define  PCIBAR_IO 132 
#define  PCIBAR_MEM32 131 
#define  PCIBAR_MEM64 130 
#define  PCIBAR_MEMHI64 129 
#define  PCIBAR_NONE 128 
 int PCIM_BAR_IO_SPACE ; 
 int PCIM_BAR_MEM_32 ; 
 int PCIM_BAR_MEM_64 ; 
 int PCIM_BAR_MEM_PREFETCH ; 
 int PCIM_BAR_MEM_SPACE ; 
 int PCIR_BAR (scalar_t__) ; 
 int PCIR_COMMAND ; 
 int PCIR_REVID ; 
 scalar_t__ PCI_BARMAX ; 
 int PCI_REGMAX ; 
 struct businfo** pci_businfo ; 
 int /*<<< orphan*/  pci_emul_capwrite (struct pci_devinst*,int,int,int) ; 
 int /*<<< orphan*/  pci_emul_cmdsts_write (struct pci_devinst*,int,int,int) ; 
 int /*<<< orphan*/  pci_emul_hdrtype_fixup (int,int,int,int,int*) ; 
 scalar_t__ pci_emul_iscap (struct pci_devinst*,int) ; 
 int /*<<< orphan*/  pci_set_cfgdata32 (struct pci_devinst*,int,int) ; 
 int stub1 (int,struct pci_devinst*,int,int,int*) ; 
 scalar_t__ stub2 (int,struct pci_devinst*,int,int,int) ; 
 int /*<<< orphan*/  update_bar_address (struct pci_devinst*,int,int,int const) ; 

__attribute__((used)) static void
pci_cfgrw(int vcpu, int in, int bus, int slot, int func, int coff, int bytes,
	uint32_t *eax)
{
	struct businfo *bi;
	struct slotinfo *si;
	struct pci_devinst *pi;
	struct pci_devemu *pe;
	int idx, needcfg;
	uint64_t addr, bar, mask;

	if ((bi = pci_businfo[bus]) != NULL) {
		si = &bi->slotinfo[slot];
		pi = si->si_funcs[func].fi_devi;
	} else
		pi = NULL;

	/*
	 * Just return if there is no device at this slot:func or if the
	 * the guest is doing an un-aligned access.
	 */
	if (pi == NULL || (bytes != 1 && bytes != 2 && bytes != 4) ||
	    (coff & (bytes - 1)) != 0) {
		if (in)
			*eax = 0xffffffff;
		return;
	}

	/*
	 * Ignore all writes beyond the standard config space and return all
	 * ones on reads.
	 */
	if (coff >= PCI_REGMAX + 1) {
		if (in) {
			*eax = 0xffffffff;
			/*
			 * Extended capabilities begin at offset 256 in config
			 * space. Absence of extended capabilities is signaled
			 * with all 0s in the extended capability header at
			 * offset 256.
			 */
			if (coff <= PCI_REGMAX + 4)
				*eax = 0x00000000;
		}
		return;
	}

	pe = pi->pi_d;

	/*
	 * Config read
	 */
	if (in) {
		/* Let the device emulation override the default handler */
		if (pe->pe_cfgread != NULL) {
			needcfg = pe->pe_cfgread(vcpu, pi, coff, bytes,
			    eax);
		} else {
			needcfg = 1;
		}

		if (needcfg)
			*eax = CFGREAD(pi, coff, bytes);

		pci_emul_hdrtype_fixup(bus, slot, coff, bytes, eax);
	} else {
		/* Let the device emulation override the default handler */
		if (pe->pe_cfgwrite != NULL &&
		    (*pe->pe_cfgwrite)(vcpu, pi, coff, bytes, *eax) == 0)
			return;

		/*
		 * Special handling for write to BAR registers
		 */
		if (coff >= PCIR_BAR(0) && coff < PCIR_BAR(PCI_BARMAX + 1)) {
			/*
			 * Ignore writes to BAR registers that are not
			 * 4-byte aligned.
			 */
			if (bytes != 4 || (coff & 0x3) != 0)
				return;
			idx = (coff - PCIR_BAR(0)) / 4;
			mask = ~(pi->pi_bar[idx].size - 1);
			switch (pi->pi_bar[idx].type) {
			case PCIBAR_NONE:
				pi->pi_bar[idx].addr = bar = 0;
				break;
			case PCIBAR_IO:
				addr = *eax & mask;
				addr &= 0xffff;
				bar = addr | PCIM_BAR_IO_SPACE;
				/*
				 * Register the new BAR value for interception
				 */
				if (addr != pi->pi_bar[idx].addr) {
					update_bar_address(pi, addr, idx,
							   PCIBAR_IO);
				}
				break;
			case PCIBAR_MEM32:
				addr = bar = *eax & mask;
				bar |= PCIM_BAR_MEM_SPACE | PCIM_BAR_MEM_32;
				if (addr != pi->pi_bar[idx].addr) {
					update_bar_address(pi, addr, idx,
							   PCIBAR_MEM32);
				}
				break;
			case PCIBAR_MEM64:
				addr = bar = *eax & mask;
				bar |= PCIM_BAR_MEM_SPACE | PCIM_BAR_MEM_64 |
				       PCIM_BAR_MEM_PREFETCH;
				if (addr != (uint32_t)pi->pi_bar[idx].addr) {
					update_bar_address(pi, addr, idx,
							   PCIBAR_MEM64);
				}
				break;
			case PCIBAR_MEMHI64:
				mask = ~(pi->pi_bar[idx - 1].size - 1);
				addr = ((uint64_t)*eax << 32) & mask;
				bar = addr >> 32;
				if (bar != pi->pi_bar[idx - 1].addr >> 32) {
					update_bar_address(pi, addr, idx - 1,
							   PCIBAR_MEMHI64);
				}
				break;
			}
			pci_set_cfgdata32(pi, coff, ((uint32_t) bar));

		} else if (pci_emul_iscap(pi, coff)) {
			pci_emul_capwrite(pi, coff, bytes, *eax);
		} else if (coff >= PCIR_COMMAND && coff < PCIR_REVID) {
			pci_emul_cmdsts_write(pi, coff, *eax, bytes);
		} else {
			CFGWRITE(pi, coff, *eax, bytes);
		}
	}
}