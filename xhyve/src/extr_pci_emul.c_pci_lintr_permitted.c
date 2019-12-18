#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_3__ {scalar_t__ enabled; } ;
struct pci_devinst {TYPE_2__ pi_msix; TYPE_1__ pi_msi; } ;

/* Variables and functions */
 int PCIM_CMD_INTxDIS ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int pci_get_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
pci_lintr_permitted(struct pci_devinst *pi)
{
	uint16_t cmd;

	cmd = pci_get_cfgdata16(pi, PCIR_COMMAND);
	return (!(pi->pi_msi.enabled || pi->pi_msix.enabled ||
		(cmd & PCIM_CMD_INTxDIS)));
}