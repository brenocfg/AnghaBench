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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pci_devinst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata32 (struct pci_devinst*,int,scalar_t__) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
CFGWRITE(struct pci_devinst *pi, int coff, uint32_t val, int bytes)
{

	if (bytes == 1)
		pci_set_cfgdata8(pi, coff, ((uint8_t) val));
	else if (bytes == 2)
		pci_set_cfgdata16(pi, coff, ((uint16_t) val));
	else
		pci_set_cfgdata32(pi, coff, val);
}