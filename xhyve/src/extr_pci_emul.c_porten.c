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
typedef  int uint16_t ;
struct pci_devinst {int dummy; } ;

/* Variables and functions */
 int PCIM_CMD_PORTEN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int pci_get_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
porten(struct pci_devinst *pi)
{
	uint16_t cmd;

	cmd = pci_get_cfgdata16(pi, PCIR_COMMAND);

	return (cmd & PCIM_CMD_PORTEN);
}