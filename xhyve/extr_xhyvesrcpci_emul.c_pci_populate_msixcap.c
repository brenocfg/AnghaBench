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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct msixcap {int table_info; int pba_info; scalar_t__ msgctrl; int /*<<< orphan*/  capid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int PCIM_MSIX_BIR_MASK ; 
 int /*<<< orphan*/  PCIY_MSIX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (struct msixcap*,int) ; 

__attribute__((used)) static void
pci_populate_msixcap(struct msixcap *msixcap, int msgnum, int barnum,
		     uint32_t msix_tab_size)
{
	CTASSERT(sizeof(struct msixcap) == 12);

	assert(msix_tab_size % 4096 == 0);

	bzero(msixcap, sizeof(struct msixcap));
	msixcap->capid = PCIY_MSIX;

	/*
	 * Message Control Register, all fields set to
	 * zero except for the Table Size.
	 * Note: Table size N is encoded as N-1
	 */
	msixcap->msgctrl = (uint16_t) (msgnum - 1);

	/*
	 * MSI-X BAR setup:
	 * - MSI-X table start at offset 0
	 * - PBA table starts at a 4K aligned offset after the MSI-X table
	 */
	msixcap->table_info = barnum & PCIM_MSIX_BIR_MASK;
	msixcap->pba_info = msix_tab_size | (barnum & PCIM_MSIX_BIR_MASK);
}