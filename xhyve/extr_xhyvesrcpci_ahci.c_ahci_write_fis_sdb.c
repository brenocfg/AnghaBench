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
struct ahci_port {int* err_cfis; int sact; unsigned int tfd; } ;
typedef  int /*<<< orphan*/  fis ;

/* Variables and functions */
 int ATA_S_ERROR ; 
 int FIS_TYPE_SETDEVBITS ; 
 int /*<<< orphan*/  ahci_write_fis (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahci_write_fis_sdb(struct ahci_port *p, int slot, uint8_t *cfis, uint32_t tfd)
{
	uint8_t fis[8];
	uint8_t error;

	error = (tfd >> 8) & 0xff;
	tfd &= 0x77;
	memset(fis, 0, sizeof(fis));
	fis[0] = FIS_TYPE_SETDEVBITS;
	fis[1] = (1 << 6);
	fis[2] = (uint8_t) tfd;
	fis[3] = error;
	if (fis[2] & ATA_S_ERROR) {
		p->err_cfis[0] = (uint8_t) slot;
		p->err_cfis[2] = (uint8_t) tfd;
		p->err_cfis[3] = error;
		memcpy(&p->err_cfis[4], cfis + 4, 16);
	} else {
		*(uint32_t *)((void *) (fis + 4)) = (1 << slot);
		p->sact &= ~(1 << slot);
	}
	p->tfd &= ~((unsigned) 0x77);
	p->tfd |= tfd;
	ahci_write_fis(p, FIS_TYPE_SETDEVBITS, fis);
}