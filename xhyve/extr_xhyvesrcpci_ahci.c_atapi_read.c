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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct pci_ahci_softc {int dummy; } ;
struct blockif_req {scalar_t__ br_offset; } ;
struct ahci_prdt_entry {int dummy; } ;
struct ahci_port {int pending; int /*<<< orphan*/  bctx; int /*<<< orphan*/  iobhd; int /*<<< orphan*/  iofhd; scalar_t__ cmd_lst; struct pci_ahci_softc* pr_sc; } ;
struct ahci_ioreq {scalar_t__* cfis; int slot; int len; int done; struct blockif_req io_req; } ;
struct ahci_cmd_hdr {int /*<<< orphan*/  prdtl; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int AHCI_CL_SIZE ; 
 scalar_t__ ATA_I_CMD ; 
 scalar_t__ ATA_I_IN ; 
 int ATA_S_DSC ; 
 int ATA_S_READY ; 
 scalar_t__ READ_10 ; 
 struct ahci_ioreq* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct ahci_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_build_iov (struct ahci_port*,struct ahci_ioreq*,struct ahci_prdt_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_write_fis_d2h (struct ahci_port*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int be16dec (scalar_t__*) ; 
 int be32dec (scalar_t__*) ; 
 int blockif_read (int /*<<< orphan*/ ,struct blockif_req*) ; 
 int /*<<< orphan*/  io_blist ; 
 int /*<<< orphan*/  io_flist ; 

__attribute__((used)) static void
atapi_read(struct ahci_port *p, int slot, uint8_t *cfis, uint32_t done)
{
	struct ahci_ioreq *aior;
	struct ahci_cmd_hdr *hdr;
	struct ahci_prdt_entry *prdt;
	struct blockif_req *breq;
	struct pci_ahci_softc *sc;
	uint8_t *acmd;
	uint64_t lba;
	uint32_t len;
	int err;

	sc = p->pr_sc;
	acmd = cfis + 0x40;
	hdr = (struct ahci_cmd_hdr *)((void *) (p->cmd_lst + slot * AHCI_CL_SIZE));
	prdt = (struct ahci_prdt_entry *)((void *) (cfis + 0x80));

	lba = be32dec(acmd + 2);
	if (acmd[0] == READ_10)
		len = be16dec(acmd + 7);
	else
		len = be32dec(acmd + 6);
	if (len == 0) {
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		ahci_write_fis_d2h(p, slot, cfis, ATA_S_READY | ATA_S_DSC);
	}
	lba *= 2048;
	len *= 2048;

	/*
	 * Pull request off free list
	 */
	aior = STAILQ_FIRST(&p->iofhd);
	assert(aior != NULL);
	STAILQ_REMOVE_HEAD(&p->iofhd, io_flist);
	aior->cfis = cfis;
	aior->slot = slot;
	aior->len = len;
	aior->done = done;
	breq = &aior->io_req;
	breq->br_offset = (off_t) (lba + ((uint64_t) done));
	ahci_build_iov(p, aior, prdt, hdr->prdtl);

	/* Mark this command in-flight. */
	p->pending |= 1 << slot;

	/* Stuff request onto busy list. */
	TAILQ_INSERT_HEAD(&p->iobhd, aior, io_blist);

	err = blockif_read(p->bctx, breq);
	assert(err == 0);
}