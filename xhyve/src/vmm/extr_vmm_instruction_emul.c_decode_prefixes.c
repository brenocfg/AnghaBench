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
struct vie {int opsize_override; int addrsize_override; int repz_present; int repnz_present; int segment_override; int rex_present; int rex_w; int rex_r; int rex_x; int rex_b; int addrsize; int opsize; int /*<<< orphan*/  segment_register; } ;
typedef  enum vm_cpu_mode { ____Placeholder_vm_cpu_mode } vm_cpu_mode ;

/* Variables and functions */
 int CPU_MODE_64BIT ; 
 scalar_t__ segment_override (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vie_advance (struct vie*) ; 
 scalar_t__ vie_peek (struct vie*,int*) ; 

__attribute__((used)) static int
decode_prefixes(struct vie *vie, enum vm_cpu_mode cpu_mode, int cs_d)
{
	uint8_t x;

	while (1) {
		if (vie_peek(vie, &x))
			return (-1);

		if (x == 0x66)
			vie->opsize_override = 1;
		else if (x == 0x67)
			vie->addrsize_override = 1;
		else if (x == 0xF3)
			vie->repz_present = 1;
		else if (x == 0xF2)
			vie->repnz_present = 1;
		else if (segment_override(x, &vie->segment_register))
			vie->segment_override = 1;
		else
			break;

		vie_advance(vie);
	}

	/*
	 * From section 2.2.1, "REX Prefixes", Intel SDM Vol 2:
	 * - Only one REX prefix is allowed per instruction.
	 * - The REX prefix must immediately precede the opcode byte or the
	 *   escape opcode byte.
	 * - If an instruction has a mandatory prefix (0x66, 0xF2 or 0xF3)
	 *   the mandatory prefix must come before the REX prefix.
	 */
	if (cpu_mode == CPU_MODE_64BIT && x >= 0x40 && x <= 0x4F) {
		vie->rex_present = 1;
		vie->rex_w = x & 0x8 ? 1 : 0;
		vie->rex_r = x & 0x4 ? 1 : 0;
		vie->rex_x = x & 0x2 ? 1 : 0;
		vie->rex_b = x & 0x1 ? 1 : 0;
		vie_advance(vie);
	}

	/*
	 * Section "Operand-Size And Address-Size Attributes", Intel SDM, Vol 1
	 */
	if (cpu_mode == CPU_MODE_64BIT) {
		/*
		 * Default address size is 64-bits and default operand size
		 * is 32-bits.
		 */
		vie->addrsize = vie->addrsize_override ? 4 : 8;
		if (vie->rex_w)
			vie->opsize = 8;
		else if (vie->opsize_override)
			vie->opsize = 2;
		else
			vie->opsize = 4;
	} else if (cs_d) {
		/* Default address and operand sizes are 32-bits */
		vie->addrsize = vie->addrsize_override ? 2 : 4;
		vie->opsize = vie->opsize_override ? 2 : 4;
	} else {
		/* Default address and operand sizes are 16-bits */
		vie->addrsize = vie->addrsize_override ? 4 : 2;
		vie->opsize = vie->opsize_override ? 4 : 2;
	}
	return (0);
}