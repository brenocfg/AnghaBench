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
struct ahci_port {int cmd; int ci; int pending; int ccs; int tfd; scalar_t__ waitforclear; } ;

/* Variables and functions */
 scalar_t__ AHCI_P_CMD_CCS_MASK ; 
 int AHCI_P_CMD_CCS_SHIFT ; 
 int AHCI_P_CMD_ST ; 
 int ATA_S_BUSY ; 
 int ATA_S_DRQ ; 
 int /*<<< orphan*/  ahci_handle_slot (struct ahci_port*,int) ; 

__attribute__((used)) static void
ahci_handle_port(struct ahci_port *p)
{

	if (!(p->cmd & AHCI_P_CMD_ST))
		return;

	/*
	 * Search for any new commands to issue ignoring those that
	 * are already in-flight.  Stop if device is busy or in error.
	 */
	for (; (p->ci & ~p->pending) != 0; p->ccs = ((p->ccs + 1) & 31)) {
		if ((p->tfd & (ATA_S_BUSY | ATA_S_DRQ)) != 0)
			break;
		if (p->waitforclear)
			break;
		if ((p->ci & ~p->pending & (1 << p->ccs)) != 0) {
			p->cmd &= ~((unsigned) AHCI_P_CMD_CCS_MASK);
			p->cmd |= p->ccs << AHCI_P_CMD_CCS_SHIFT;
			ahci_handle_slot(p, ((int) p->ccs));
		}
	}
}