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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ RSDT_OFFSET ; 
 scalar_t__ XHYVE_ACPI_BASE ; 
 scalar_t__ XSDT_OFFSET ; 
 int /*<<< orphan*/  acpitbl_checksum (void*,int) ; 
 int /*<<< orphan*/  acpitbl_write32 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpitbl_write64 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpitbl_write8 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 scalar_t__ tb ; 

__attribute__((used)) static void
acpitbl_build_rdsp(void) {
	void *rdsp;
	/*
	 * [000h 0000  8]                    Signature : "RSD PTR "
	 * [008h 0008  1]                     Checksum : 00
	 * [009h 0009  6]                       Oem ID : "BHYVE "
	 * [00Fh 0015  1]                     Revision : 02
	 * [010h 0016  4]                 RSDT Address : 00000000
	 * [014h 0020  4]                       Length : 00000024
	 * [018h 0024  8]                 XSDT Address : 0000000000000000
	 * [020h 0032  1]            Extended Checksum : 00
	 * [021h 0033  3]                     Reserved : 000000
	 */
	static const uint8_t rdsp_tmpl[36] = {
		0x52, 0x53, 0x44, 0x20, 0x50, 0x54, 0x52, 0x20,
		0x00, 0x42, 0x48, 0x59, 0x56, 0x45, 0x20, 0x02,
		0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	};

	rdsp = (void *) (((uintptr_t) tb) + 0);
	/* copy RDSP template to guest memory */
	memcpy(rdsp, rdsp_tmpl, 36);
	/* fixup table */
	acpitbl_write32(rdsp, 0x10, ((uint32_t) (XHYVE_ACPI_BASE + RSDT_OFFSET)));
	acpitbl_write64(rdsp, 0x18, ((uint64_t) (XHYVE_ACPI_BASE + XSDT_OFFSET)));
	/* write checksum */
	acpitbl_write8(rdsp, 0x8, acpitbl_checksum(rdsp, 20));
	/* write extended checksum */
	acpitbl_write8(rdsp, 0x20, acpitbl_checksum(rdsp, 36));
}