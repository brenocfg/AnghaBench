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

/* Variables and functions */
 int /*<<< orphan*/ * lpc_bridge ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pirq_read (int) ; 

void
lpc_pirq_routed(void)
{
	int pin;

	if (lpc_bridge == NULL)
		return;

 	for (pin = 0; pin < 4; pin++)
		pci_set_cfgdata8(lpc_bridge, 0x60 + pin, pirq_read(pin + 1));
	for (pin = 0; pin < 4; pin++)
		pci_set_cfgdata8(lpc_bridge, 0x68 + pin, pirq_read(pin + 5));
}