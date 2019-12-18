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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int table_bar; int pba_bar; int table_count; scalar_t__ pba_size; scalar_t__ pba_offset; scalar_t__ table_offset; } ;
struct pci_devinst {TYPE_1__ pi_msix; } ;
struct msixcap {int dummy; } ;
typedef  int /*<<< orphan*/  msixcap ;

/* Variables and functions */
 int MAX_MSIX_TABLE_ENTRIES ; 
 int MSIX_TABLE_ENTRY_SIZE ; 
 scalar_t__ PBA_SIZE (int) ; 
 int /*<<< orphan*/  PCIBAR_MEM32 ; 
 int PCIR_MAX_BAR_0 ; 
 int /*<<< orphan*/  assert (int) ; 
 int pci_emul_add_capability (struct pci_devinst*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_emul_alloc_bar (struct pci_devinst*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_msix_table_init (struct pci_devinst*,int) ; 
 int /*<<< orphan*/  pci_populate_msixcap (struct msixcap*,int,int,scalar_t__) ; 
 scalar_t__ roundup2 (scalar_t__,unsigned int) ; 

int
pci_emul_add_msixcap(struct pci_devinst *pi, int msgnum, int barnum)
{
	uint32_t tab_size;
	struct msixcap msixcap;

	assert(msgnum >= 1 && msgnum <= MAX_MSIX_TABLE_ENTRIES);
	assert(barnum >= 0 && barnum <= PCIR_MAX_BAR_0);
	
	tab_size = (uint32_t) (msgnum * MSIX_TABLE_ENTRY_SIZE);

	/* Align table size to nearest 4K */
	tab_size = roundup2(tab_size, 4096u);

	pi->pi_msix.table_bar = barnum;
	pi->pi_msix.pba_bar   = barnum;
	pi->pi_msix.table_offset = 0;
	pi->pi_msix.table_count = msgnum;
	pi->pi_msix.pba_offset = tab_size;
	pi->pi_msix.pba_size = PBA_SIZE(msgnum);

	pci_msix_table_init(pi, msgnum);

	pci_populate_msixcap(&msixcap, msgnum, barnum, tab_size);

	/* allocate memory for MSI-X Table and PBA */
	pci_emul_alloc_bar(pi, barnum, PCIBAR_MEM32,
		(tab_size + ((uint32_t) pi->pi_msix.pba_size)));

	return (pci_emul_add_capability(pi, (u_char *)&msixcap,
					sizeof(msixcap)));
}