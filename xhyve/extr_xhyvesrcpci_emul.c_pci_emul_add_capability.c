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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct pci_devinst {int pi_capend; int pi_prevcap; } ;

/* Variables and functions */
 int CAP_START_OFFSET ; 
 int PCIM_STATUS_CAPPRESENT ; 
 int PCIR_CAP_PTR ; 
 int /*<<< orphan*/  PCIR_STATUS ; 
 int PCI_REGMAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int pci_get_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int,int /*<<< orphan*/ ) ; 
 int roundup2 (int,int) ; 

__attribute__((used)) static int
pci_emul_add_capability(struct pci_devinst *pi, u_char *capdata, int caplen)
{
	int i, capoff, reallen;
	uint16_t sts;

	assert(caplen > 0);

	reallen = roundup2(caplen, 4);		/* dword aligned */

	sts = pci_get_cfgdata16(pi, PCIR_STATUS);
	if ((sts & PCIM_STATUS_CAPPRESENT) == 0)
		capoff = CAP_START_OFFSET;
	else
		capoff = pi->pi_capend + 1;

	/* Check if we have enough space */
	if (capoff + reallen > PCI_REGMAX + 1)
		return (-1);

	/* Set the previous capability pointer */
	if ((sts & PCIM_STATUS_CAPPRESENT) == 0) {
		pci_set_cfgdata8(pi, PCIR_CAP_PTR, ((uint8_t) capoff));
		pci_set_cfgdata16(pi, PCIR_STATUS, sts|PCIM_STATUS_CAPPRESENT);
	} else
		pci_set_cfgdata8(pi, pi->pi_prevcap + 1, ((uint8_t) capoff));

	/* Copy the capability */
	for (i = 0; i < caplen; i++)
		pci_set_cfgdata8(pi, capoff + i, capdata[i]);

	/* Set the next capability pointer */
	pci_set_cfgdata8(pi, capoff + 1, 0);

	pi->pi_prevcap = capoff;
	pi->pi_capend = capoff + reallen - 1;
	return (0);
}