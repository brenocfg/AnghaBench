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
typedef  int uint32_t ;
struct ahci_port {int sense_key; int asc; } ;

/* Variables and functions */
 int ATA_I_CMD ; 
 int ATA_I_IN ; 
 int ATA_SENSE_ILLEGAL_REQUEST ; 
 int ATA_S_DSC ; 
 int ATA_S_ERROR ; 
 int ATA_S_READY ; 
 int /*<<< orphan*/  ahci_write_fis_d2h (struct ahci_port*,int,int*,int) ; 

__attribute__((used)) static void
atapi_start_stop_unit(struct ahci_port *p, int slot, uint8_t *cfis)
{
	uint8_t *acmd = cfis + 0x40;
	uint32_t tfd;

	tfd = 0;

	switch (acmd[4] & 3) {
	case 0:
	case 1:
	case 3:
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		tfd = ATA_S_READY | ATA_S_DSC;
		break;
	case 2:
		/* TODO eject media */
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		p->sense_key = ATA_SENSE_ILLEGAL_REQUEST;
		p->asc = 0x53;
		tfd = (uint32_t) ((p->sense_key << 12) | ATA_S_READY | ATA_S_ERROR);
		break;
	}
	ahci_write_fis_d2h(p, slot, cfis, tfd);
}