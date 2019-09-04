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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EFFLUSH (int /*<<< orphan*/ *) ; 
 scalar_t__ dsdt_error ; 
 int /*<<< orphan*/  dsdt_fixed_mem32 (int,int) ; 
 int /*<<< orphan*/ * dsdt_fp ; 
 int /*<<< orphan*/  dsdt_indent (int) ; 
 scalar_t__ dsdt_indent_level ; 
 int /*<<< orphan*/  dsdt_line (char*) ; 
 int /*<<< orphan*/  dsdt_unindent (int) ; 
 int errno ; 
 int /*<<< orphan*/  pci_write_dsdt () ; 

__attribute__((used)) static int
basl_fwrite_dsdt(FILE *fp)
{
	int err;

	err = 0;
	dsdt_fp = fp;
	dsdt_error = 0;
	dsdt_indent_level = 0;

	dsdt_line("/*");
	dsdt_line(" * bhyve DSDT template");
	dsdt_line(" */");
	dsdt_line("DefinitionBlock (\"bhyve_dsdt.aml\", \"DSDT\", 2,"
		 "\"BHYVE \", \"BVDSDT  \", 0x00000001)");
	dsdt_line("{");
	dsdt_line("  Name (_S5, Package ()");
	dsdt_line("  {");
	dsdt_line("      0x05,");
	dsdt_line("      Zero,");
	dsdt_line("  })");

	pci_write_dsdt();

	dsdt_line("");
	dsdt_line("  Scope (_SB.PC00)");
	dsdt_line("  {");
	dsdt_line("    Device (HPET)");
	dsdt_line("    {");
	dsdt_line("      Name (_HID, EISAID(\"PNP0103\"))");
	dsdt_line("      Name (_UID, 0)");
	dsdt_line("      Name (_CRS, ResourceTemplate ()");
	dsdt_line("      {");
	dsdt_indent(4);
	dsdt_fixed_mem32(0xFED00000, 0x400);
	dsdt_unindent(4);
	dsdt_line("      })");
	dsdt_line("    }");
	dsdt_line("  }");
	dsdt_line("}");

	if (dsdt_error != 0)
		return (dsdt_error);

	EFFLUSH(fp);

	return (0);

err_exit:
	return (errno);
}