#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int op_flags; } ;
struct vie {int mod; int rm; int reg; int rex_b; int rex_r; int base_register; int disp_bytes; TYPE_1__ op; } ;
typedef  enum vm_cpu_mode { ____Placeholder_vm_cpu_mode } vm_cpu_mode ;

/* Variables and functions */
 int CPU_MODE_64BIT ; 
 int CPU_MODE_REAL ; 
 int VIE_MOD_DIRECT ; 
#define  VIE_MOD_INDIRECT 130 
#define  VIE_MOD_INDIRECT_DISP32 129 
#define  VIE_MOD_INDIRECT_DISP8 128 
 int VIE_OP_F_NO_MODRM ; 
 int VIE_RM_DISP32 ; 
 int VIE_RM_SIB ; 
 int VM_REG_GUEST_RIP ; 
 int VM_REG_LAST ; 
 scalar_t__* gpr_map ; 
 int /*<<< orphan*/  vie_advance (struct vie*) ; 
 scalar_t__ vie_peek (struct vie*,int*) ; 

__attribute__((used)) static int
decode_modrm(struct vie *vie, enum vm_cpu_mode cpu_mode)
{
	uint8_t x;

	if (vie->op.op_flags & VIE_OP_F_NO_MODRM)
		return (0);

	if (cpu_mode == CPU_MODE_REAL)
		return (-1);

	if (vie_peek(vie, &x))
		return (-1);

	vie->mod = (x >> 6) & 0x3;
	vie->rm =  (x >> 0) & 0x7;
	vie->reg = (x >> 3) & 0x7;

	/*
	 * A direct addressing mode makes no sense in the context of an EPT
	 * fault. There has to be a memory access involved to cause the
	 * EPT fault.
	 */
	if (vie->mod == VIE_MOD_DIRECT)
		return (-1);

	if ((vie->mod == VIE_MOD_INDIRECT && vie->rm == VIE_RM_DISP32) ||
	    (vie->mod != VIE_MOD_DIRECT && vie->rm == VIE_RM_SIB)) {
		/*
		 * Table 2-5: Special Cases of REX Encodings
		 *
		 * mod=0, r/m=5 is used in the compatibility mode to
		 * indicate a disp32 without a base register.
		 *
		 * mod!=3, r/m=4 is used in the compatibility mode to
		 * indicate that the SIB byte is present.
		 *
		 * The 'b' bit in the REX prefix is don't care in
		 * this case.
		 */
	} else {
		vie->rm |= (vie->rex_b << 3);
	}

	vie->reg |= (vie->rex_r << 3);

	/* SIB */
	if (vie->mod != VIE_MOD_DIRECT && vie->rm == VIE_RM_SIB)
		goto done;

	vie->base_register = (int) gpr_map[vie->rm];

	switch (vie->mod) {
	case VIE_MOD_INDIRECT_DISP8:
		vie->disp_bytes = 1;
		break;
	case VIE_MOD_INDIRECT_DISP32:
		vie->disp_bytes = 4;
		break;
	case VIE_MOD_INDIRECT:
		if (vie->rm == VIE_RM_DISP32) {
			vie->disp_bytes = 4;
			/*
			 * Table 2-7. RIP-Relative Addressing
			 *
			 * In 64-bit mode mod=00 r/m=101 implies [rip] + disp32
			 * whereas in compatibility mode it just implies disp32.
			 */

			if (cpu_mode == CPU_MODE_64BIT)
				vie->base_register = VM_REG_GUEST_RIP;
			else
				vie->base_register = VM_REG_LAST;
		}
		break;
	}

done:
	vie_advance(vie);

	return (0);
}