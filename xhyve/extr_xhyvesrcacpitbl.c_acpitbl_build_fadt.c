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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHYVE_ACPI_DISABLE ; 
 int /*<<< orphan*/  BHYVE_ACPI_ENABLE ; 
 scalar_t__ DSDT_OFFSET ; 
 scalar_t__ FACS_OFFSET ; 
 scalar_t__ FADT_OFFSET ; 
 scalar_t__ IO_PMTMR ; 
 scalar_t__ PM1A_CNT_ADDR ; 
 scalar_t__ PM1A_EVT_ADDR ; 
 int /*<<< orphan*/  SCI_INT ; 
 scalar_t__ SMI_CMD ; 
 scalar_t__ XHYVE_ACPI_BASE ; 
 int /*<<< orphan*/  acpitbl_checksum (void*,int) ; 
 int /*<<< orphan*/  acpitbl_write16 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpitbl_write32 (void*,int,scalar_t__) ; 
 int /*<<< orphan*/  acpitbl_write64 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpitbl_write8 (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 scalar_t__ tb ; 

__attribute__((used)) static void
acpitbl_build_fadt(void) {
	void *fadt;
	/*
	 * [000h 0000  4]                    Signature : "FACP"
	 * [004h 0004  4]                 Table Length : 0000010C
	 * [008h 0008  1]                     Revision : 05
	 * [009h 0009  1]                     Checksum : 00
	 * [00Ah 0010  6]                       Oem ID : "BHYVE "
	 * [010h 0016  8]                 Oem Table ID : "BVFACP  "
	 * [018h 0024  4]                 Oem Revision : 00000001
	 * [01Ch 0028  4]              Asl Compiler ID : "INTL"
	 * [020h 0032  4]        Asl Compiler Revision : 20140828
	 * [024h 0036  4]                 FACS Address : 00000000
	 * [028h 0040  4]                 DSDT Address : 00000000
	 * [02Ch 0044  1]                        Model : 01
	 * [02Dh 0045  1]                   PM Profile : 00 (Unspecified)
	 * [02Eh 0046  2]                SCI Interrupt : 0000
	 * [030h 0048  4]             SMI Command Port : 00000000
	 * [034h 0052  1]            ACPI Enable Value : 00
	 * [035h 0053  1]           ACPI Disable Value : 00
	 * [036h 0054  1]               S4BIOS Command : 00
	 * [037h 0055  1]              P-State Control : 00
	 * [038h 0056  4]     PM1A Event Block Address : 00000000
	 * [03Ch 0060  4]     PM1B Event Block Address : 00000000
	 * [040h 0064  4]   PM1A Control Block Address : 00000000
	 * [044h 0068  4]   PM1B Control Block Address : 00000000
	 * [048h 0072  4]    PM2 Control Block Address : 00000000
	 * [04Ch 0076  4]       PM Timer Block Address : 00000000
	 * [050h 0080  4]           GPE0 Block Address : 00000000
	 * [054h 0084  4]           GPE1 Block Address : 00000000
	 * [058h 0088  1]       PM1 Event Block Length : 04
	 * [059h 0089  1]     PM1 Control Block Length : 02
	 * [05Ah 0090  1]     PM2 Control Block Length : 00
	 * [05Bh 0091  1]        PM Timer Block Length : 04
	 * [05Ch 0092  1]            GPE0 Block Length : 00
	 * [05Dh 0093  1]            GPE1 Block Length : 00
	 * [05Eh 0094  1]             GPE1 Base Offset : 00
	 * [05Fh 0095  1]                 _CST Support : 00
	 * [060h 0096  2]                   C2 Latency : 0000
	 * [062h 0098  2]                   C3 Latency : 0000
	 * [064h 0100  2]               CPU Cache Size : 0000
	 * [066h 0102  2]           Cache Flush Stride : 0000
	 * [068h 0104  1]            Duty Cycle Offset : 00
	 * [069h 0105  1]             Duty Cycle Width : 00
	 * [06Ah 0106  1]          RTC Day Alarm Index : 00
	 * [06Bh 0107  1]        RTC Month Alarm Index : 00
	 * [06Ch 0108  1]            RTC Century Index : 32
	 * [06Dh 0109  2]   Boot Flags (decoded below) : 0014
	 *               Legacy Devices Supported (V2) : 0
	 *            8042 Present on ports 60/64 (V2) : 0
	 *                        VGA Not Present (V4) : 1
	 *                      MSI Not Supported (V4) : 0
	 *                PCIe ASPM Not Supported (V4) : 1
	 * [06Fh 0111  1]                     Reserved : 00
	 * [070h 0112  4]        Flags (decoded below) : 00081525
	 *      WBINVD instruction is operational (V1) : 1
	 *              WBINVD flushes all caches (V1) : 0
	 *                    All CPUs support C1 (V1) : 1
	 *                  C2 works on MP system (V1) : 0
	 *            Control Method Power Button (V1) : 0
	 *            Control Method Sleep Button (V1) : 1
	 *        RTC wake not in fixed reg space (V1) : 0
	 *            RTC can wake system from S4 (V1) : 0
	 *                        32-bit PM Timer (V1) : 1
	 *                      Docking Supported (V1) : 0
	 *               Reset Register Supported (V2) : 1
	 *                            Sealed Case (V3) : 0
	 *                    Headless - No Video (V3) : 1
	 *        Use native instr after SLP_TYPx (V3) : 0
	 *              PCIEXP_WAK Bits Supported (V4) : 0
	 *                     Use Platform Timer (V4) : 0
	 *               RTC_STS valid on S4 wake (V4) : 0
	 *                Remote Power-on capable (V4) : 0
	 *                 Use APIC Cluster Model (V4) : 0
	 *     Use APIC Physical Destination Mode (V4) : 1
	 * [074h 0116 12]               Reset Register : <Generic Address Structure>
	 * [074h 0116  1]                     Space ID : 01 (SystemIO)
	 * [075h 0117  1]                    Bit Width : 08
	 * [076h 0118  1]                   Bit Offset : 00
	 * [077h 0119  1]                 Access Width : 01
	 * [078h 0120  8]                      Address : 0000000000000CF9
	 * [080h 0128  1]         Value to cause reset : 06
	 * [081h 0129  3]                     Reserved : 000001
	 * [084h 0132  8]                 FACS Address : 0000000000000000
	 * [08Ch 0140  8]                 DSDT Address : 0000000000000000
	 * [094h 0148 12]             PM1A Event Block : <Generic Address Structure>
	 * [094h 0148  1]                     Space ID : 01 (SystemIO)
	 * [095h 0149  1]                    Bit Width : 20
	 * [096h 0150  1]                   Bit Offset : 00
	 * [097h 0151  1]                 Access Width : 02
	 * [098h 0152  8]                      Address : 0000000000000000
	 * [0A0h 0160 12]             PM1B Event Block : <Generic Address Structure>
	 * [0A0h 0160  1]                     Space ID : 01 (SystemIO)
	 * [0A1h 0161  1]                    Bit Width : 00
	 * [0A2h 0162  1]                   Bit Offset : 00
	 * [0A3h 0163  1]                 Access Width : 00
	 * [0A4h 0164  8]                      Address : 0000000000000000
	 * [0ACh 0172 12]           PM1A Control Block : <Generic Address Structure>
	 * [0ACh 0172  1]                     Space ID : 01 (SystemIO)
	 * [0ADh 0173  1]                    Bit Width : 10
	 * [0AEh 0174  1]                   Bit Offset : 00
	 * [0AFh 0175  1]                 Access Width : 02
	 * [0B0h 0176  8]                      Address : 0000000000000000
	 * [0B8h 0184 12]           PM1B Control Block : <Generic Address Structure>
	 * [0B8h 0184  1]                     Space ID : 01 (SystemIO)
	 * [0B9h 0185  1]                    Bit Width : 00
	 * [0BAh 0186  1]                   Bit Offset : 00
	 * [0BBh 0187  1]                 Access Width : 00
	 * [0BCh 0188  8]                      Address : 0000000000000000
	 * [0C4h 0196 12]            PM2 Control Block : <Generic Address Structure>
	 * [0C4h 0196  1]                     Space ID : 01 (SystemIO)
	 * [0C5h 0197  1]                    Bit Width : 08
	 * [0C6h 0198  1]                   Bit Offset : 00
	 * [0C7h 0199  1]                 Access Width : 00
	 * [0C8h 0200  8]                      Address : 0000000000000000
	 * [0D0h 0208 12]               PM Timer Block : <Generic Address Structure>
	 * [0D0h 0208  1]                     Space ID : 01 (SystemIO)
	 * [0D1h 0209  1]                    Bit Width : 20
	 * [0D2h 0210  1]                   Bit Offset : 00
	 * [0D3h 0211  1]                 Access Width : 03
	 * [0D4h 0212  8]                      Address : 0000000000000000
	 * [0DCh 0220 12]                   GPE0 Block : <Generic Address Structure>
	 * [0DCh 0220  1]                     Space ID : 01 (SystemIO)
	 * [0DDh 0221  1]                    Bit Width : 00
	 * [0DEh 0222  1]                   Bit Offset : 00
	 * [0DFh 0223  1]                 Access Width : 01
	 * [0E0h 0224  8]                      Address : 0000000000000000
	 * [0E8h 0232 12]                   GPE1 Block : <Generic Address Structure>
	 * [0E8h 0232  1]                     Space ID : 01 (SystemIO)
	 * [0E9h 0233  1]                    Bit Width : 00
	 * [0EAh 0234  1]                   Bit Offset : 00
	 * [0EBh 0235  1]                 Access Width : 00
	 * [0ECh 0236  8]                      Address : 0000000000000000
	 * [0F4h 0244 12]       Sleep Control Register : <Generic Address Structure>
	 * [0F4h 0244  1]                     Space ID : 01 (SystemIO)
	 * [0F5h 0245  1]                    Bit Width : 08
	 * [0F6h 0246  1]                   Bit Offset : 00
	 * [0F7h 0247  1]                 Access Width : 01
	 * [0F8h 0248  8]                      Address : 0000000000000000
	 * [100h 0256 12]        Sleep Status Register : <Generic Address Structure>
	 * [100h 0256 01]                     Space ID : 01 (SystemIO)
	 * [101h 0257 01]                    Bit Width : 08
	 * [102h 0258 01]                   Bit Offset : 00
	 * [103h 0259 01]                 Access Width : 01
	 * [104h 0260 08]                      Address : 0000000000000000
	 */
	static const uint8_t fadt_tmpl[268] = {
		0x46, 0x41, 0x43, 0x50, 0x0C, 0x01, 0x00, 0x00,
		0x05, 0x00, 0x42, 0x48, 0x59, 0x56, 0x45, 0x20,
		0x42, 0x56, 0x46, 0x41, 0x43, 0x50, 0x20, 0x20,
		0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,
		0x28, 0x08, 0x14, 0x20, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x04, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x32, 0x14, 0x00, 0x00,
		0x25, 0x15, 0x08, 0x00, 0x01, 0x08, 0x00, 0x01,
		0xF9, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x06, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x20, 0x00, 0x02,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x02,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x20, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x00, 0x01,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	};

	fadt = (void *) (((uintptr_t) tb) + FADT_OFFSET);
	/* copy FADT template to guest memory */
	memcpy(fadt, fadt_tmpl, 268);
	/* fixup table */
	acpitbl_write32(fadt, 0x24, ((uint32_t) (XHYVE_ACPI_BASE + FACS_OFFSET)));
	acpitbl_write32(fadt, 0x28, ((uint32_t) (XHYVE_ACPI_BASE + DSDT_OFFSET)));
	acpitbl_write16(fadt, 0x2e, SCI_INT);
	acpitbl_write32(fadt, 0x30, SMI_CMD);
	acpitbl_write8(fadt, 0x34, BHYVE_ACPI_ENABLE);
	acpitbl_write8(fadt, 0x35, BHYVE_ACPI_DISABLE);
	acpitbl_write32(fadt, 0x38, PM1A_EVT_ADDR);
	acpitbl_write32(fadt, 0x40, PM1A_CNT_ADDR);
	acpitbl_write32(fadt, 0x4c, IO_PMTMR);
	acpitbl_write64(fadt, 0x84, ((uint64_t) (XHYVE_ACPI_BASE + FACS_OFFSET)));
	acpitbl_write64(fadt, 0x8c, ((uint64_t) (XHYVE_ACPI_BASE + DSDT_OFFSET)));
	acpitbl_write64(fadt, 0x98, ((uint64_t) PM1A_EVT_ADDR));
	acpitbl_write64(fadt, 0xb0, ((uint64_t) PM1A_CNT_ADDR));
	acpitbl_write64(fadt, 0xd4, ((uint64_t) IO_PMTMR));
	/* write checksum */
	acpitbl_write8(fadt, 0x9, acpitbl_checksum(fadt, 268));
}