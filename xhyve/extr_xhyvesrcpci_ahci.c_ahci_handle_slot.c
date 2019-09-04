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
typedef  int uint8_t ;
struct pci_ahci_softc {int dummy; } ;
struct ahci_prdt_entry {int dummy; } ;
struct ahci_port {int reset; int ci; scalar_t__ cmd_lst; struct pci_ahci_softc* pr_sc; } ;
struct ahci_cmd_hdr {int flags; int prdtl; int /*<<< orphan*/  ctba; } ;

/* Variables and functions */
 int AHCI_CL_SIZE ; 
 int FIS_TYPE_REGH2D ; 
 int /*<<< orphan*/  WPRINTF (char*,int) ; 
 int /*<<< orphan*/  ahci_handle_cmd (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  ahci_port_reset (struct ahci_port*) ; 
 int* paddr_guest2host (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahci_handle_slot(struct ahci_port *p, int slot)
{
	struct ahci_cmd_hdr *hdr;
	struct ahci_prdt_entry *prdt;
	struct pci_ahci_softc *sc;
	uint8_t *cfis;
	int cfl;

	sc = p->pr_sc;
	hdr = (struct ahci_cmd_hdr *)((void *) (p->cmd_lst + slot * AHCI_CL_SIZE));
	cfl = (hdr->flags & 0x1f) * 4;
	cfis = paddr_guest2host(hdr->ctba,
		0x80 + hdr->prdtl * sizeof(struct ahci_prdt_entry));
	prdt = (struct ahci_prdt_entry *)((void *) (cfis + 0x80));

#ifdef AHCI_DEBUG
	DPRINTF("\ncfis:");
	for (i = 0; i < cfl; i++) {
		if (i % 10 == 0)
			DPRINTF("\n");
		DPRINTF("%02x ", cfis[i]);
	}
	DPRINTF("\n");

	for (i = 0; i < hdr->prdtl; i++) {
		DPRINTF("%d@%08"PRIx64"\n", prdt->dbc & 0x3fffff, prdt->dba);
		prdt++;
	}
#endif

	if (cfis[0] != FIS_TYPE_REGH2D) {
		WPRINTF("Not a H2D FIS:%02x\n", cfis[0]);
		return;
	}

	if (cfis[1] & 0x80) {
		ahci_handle_cmd(p, slot, cfis);
	} else {
		if (cfis[15] & (1 << 2))
			p->reset = 1;
		else if (p->reset) {
			p->reset = 0;
			ahci_port_reset(p);
		}
		p->ci &= ~(1 << slot);
	}
}