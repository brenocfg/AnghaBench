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
struct vie {int mod; scalar_t__ rm; int ss; int index; int base; int rex_x; int rex_b; int disp_bytes; int base_register; int index_register; int scale; } ;

/* Variables and functions */
 int VIE_MOD_DIRECT ; 
 int VIE_MOD_INDIRECT ; 
#define  VIE_MOD_INDIRECT_DISP32 129 
#define  VIE_MOD_INDIRECT_DISP8 128 
 scalar_t__ VIE_RM_SIB ; 
 int VM_REG_LAST ; 
 scalar_t__* gpr_map ; 
 int /*<<< orphan*/  vie_advance (struct vie*) ; 
 scalar_t__ vie_peek (struct vie*,int*) ; 

__attribute__((used)) static int
decode_sib(struct vie *vie)
{
	uint8_t x;

	/* Proceed only if SIB byte is present */
	if (vie->mod == VIE_MOD_DIRECT || vie->rm != VIE_RM_SIB)
		return (0);

	if (vie_peek(vie, &x))
		return (-1);

	/* De-construct the SIB byte */
	vie->ss = (x >> 6) & 0x3;
	vie->index = (x >> 3) & 0x7;
	vie->base = (x >> 0) & 0x7;

	/* Apply the REX prefix modifiers */
	vie->index |= vie->rex_x << 3;
	vie->base |= vie->rex_b << 3;

	switch (vie->mod) {
	case VIE_MOD_INDIRECT_DISP8:
		vie->disp_bytes = 1;
		break;
	case VIE_MOD_INDIRECT_DISP32:
		vie->disp_bytes = 4;
		break;
	}

	if (vie->mod == VIE_MOD_INDIRECT &&
	    (vie->base == 5 || vie->base == 13)) {
		/*
		 * Special case when base register is unused if mod = 0
		 * and base = %rbp or %r13.
		 *
		 * Documented in:
		 * Table 2-3: 32-bit Addressing Forms with the SIB Byte
		 * Table 2-5: Special Cases of REX Encodings
		 */
		vie->disp_bytes = 4;
	} else {
		vie->base_register = (int) gpr_map[vie->base];
	}

	/*
	 * All encodings of 'index' are valid except for %rsp (4).
	 *
	 * Documented in:
	 * Table 2-3: 32-bit Addressing Forms with the SIB Byte
	 * Table 2-5: Special Cases of REX Encodings
	 */
	if (vie->index != 4)
		vie->index_register = (int) gpr_map[vie->index];

	/* 'scale' makes sense only in the context of an index register */
	if (vie->index_register < VM_REG_LAST)
		vie->scale = (uint8_t) (1 << vie->ss);

	vie_advance(vie);

	return (0);
}