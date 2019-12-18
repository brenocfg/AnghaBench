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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ FADT_OFFSET ; 
 scalar_t__ HPET_OFFSET ; 
 scalar_t__ MADT_OFFSET ; 
 scalar_t__ MCFG_OFFSET ; 
 scalar_t__ XHYVE_ACPI_BASE ; 
 scalar_t__ XSDT_OFFSET ; 
 int /*<<< orphan*/  acpitbl_checksum (void*,int) ; 
 int /*<<< orphan*/  acpitbl_write64 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpitbl_write8 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 scalar_t__ tb ; 

__attribute__((used)) static void
acpitbl_build_xsdt(void) {
	void *xsdt;
	/*
	 * [000h 0000  4]                    Signature : "XSDT"
	 * [004h 0004  4]                 Table Length : 00000044
	 * [008h 0008  1]                     Revision : 01
	 * [009h 0009  1]                     Checksum : 00
	 * [00Ah 0010  6]                       Oem ID : "BHYVE "
	 * [010h 0016  8]                 Oem Table ID : "BVXSDT  "
	 * [018h 0024  4]                 Oem Revision : 00000001
	 * [01Ch 0028  4]              Asl Compiler ID : "INTL"
	 * [020h 0032  4]        Asl Compiler Revision : 20140828
	 * [024h 0036  8]       ACPI Table Address   0 : 0000000000000000
	 * [02Ch 0044  8]       ACPI Table Address   1 : 0000000000000000
	 * [034h 0052  8]       ACPI Table Address   2 : 0000000000000000
	 * [03Ch 0060  8]       ACPI Table Address   3 : 0000000000000000
	 */
	static const uint8_t xsdt_tmpl[68] = {
  		0x58, 0x53, 0x44, 0x54, 0x44, 0x00, 0x00, 0x00,
  		0x01, 0x00, 0x42, 0x48, 0x59, 0x56, 0x45, 0x20,
  		0x42, 0x56, 0x58, 0x53, 0x44, 0x54, 0x20, 0x20,
  		0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,
  		0x28, 0x08, 0x14, 0x20, 0x00, 0x00, 0x00, 0x00,
  		0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x00, 0x00,
  		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  		0x00, 0x00, 0x00, 0x00
	};

	xsdt = (void *) (((uintptr_t) tb) + XSDT_OFFSET);
	/* copy XSDT template to guest memory */
	memcpy(xsdt, xsdt_tmpl, 68);
	/* fixup table */
	acpitbl_write64(xsdt, 0x24, ((uint64_t) (XHYVE_ACPI_BASE + MADT_OFFSET)));
	acpitbl_write64(xsdt, 0x2c, ((uint64_t) (XHYVE_ACPI_BASE + FADT_OFFSET)));
	acpitbl_write64(xsdt, 0x34, ((uint64_t) (XHYVE_ACPI_BASE + HPET_OFFSET)));
	acpitbl_write64(xsdt, 0x3c, ((uint64_t) (XHYVE_ACPI_BASE + MCFG_OFFSET)));
	/* write checksum */
	acpitbl_write8(xsdt, 0x9, acpitbl_checksum(xsdt, 68));
}