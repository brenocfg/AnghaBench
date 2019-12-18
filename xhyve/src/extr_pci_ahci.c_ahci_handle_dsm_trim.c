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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct blockif_req {int br_resid; scalar_t__ br_offset; } ;
struct ahci_port {int pending; int /*<<< orphan*/  bctx; int /*<<< orphan*/  iobhd; int /*<<< orphan*/  iofhd; } ;
struct ahci_ioreq {int* cfis; int slot; int len; int done; int more; struct blockif_req io_req; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ATA_DATA_SET_MANAGEMENT ; 
 int ATA_S_DSC ; 
 int ATA_S_READY ; 
 struct ahci_ioreq* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct ahci_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_check_stopped (struct ahci_port*) ; 
 int /*<<< orphan*/  ahci_handle_port (struct ahci_port*) ; 
 int /*<<< orphan*/  ahci_write_fis_d2h (struct ahci_port*,int,int*,int) ; 
 int /*<<< orphan*/  ahci_write_fis_d2h_ncq (struct ahci_port*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int blockif_delete (int /*<<< orphan*/ ,struct blockif_req*) ; 
 scalar_t__ blockif_sectsz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_blist ; 
 int /*<<< orphan*/  io_flist ; 
 int /*<<< orphan*/  read_prdt (struct ahci_port*,int,int*,int*,int) ; 

__attribute__((used)) static void
ahci_handle_dsm_trim(struct ahci_port *p, int slot, uint8_t *cfis, uint32_t done)
{
	struct ahci_ioreq *aior;
	struct blockif_req *breq;
	uint8_t *entry;
	uint64_t elba;
	uint32_t len, elen;
	int err, first, ncq;
	uint8_t buf[512];

	first = (done == 0);
	if (cfis[2] == ATA_DATA_SET_MANAGEMENT) {
		len = (uint32_t) ((((uint16_t) cfis[13]) << 8) | cfis[12]);
		len *= 512;
		ncq = 0;
	} else { /* ATA_SEND_FPDMA_QUEUED */
		len = (uint32_t) ((((uint16_t) cfis[11]) << 8) | cfis[3]);
		len *= 512;
		ncq = 1;
	}
	read_prdt(p, slot, cfis, buf, sizeof(buf));

next:
	entry = &buf[done];
	elba = ((uint64_t)entry[5] << 40) |
		((uint64_t)entry[4] << 32) |
		((uint64_t)entry[3] << 24) |
		((uint64_t)entry[2] << 16) |
		((uint64_t)entry[1] << 8) |
		entry[0];
	elen = (uint32_t) ((((uint16_t) entry[7]) << 8) | entry[6]);
	done += 8;
	if (elen == 0) {
		if (done >= len) {
			ahci_write_fis_d2h(p, slot, cfis, ATA_S_READY | ATA_S_DSC);
			p->pending &= ~(1 << slot);
			ahci_check_stopped(p);
			if (!first)
				ahci_handle_port(p);
			return;
		}
		goto next;
	}

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
	aior->more = (len != done);

	breq = &aior->io_req;
	breq->br_offset = (off_t) (elba * ((uint64_t) blockif_sectsz(p->bctx)));
	breq->br_resid = elen * ((unsigned) blockif_sectsz(p->bctx));

	/*
	 * Mark this command in-flight.
	 */
	p->pending |= 1 << slot;

	/*
	 * Stuff request onto busy list
	 */
	TAILQ_INSERT_HEAD(&p->iobhd, aior, io_blist);

	if (ncq && first)
		ahci_write_fis_d2h_ncq(p, slot);

	err = blockif_delete(p->bctx, breq);
	assert(err == 0);
}