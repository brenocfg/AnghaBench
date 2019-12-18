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

/* Variables and functions */
 scalar_t__ MCFG_OFFSET ; 
 int /*<<< orphan*/  acpitbl_checksum (void*,int) ; 
 int /*<<< orphan*/  acpitbl_write64 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpitbl_write8 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 int /*<<< orphan*/  pci_ecfg_base () ; 
 scalar_t__ tb ; 

__attribute__((used)) static void
acpitbl_build_mcfg(void) {
	void *mcfg;
	/*
	 * [000h 0000  4]                    Signature : "MCFG"
	 * [004h 0004  4]                 Table Length : 0000003C
	 * [008h 0008  1]                     Revision : 01
	 * [009h 0009  1]                     Checksum : 00
	 * [00Ah 0010  6]                       Oem ID : "BHYVE "
	 * [010h 0016  8]                 Oem Table ID : "BVMCFG  "
	 * [018h 0024  4]                 Oem Revision : 00000001
	 * [01Ch 0028  4]              Asl Compiler ID : "INTL"
	 * [020h 0032  4]        Asl Compiler Revision : 20140828
	 * [024h 0036  8]                     Reserved : 0000000000000000
	 * [02Ch 0044  8]                 Base Address : 0000000000000000
	 * [034h 0052  2]         Segment Group Number : 0000
	 * [036h 0054  1]             Start Bus Number : 00
	 * [037h 0055  1]               End Bus Number : FF
	 * [038h 0056  4]                     Reserved : 00000000
	 */
	static const uint8_t mcfg_tmpl[60] = {
		0x4D, 0x43, 0x46, 0x47, 0x3C, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x42, 0x48, 0x59, 0x56, 0x45, 0x20,
		0x42, 0x56, 0x4D, 0x43, 0x46, 0x47, 0x20, 0x20,
		0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,
		0x28, 0x08, 0x14, 0x20, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x00, 0x00
	};

	mcfg = (void *) (((uintptr_t) tb) + MCFG_OFFSET);
	/* copy MCFG template to guest memory */
	memcpy(mcfg, mcfg_tmpl, 60);
	/* fixup table */
	acpitbl_write64(mcfg, 0x2c, pci_ecfg_base());
	/* write checksum */
	acpitbl_write8(mcfg, 0x9, acpitbl_checksum(mcfg, 60));
}