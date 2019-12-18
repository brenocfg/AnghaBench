#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  TYPE_1__* int_entry_ptr ;
struct TYPE_5__ {int src_bus_id; int src_bus_irq; int int_flags; void* int_type; void* dst_apic_int; void* dst_apic_id; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int INTENTRY_FLAGS_POLARITY_ACTIVELO ; 
 int INTENTRY_FLAGS_TRIGGER_LEVEL ; 
 void* INTENTRY_TYPE_EXTINT ; 
 void* INTENTRY_TYPE_INT ; 
 int /*<<< orphan*/  MPCT_ENTRY_INT ; 
 int PCI_BUSMAX ; 
#define  SCI_INT 128 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_generate_pci_int ; 
 int /*<<< orphan*/  pci_walk_lintr (int,int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static void
mpt_build_ioint_entries(int_entry_ptr mpie, int id)
{
	int pin, bus;

	/*
	 * The following config is taken from kernel mptable.c
	 * mptable_parse_default_config_ints(...), for now 
	 * just use the default config, tweek later if needed.
	 */

	/* First, generate the first 16 pins. */
	for (pin = 0; pin < 16; pin++) {
		memset(mpie, 0, sizeof(*mpie));
		mpie->type = MPCT_ENTRY_INT;
		mpie->src_bus_id = 1;
		mpie->dst_apic_id = (uint8_t) id;

		/*
		 * All default configs route IRQs from bus 0 to the first 16
		 * pins of the first I/O APIC with an APIC ID of 2.
		 */
		mpie->dst_apic_int = (uint8_t) pin;
		switch (pin) {
		case 0:
			/* Pin 0 is an ExtINT pin. */
			mpie->int_type = INTENTRY_TYPE_EXTINT;
			break;
		case 2:
			/* IRQ 0 is routed to pin 2. */
			mpie->int_type = INTENTRY_TYPE_INT;
			mpie->src_bus_irq = 0;
			break;
		case SCI_INT:
			/* ACPI SCI is level triggered and active-lo. */
			mpie->int_flags = INTENTRY_FLAGS_POLARITY_ACTIVELO |
			    INTENTRY_FLAGS_TRIGGER_LEVEL;
			mpie->int_type = INTENTRY_TYPE_INT;
			mpie->src_bus_irq = SCI_INT;
			break;
		default:
			/* All other pins are identity mapped. */
			mpie->int_type = INTENTRY_TYPE_INT;
			mpie->src_bus_irq = (uint8_t) pin;
			break;
		}
		mpie++;
	}

	/* Next, generate entries for any PCI INTx interrupts. */
	for (bus = 0; bus <= PCI_BUSMAX; bus++)
		pci_walk_lintr(bus, mpt_generate_pci_int, &mpie); 
}