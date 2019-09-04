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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int table_count; scalar_t__ table; } ;
struct pci_devinst {TYPE_1__ pi_msix; } ;

/* Variables and functions */
 int MSIX_TABLE_ENTRY_SIZE ; 

int
pci_emul_msix_twrite(struct pci_devinst *pi, uint64_t offset, int size,
		     uint64_t value)
{
	int msix_entry_offset;
	int tab_index;
	char *dest;

	/* support only 4 or 8 byte writes */
	if (size != 4 && size != 8)
		return (-1);

	/*
	 * Return if table index is beyond what device supports
	 */
	tab_index = (int) (offset / MSIX_TABLE_ENTRY_SIZE);
	if (tab_index >= pi->pi_msix.table_count)
		return (-1);

	msix_entry_offset = offset % MSIX_TABLE_ENTRY_SIZE;

	/* support only aligned writes */
	if ((msix_entry_offset % size) != 0)
		return (-1);

	dest = (char *)(pi->pi_msix.table + tab_index);
	dest += msix_entry_offset;

	if (size == 4)
		*((uint32_t *)((void *) dest)) = (uint32_t) value;
	else
		*((uint64_t *)((void *) dest)) = value;

	return (0);
}