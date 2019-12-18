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
 int MAXBUSES ; 
 int /*<<< orphan*/  dsdt_indent (int) ; 
 int /*<<< orphan*/  dsdt_line (char*) ; 
 int /*<<< orphan*/  dsdt_unindent (int) ; 
 int /*<<< orphan*/  pci_bus_write_dsdt (int) ; 

void
pci_write_dsdt(void)
{
	int bus;

	dsdt_indent(1);
	dsdt_line("Name (PICM, 0x00)");
	dsdt_line("Method (_PIC, 1, NotSerialized)");
	dsdt_line("{");
	dsdt_line("  Store (Arg0, PICM)");
	dsdt_line("}");
	dsdt_line("");
	dsdt_line("Scope (_SB)");
	dsdt_line("{");
	for (bus = 0; bus < MAXBUSES; bus++)
		pci_bus_write_dsdt(bus);
	dsdt_line("}");
	dsdt_unindent(1);
}