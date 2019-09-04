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
typedef  int uint32_t ;
struct pci_devinst {TYPE_1__* pi_bar; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int CFGREAD (struct pci_devinst*,int,int) ; 
 int /*<<< orphan*/  CFGWRITE (struct pci_devinst*,int,int,int) ; 
#define  PCIBAR_IO 132 
#define  PCIBAR_MEM32 131 
#define  PCIBAR_MEM64 130 
#define  PCIBAR_MEMHI64 129 
#define  PCIBAR_NONE 128 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_PORTEN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int PCI_BARMAX ; 
 int /*<<< orphan*/  memen (struct pci_devinst*) ; 
 int pci_get_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lintr_update (struct pci_devinst*) ; 
 int /*<<< orphan*/  porten (struct pci_devinst*) ; 
 int /*<<< orphan*/  register_bar (struct pci_devinst*,int) ; 
 int /*<<< orphan*/  unregister_bar (struct pci_devinst*,int) ; 

__attribute__((used)) static void
pci_emul_cmdsts_write(struct pci_devinst *pi, int coff, uint32_t new, int bytes)
{
	int i, rshift;
	uint32_t cmd, cmd2, changed, old, readonly;

	cmd = pci_get_cfgdata16(pi, PCIR_COMMAND);	/* stash old value */

	/*
	 * From PCI Local Bus Specification 3.0 sections 6.2.2 and 6.2.3.
	 *
	 * XXX Bits 8, 11, 12, 13, 14 and 15 in the status register are
	 * 'write 1 to clear'. However these bits are not set to '1' by
	 * any device emulation so it is simpler to treat them as readonly.
	 */
	rshift = (coff & 0x3) * 8;
	readonly = 0xFFFFF880 >> rshift;

	old = CFGREAD(pi, coff, bytes);
	new &= ~readonly;
	new |= (old & readonly);
	CFGWRITE(pi, coff, new, bytes);			/* update config */

	cmd2 = pci_get_cfgdata16(pi, PCIR_COMMAND);	/* get updated value */
	changed = cmd ^ cmd2;

	/*
	 * If the MMIO or I/O address space decoding has changed then
	 * register/unregister all BARs that decode that address space.
	 */
	for (i = 0; i <= PCI_BARMAX; i++) {
		switch (pi->pi_bar[i].type) {
			case PCIBAR_NONE:
			case PCIBAR_MEMHI64:
				break;
			case PCIBAR_IO:
				/* I/O address space decoding changed? */
				if (changed & PCIM_CMD_PORTEN) {
					if (porten(pi))
						register_bar(pi, i);
					else
						unregister_bar(pi, i);
				}
				break;
			case PCIBAR_MEM32:
			case PCIBAR_MEM64:
				/* MMIO address space decoding changed? */
				if (changed & PCIM_CMD_MEMEN) {
					if (memen(pi))
						register_bar(pi, i);
					else
						unregister_bar(pi, i);
				}
				break;
		}
	}

	/*
	 * If INTx has been unmasked and is pending, assert the
	 * interrupt.
	 */
	pci_lintr_update(pi);
}