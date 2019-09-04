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
typedef  int /*<<< orphan*/  uint32_t ;
struct pci_devinst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_get_cfgdata16 (struct pci_devinst*,int) ; 
 int /*<<< orphan*/  pci_get_cfgdata32 (struct pci_devinst*,int) ; 
 int /*<<< orphan*/  pci_get_cfgdata8 (struct pci_devinst*,int) ; 

__attribute__((used)) static __inline uint32_t
CFGREAD(struct pci_devinst *pi, int coff, int bytes)
{

	if (bytes == 1)
		return (pci_get_cfgdata8(pi, coff));
	else if (bytes == 2)
		return (pci_get_cfgdata16(pi, coff));
	else
		return (pci_get_cfgdata32(pi, coff));
}