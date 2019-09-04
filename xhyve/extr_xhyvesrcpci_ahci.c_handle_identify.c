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
typedef  int uint64_t ;
typedef  int uint16_t ;
struct ahci_port {char* ident; int mult_sectors; int xfermode; int ssts; int /*<<< orphan*/  bctx; scalar_t__ atapi; scalar_t__ cmd_lst; } ;
struct ahci_cmd_hdr {scalar_t__ prdtl; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int AHCI_CL_SIZE ; 
 int ATA_E_ABORT ; 
 int ATA_SATA_GEN1 ; 
 int ATA_SATA_GEN2 ; 
 int ATA_SATA_GEN3 ; 
 int ATA_SS_SPD_MASK ; 
 int ATA_SUPPORT_ADDRESS48 ; 
 int ATA_SUPPORT_DRAT ; 
 int ATA_SUPPORT_DSM_TRIM ; 
 int ATA_SUPPORT_FLUSHCACHE ; 
 int ATA_SUPPORT_FLUSHCACHE48 ; 
 int ATA_SUPPORT_LOOKAHEAD ; 
 int ATA_SUPPORT_NCQ ; 
 int ATA_SUPPORT_NOP ; 
 int ATA_SUPPORT_POWERMGT ; 
 int ATA_SUPPORT_RCVSND_FPDMA_QUEUED ; 
 int ATA_SUPPORT_RWLOGDMAEXT ; 
 int ATA_SUPPORT_RZAT ; 
 int ATA_SUPPORT_WRITECACHE ; 
 int ATA_S_DSC ; 
 int ATA_S_ERROR ; 
 int ATA_S_READY ; 
 int ATA_UDMA0 ; 
 int ATA_WDMA0 ; 
 int /*<<< orphan*/  ahci_checksum (int*,int) ; 
 int /*<<< orphan*/  ahci_write_fis_d2h (struct ahci_port*,int,int*,int) ; 
 int /*<<< orphan*/  ahci_write_fis_piosetup (struct ahci_port*) ; 
 int /*<<< orphan*/  ata_string (int*,char*,int) ; 
 int blockif_candelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blockif_chs (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int blockif_is_ro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blockif_psectsz (int /*<<< orphan*/ ,int*,int*) ; 
 int blockif_sectsz (int /*<<< orphan*/ ) ; 
 int blockif_size (int /*<<< orphan*/ ) ; 
 int ffsl (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_prdt (struct ahci_port*,int,int*,void*,int) ; 

__attribute__((used)) static void
handle_identify(struct ahci_port *p, int slot, uint8_t *cfis)
{
	struct ahci_cmd_hdr *hdr;

	hdr = (struct ahci_cmd_hdr *)((void *) (p->cmd_lst + slot * AHCI_CL_SIZE));
	if (p->atapi || hdr->prdtl == 0) {
		ahci_write_fis_d2h(p, slot, cfis,
		    (ATA_E_ABORT << 8) | ATA_S_READY | ATA_S_ERROR);
	} else {
		uint16_t buf[256];
		uint64_t sectors;
		int sectsz, psectsz, psectoff, candelete, ro;
		uint16_t cyl;
		uint8_t sech, heads;

		ro = blockif_is_ro(p->bctx);
		candelete = blockif_candelete(p->bctx);
		sectsz = blockif_sectsz(p->bctx);
		sectors = (uint64_t) (blockif_size(p->bctx) / sectsz);
		blockif_chs(p->bctx, &cyl, &heads, &sech);
		blockif_psectsz(p->bctx, &psectsz, &psectoff);
		memset(buf, 0, sizeof(buf));
		buf[0] = 0x0040;
		buf[1] = cyl;
		buf[3] = heads;
		buf[6] = sech;
		ata_string((uint8_t *)(buf+10), p->ident, 20);
		ata_string((uint8_t *)(buf+23), "001", 8);
		ata_string((uint8_t *)(buf+27), "BHYVE SATA DISK", 40);
		buf[47] = (0x8000 | 128);
		buf[48] = 0x1;
		buf[49] = (1 << 8 | 1 << 9 | 1 << 11);
		buf[50] = (1 << 14);
		buf[53] = (1 << 1 | 1 << 2);
		if (p->mult_sectors)
			buf[59] = (uint16_t) (0x100 | p->mult_sectors);
		if (sectors <= 0x0fffffff) {
			buf[60] = (uint16_t) sectors;
			buf[61] = (uint16_t)(sectors >> 16);
		} else {
			buf[60] = 0xffff;
			buf[61] = 0x0fff;
		}
		buf[63] = 0x7;
		if (p->xfermode & ATA_WDMA0)
			buf[63] |= (1 << ((p->xfermode & 7) + 8));
		buf[64] = 0x3;
		buf[65] = 120;
		buf[66] = 120;
		buf[67] = 120;
		buf[68] = 120;
		buf[69] = 0;
		buf[75] = 31;
		buf[76] = (ATA_SATA_GEN1 | ATA_SATA_GEN2 | ATA_SATA_GEN3 |
			   ATA_SUPPORT_NCQ);
		buf[77] = (ATA_SUPPORT_RCVSND_FPDMA_QUEUED |
			   (p->ssts & ATA_SS_SPD_MASK) >> 3);
		buf[80] = 0x3f0;
		buf[81] = 0x28;
		buf[82] = (ATA_SUPPORT_POWERMGT | ATA_SUPPORT_WRITECACHE|
			   ATA_SUPPORT_LOOKAHEAD | ATA_SUPPORT_NOP);
		buf[83] = (ATA_SUPPORT_ADDRESS48 | ATA_SUPPORT_FLUSHCACHE |
			   ATA_SUPPORT_FLUSHCACHE48 | 1 << 14);
		buf[84] = (1 << 14);
		buf[85] = (ATA_SUPPORT_POWERMGT | ATA_SUPPORT_WRITECACHE|
			   ATA_SUPPORT_LOOKAHEAD | ATA_SUPPORT_NOP);
		buf[86] = (ATA_SUPPORT_ADDRESS48 | ATA_SUPPORT_FLUSHCACHE |
			   ATA_SUPPORT_FLUSHCACHE48 | 1 << 15);
		buf[87] = (1 << 14);
		buf[88] = 0x7f;
		if (p->xfermode & ATA_UDMA0)
			buf[88] |= (1 << ((p->xfermode & 7) + 8));
		buf[100] = (uint16_t) sectors;
		buf[101] = (uint16_t) (sectors >> 16);
		buf[102] = (uint16_t) (sectors >> 32);
		buf[103] = (sectors >> 48);
		if (candelete && !ro) {
			buf[69] |= ATA_SUPPORT_RZAT | ATA_SUPPORT_DRAT;
			buf[105] = 1;
			buf[169] = ATA_SUPPORT_DSM_TRIM;
		}
		buf[106] = 0x4000;
		buf[209] = 0x4000;
		if (psectsz > sectsz) {
			buf[106] |= 0x2000;
			buf[106] |= ffsl(psectsz / sectsz) - 1;
			buf[209] |= (psectoff / sectsz);
		}
		if (sectsz > 512) {
			buf[106] |= 0x1000;
			buf[117] = (uint16_t) (sectsz / 2);
			buf[118] = (uint16_t) ((sectsz / 2) >> 16);
		}
		buf[119] = (ATA_SUPPORT_RWLOGDMAEXT | 1 << 14);
		buf[120] = (ATA_SUPPORT_RWLOGDMAEXT | 1 << 14);
		buf[222] = 0x1020;
		buf[255] = 0x00a5;
		ahci_checksum((uint8_t *)buf, sizeof(buf));
		ahci_write_fis_piosetup(p);
		write_prdt(p, slot, cfis, (void *)buf, sizeof(buf));
		ahci_write_fis_d2h(p, slot, cfis, ATA_S_DSC | ATA_S_READY);
	}
}