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
 int /*<<< orphan*/  IO_RTC ; 
 int /*<<< orphan*/  dsdt_fixed_ioport (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsdt_fixed_irq (int) ; 
 int /*<<< orphan*/  dsdt_indent (int) ; 
 int /*<<< orphan*/  dsdt_line (char*) ; 
 int /*<<< orphan*/  dsdt_unindent (int) ; 

__attribute__((used)) static void
rtc_dsdt(void)
{
	dsdt_line("");
	dsdt_line("Device (RTC)");
	dsdt_line("{");
	dsdt_line("  Name (_HID, EisaId (\"PNP0B00\"))");
	dsdt_line("  Name (_CRS, ResourceTemplate ()");
	dsdt_line("  {");
	dsdt_indent(2);
	dsdt_fixed_ioport(IO_RTC, 2);
	dsdt_fixed_irq(8);
	dsdt_unindent(2);
	dsdt_line("  })");
	dsdt_line("}");
}