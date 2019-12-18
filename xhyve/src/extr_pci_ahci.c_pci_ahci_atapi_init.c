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
struct pci_devinst {int dummy; } ;

/* Variables and functions */
 int pci_ahci_init (struct pci_devinst*,char*,int) ; 

__attribute__((used)) static int
pci_ahci_atapi_init(struct pci_devinst *pi, char *opts)
{
	return (pci_ahci_init(pi, opts, 1));
}