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
 scalar_t__ FACS_OFFSET ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 scalar_t__ tb ; 

__attribute__((used)) static void
acpitbl_build_facs(void) {
	void *facs;
	/*
	 * [000h 0000  4]                    Signature : "FACS"
	 * [004h 0004  4]                       Length : 00000040
	 * [008h 0008  4]           Hardware Signature : 00000000
	 * [00Ch 0012  4]    32 Firmware Waking Vector : 00000000
	 * [010h 0016  4]                  Global Lock : 00000000
	 * [014h 0020  4]        Flags (decoded below) : 00000000
	 *                      S4BIOS Support Present : 0
	 *                  64-bit Wake Supported (V2) : 0
	 * [018h 0024  8]    64 Firmware Waking Vector : 0000000000000000
	 * [020h 0032  1]                      Version : 02
	 * [021h 0033  3]                     Reserved : 000000
	 * [024h 0036  4]    OspmFlags (decoded below) : 00000000
	 *               64-bit Wake Env Required (V2) : 0
	 */
	static const uint8_t facs_tmpl[64] = {
		0x46, 0x41, 0x43, 0x53, 0x40, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	facs = (void *) (((uintptr_t) tb) + FACS_OFFSET);
	/* copy MCFG template to guest memory */
	memcpy(facs, facs_tmpl, 64);
}