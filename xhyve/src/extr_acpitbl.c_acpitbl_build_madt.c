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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ MADT_OFFSET ; 
 int SCI_INT ; 
 int acpi_ncpu ; 
 int acpitbl_checksum (void*,size_t) ; 
 int /*<<< orphan*/  acpitbl_write32 (void*,int,int) ; 
 int /*<<< orphan*/  acpitbl_write8 (void*,int,int) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 scalar_t__ tb ; 

__attribute__((used)) static void
acpitbl_build_madt(void) {
	void *madt_head, *madt_apic, *madt_tail;
	int i;
	/*
	 * [000h 0000  4]                    Signature : "APIC"
	 * [004h 0004  4]                 Table Length : 00000000
	 * [008h 0008  1]                     Revision : 01
	 * [009h 0009  1]                     Checksum : 4E
	 * [00Ah 0010  6]                       Oem ID : "BHYVE "
	 * [010h 0016  8]                 Oem Table ID : "BVMADT  "
	 * [018h 0024  4]                 Oem Revision : 00000001
	 * [01Ch 0028  4]              Asl Compiler ID : "INTL"
	 * [020h 0032  4]        Asl Compiler Revision : 20140828
	 * [024h 0036  4]           Local Apic Address : FEE00000
	 * [028h 0040  4]        Flags (decoded below) : 00000001
     *                         PC-AT Compatibility : 1
	 */
	static const uint8_t madt_head_tmpl[44] = {
		0x41, 0x50, 0x49, 0x43, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x42, 0x48, 0x59, 0x56, 0x45, 0x20,
		0x42, 0x56, 0x4D, 0x41, 0x44, 0x54, 0x20, 0x20,
		0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,
		0x28, 0x08, 0x14, 0x20, 0x00, 0x00, 0xE0, 0xFE,
		0x01, 0x00, 0x00, 0x00,
	};
	/*
	 * [+000h +0000  1]              Subtable Type : 00 <Processor Local APIC>
	 * [+001h +0001  1]                     Length : 08
	 * [+002h +0002  1]               Processor ID : 00
	 * [+003h +0003  1]              Local Apic ID : 00
	 * [+004h +0004  4]      Flags (decoded below) : 00000001
	 *                           Processor Enabled : 1
	 */
	static const uint8_t madt_apic_tmpl[8] = {
		0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	};
	/*
	 * [+000h +0000  1]              Subtable Type : 01 <I/O APIC>
	 * [+001h +0001  1]                     Length : 0C
	 * [+002h +0002  1]                I/O Apic ID : 00
	 * [+003h +0003  1]                   Reserved : 00
	 * [+004h +0004  4]                    Address : FEC00000
	 * [+008h +0008  4]                  Interrupt : 00000000
	 * [+00Ch +0012  1]              Subtable Type : 02 <IRQ Source Override>
	 * [+00Dh +0013  1]                     Length : 0A
	 * [+00Eh +0014  1]                        Bus : 00
	 * [+00Fh +0015  1]                     Source : 00
	 * [+010h +0016  4]                  Interrupt : 00000002
	 * [+014h +0020  2]      Flags (decoded below) : 0005
	 *                                  Polarity : 1
	 *                              Trigger Mode : 1
	 * [+016h +0022  1]              Subtable Type : 02 <IRQ Source Override>
	 * [+017h +0023  1]                     Length : 0A
	 * [+018h +0024  1]                        Bus : 00
	 * [+019h +0025  1]                     Source : 00
	 * [+01Ah +0026  4]                  Interrupt : 00000000
	 * [+01Eh +0030  2]      Flags (decoded below) : 000F
	 *                                  Polarity : 3
	 *                              Trigger Mode : 3
	 * [+020h +0032  1]              Subtable Type : 04 <Local APIC NMI>
	 * [+021h +0033  1]                     Length : 06
	 * [+022h +0034  1]               Processor ID : FF
	 * [+023h +0035  2]      Flags (decoded below) : 0005
	 *                                  Polarity : 1
	 *                              Trigger Mode : 1
	 * [+025h +0037  1]       Interrupt Input LINT : 01
	 */
	static const uint8_t madt_tail_tmpl[38] = {
		0x01, 0x0C, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFE,
		0x00, 0x00, 0x00, 0x00, 0x02, 0x0A, 0x00, 0x00,
		0x02, 0x00, 0x00, 0x00, 0x05, 0x00, 0x02, 0x0A,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00,
		0x04, 0x06, 0xFF, 0x05, 0x00, 0x01
	};

	madt_head = (void *) (((uintptr_t) tb) + MADT_OFFSET);
	/* copy MADT head template to guest memory */
	memcpy(madt_head, madt_head_tmpl, 44);

	for (i = 0; i < acpi_ncpu; i++) {
		madt_apic = (void *) (((uintptr_t) tb)
			+ ((size_t) ((MADT_OFFSET + 44) + (8 * i))));
		/* copy MADT APIC template to guest memory */
		memcpy(madt_apic, madt_apic_tmpl, 8);
		/* fixup table */
		acpitbl_write8(madt_apic, 0x2, ((uint8_t) i));
		acpitbl_write8(madt_apic, 0x3, ((uint8_t) i));
	}

	madt_tail = (void *) (((uintptr_t) tb)
		+ ((size_t) ((MADT_OFFSET + 44) + (8 * acpi_ncpu))));
	/* copy MADT tail template to guest memory */
	memcpy(madt_tail, madt_tail_tmpl, 38);
	/* fixup table */
	acpitbl_write8(madt_tail, 0x2, 0);
	acpitbl_write8(madt_tail, 0x19, SCI_INT);
	acpitbl_write32(madt_tail, 0x1a, SCI_INT);
	/* write checksum */
	acpitbl_write32(madt_head, 0x4, ((uint32_t) (44 + (8 * acpi_ncpu) + 38)));
	acpitbl_write8(madt_head, 0x9,
		acpitbl_checksum(madt_head, ((size_t) (44 + (8 * acpi_ncpu) + 38))));
}