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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct ahci_prdt_entry {int dbc; int /*<<< orphan*/  dba; } ;
struct ahci_port {scalar_t__ cmd_lst; } ;
struct ahci_cmd_hdr {int prdtl; } ;

/* Variables and functions */
 int AHCI_CL_SIZE ; 
 int DBCMASK ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * paddr_guest2host (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
read_prdt(struct ahci_port *p, int slot, uint8_t *cfis,
		void *buf, int size)
{
	struct ahci_cmd_hdr *hdr;
	struct ahci_prdt_entry *prdt;
	void *to;
	int i, len;

	hdr = (struct ahci_cmd_hdr *)((void *) (p->cmd_lst + slot * AHCI_CL_SIZE));
	len = size;
	to = buf;
	prdt = (struct ahci_prdt_entry *)((void *) (cfis + 0x80));
	for (i = 0; i < hdr->prdtl && len; i++) {
		uint8_t *ptr;
		uint32_t dbcsz;
		int sublen;

		dbcsz = (prdt->dbc & DBCMASK) + 1;
		ptr = paddr_guest2host(prdt->dba, dbcsz);
		sublen = ((len < ((int) dbcsz)) ? len : ((int) dbcsz));
		memcpy(to, ptr, sublen);
		len -= sublen;
		to = (uint8_t *) (((uintptr_t) to) + ((uintptr_t) sublen));
		prdt++;
	}
}