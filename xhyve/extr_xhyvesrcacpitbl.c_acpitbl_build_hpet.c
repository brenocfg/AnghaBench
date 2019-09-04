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
 scalar_t__ HPET_OFFSET ; 
 int /*<<< orphan*/  acpitbl_checksum (void*,int) ; 
 int /*<<< orphan*/  acpitbl_write32 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpitbl_write8 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_capabilities ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 scalar_t__ tb ; 

__attribute__((used)) static void
acpitbl_build_hpet(void) {
	void *hpet;
	/*
	 * [000h 0000  4]                    Signature : "HPET"
	 * [004h 0004  4]                 Table Length : 00000038
	 * [008h 0008  1]                     Revision : 01
	 * [009h 0009  1]                     Checksum : 00
	 * [00Ah 0010  6]                       Oem ID : "BHYVE "
	 * [010h 0016  8]                 Oem Table ID : "BVHPET  "
	 * [018h 0024  4]                 Oem Revision : 00000001
	 * [01Ch 0028  4]              Asl Compiler ID : "INTL"
	 * [020h 0032  4]        Asl Compiler Revision : 20140828
	 * [024h 0036  4]            Hardware Block ID : 00000000
	 * [028h 0040 12]         Timer Block Register : <Generic Address Structure>
	 * [028h 0040  1]                     Space ID : 00 (SystemMemory)
	 * [029h 0041  1]                    Bit Width : 00
	 * [02Ah 0042  1]                   Bit Offset : 00
	 * [02Bh 0043  1]                 Access Width : 00
	 * [02Ch 0044  8]                      Address : 00000000FED00000
	 * [034h 0052  1]              Sequence Number : 00
	 * [035h 0053  2]          Minimum Clock Ticks : 0000
	 * [037h 0055  1]        Flags (decoded below) : 01
	 *                             4K Page Protect : 1
	 *                            64K Page Protect : 0
	 */
	static const uint8_t hpet_tmpl[56] = {
		0x48, 0x50, 0x45, 0x54, 0x38, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x42, 0x48, 0x59, 0x56, 0x45, 0x20,
		0x42, 0x56, 0x48, 0x50, 0x45, 0x54, 0x20, 0x20,
		0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,
		0x28, 0x08, 0x14, 0x20, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0xFE,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	};

	hpet = (void *) (((uintptr_t) tb) + HPET_OFFSET);
	/* copy HPET template to guest memory */
	memcpy(hpet, hpet_tmpl, 56);
	/* fixup table */
	acpitbl_write32(hpet, 0x24, hpet_capabilities);
	/* write checksum */
	acpitbl_write8(hpet, 0x9, acpitbl_checksum(hpet, 56));
}