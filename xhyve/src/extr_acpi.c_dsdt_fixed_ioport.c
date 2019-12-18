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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsdt_line (char*,...) ; 

void
dsdt_fixed_ioport(uint16_t iobase, uint16_t length)
{

	dsdt_line("IO (Decode16,");
	dsdt_line("  0x%04X,             // Range Minimum", iobase);
	dsdt_line("  0x%04X,             // Range Maximum", iobase);
	dsdt_line("  0x01,               // Alignment");
	dsdt_line("  0x%02X,               // Length", length);
	dsdt_line("  )");
}