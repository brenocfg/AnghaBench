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
struct ahci_port {int cmd; int waitforclear; unsigned int is; int /*<<< orphan*/  pr_sc; int /*<<< orphan*/ * rfis; } ;
typedef  enum sata_fis_type { ____Placeholder_sata_fis_type } sata_fis_type ;

/* Variables and functions */
 int AHCI_P_CMD_FRE ; 
 int AHCI_P_IX_DHR ; 
 int AHCI_P_IX_PS ; 
 int AHCI_P_IX_SDB ; 
 int AHCI_P_IX_TFE ; 
 int ATA_S_ERROR ; 
#define  FIS_TYPE_BIST 135 
#define  FIS_TYPE_DATA 134 
#define  FIS_TYPE_DMAACT 133 
#define  FIS_TYPE_DMASETUP 132 
#define  FIS_TYPE_PIOSETUP 131 
#define  FIS_TYPE_REGD2H 130 
#define  FIS_TYPE_REGH2D 129 
#define  FIS_TYPE_SETDEVBITS 128 
 int /*<<< orphan*/  WPRINTF (char*,int) ; 
 int /*<<< orphan*/  ahci_generate_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
ahci_write_fis(struct ahci_port *p, enum sata_fis_type ft, uint8_t *fis)
{
	int offset, len, irq;

	if (p->rfis == NULL || !(p->cmd & AHCI_P_CMD_FRE))
		return;

	switch (ft) {
	case FIS_TYPE_REGD2H:
		offset = 0x40;
		len = 20;
		irq = (fis[1] & (1 << 6)) ? AHCI_P_IX_DHR : 0;
		break;
	case FIS_TYPE_SETDEVBITS:
		offset = 0x58;
		len = 8;
		irq = (fis[1] & (1 << 6)) ? AHCI_P_IX_SDB : 0;
		break;
	case FIS_TYPE_PIOSETUP:
		offset = 0x20;
		len = 20;
		irq = (fis[1] & (1 << 6)) ? AHCI_P_IX_PS : 0;
		break;
	case FIS_TYPE_REGH2D:
	case FIS_TYPE_DMAACT:
	case FIS_TYPE_DMASETUP:
	case FIS_TYPE_DATA:
	case FIS_TYPE_BIST:
		WPRINTF("unsupported fis type %d\n", ft);
		return;
	}
	if (fis[2] & ATA_S_ERROR) {
		p->waitforclear = 1;
		irq |= AHCI_P_IX_TFE;
	}
	memcpy(p->rfis + offset, fis, len);
	if (irq) {
		p->is |= ((unsigned) irq);
		ahci_generate_intr(p->pr_sc);
	}
}