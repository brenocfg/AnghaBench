#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_4__ {int seq_map_mask; } ;
struct TYPE_3__ {int gc_misc_mm; int gc_set_reset; int gc_enb_set_reset; int gc_latch0; int gc_latch1; int gc_latch2; int gc_latch3; int gc_mode_wm; int gc_bit_mask; int gc_rotate; scalar_t__ gc_mode_oe; int /*<<< orphan*/  gc_op; } ;
struct vga_softc {int* vga_ram; TYPE_2__ vga_seq; TYPE_1__ vga_gc; } ;

/* Variables and functions */
 int KB ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vga_mem_wr_handler(uint64_t addr, uint8_t val, void *arg1)
{
	struct vga_softc *sc = arg1;
	uint8_t c0, c1, c2, c3;
	uint8_t m0, m1, m2, m3;
	uint8_t set_reset;
	uint8_t enb_set_reset;
	uint8_t	mask;
	uint64_t offset;

	offset = addr;
	switch (sc->vga_gc.gc_misc_mm) {
	case 0x0:
		/*
		 * extended mode: base 0xa0000 size 128kb
		 */
		offset -=0xa0000;
		offset &= (128 * KB - 1);
		break;
	case 0x1:
		/*
		 * EGA/VGA mode: base 0xa0000 size 64kb
		 */
		offset -=0xa0000;
		offset &= (64 * KB - 1);
		break;
	case 0x2:
		/*
		 * monochrome text mode: base 0xb0000 size 32kb
		 */
		assert(0);
	case 0x3:
		/*
		 * color text mode and CGA: base 0xb8000 size 32kb
		 */
		offset -=0xb8000;
		offset &= (32 * KB - 1);
		break;
	}

	set_reset = sc->vga_gc.gc_set_reset;
	enb_set_reset = sc->vga_gc.gc_enb_set_reset;

	c0 = sc->vga_gc.gc_latch0;
	c1 = sc->vga_gc.gc_latch1;
	c2 = sc->vga_gc.gc_latch2;
	c3 = sc->vga_gc.gc_latch3;

	switch (sc->vga_gc.gc_mode_wm) {
	case 0:
		/* write mode 0 */
		mask = sc->vga_gc.gc_bit_mask;

		val = (uint8_t)(val >> sc->vga_gc.gc_rotate) |
		    (uint8_t)(val << (8 - sc->vga_gc.gc_rotate));

		switch (sc->vga_gc.gc_op) {
		case 0x00:		/* replace */
			m0 = (set_reset & 1) ? mask : 0x00;
			m1 = (set_reset & 2) ? mask : 0x00;
			m2 = (set_reset & 4) ? mask : 0x00;
			m3 = (set_reset & 8) ? mask : 0x00;

			c0 = (enb_set_reset & 1) ? (c0 & ~mask) : (val & mask);
			c1 = (enb_set_reset & 2) ? (c1 & ~mask) : (val & mask);
			c2 = (enb_set_reset & 4) ? (c2 & ~mask) : (val & mask);
			c3 = (enb_set_reset & 8) ? (c3 & ~mask) : (val & mask);

			c0 |= m0;
			c1 |= m1;
			c2 |= m2;
			c3 |= m3;
			break;
		case 0x08:		/* AND */
			m0 = set_reset & 1 ? 0xff : ~mask;
			m1 = set_reset & 2 ? 0xff : ~mask;
			m2 = set_reset & 4 ? 0xff : ~mask;
			m3 = set_reset & 8 ? 0xff : ~mask;

			c0 = enb_set_reset & 1 ? c0 & m0 : val & m0;
			c1 = enb_set_reset & 2 ? c1 & m1 : val & m1;
			c2 = enb_set_reset & 4 ? c2 & m2 : val & m2;
			c3 = enb_set_reset & 8 ? c3 & m3 : val & m3;
			break;
		case 0x10:		/* OR */
			m0 = set_reset & 1 ? mask : 0x00;
			m1 = set_reset & 2 ? mask : 0x00;
			m2 = set_reset & 4 ? mask : 0x00;
			m3 = set_reset & 8 ? mask : 0x00;

			c0 = enb_set_reset & 1 ? c0 | m0 : val | m0;
			c1 = enb_set_reset & 2 ? c1 | m1 : val | m1;
			c2 = enb_set_reset & 4 ? c2 | m2 : val | m2;
			c3 = enb_set_reset & 8 ? c3 | m3 : val | m3;
			break;
		case 0x18:		/* XOR */
			m0 = set_reset & 1 ? mask : 0x00;
			m1 = set_reset & 2 ? mask : 0x00;
			m2 = set_reset & 4 ? mask : 0x00;
			m3 = set_reset & 8 ? mask : 0x00;

			c0 = enb_set_reset & 1 ? c0 ^ m0 : val ^ m0;
			c1 = enb_set_reset & 2 ? c1 ^ m1 : val ^ m1;
			c2 = enb_set_reset & 4 ? c2 ^ m2 : val ^ m2;
			c3 = enb_set_reset & 8 ? c3 ^ m3 : val ^ m3;
			break;
		}
		break;
	case 1:
		/* write mode 1 */
		break;
	case 2:
		/* write mode 2 */
		mask = sc->vga_gc.gc_bit_mask;

		switch (sc->vga_gc.gc_op) {
		case 0x00:		/* replace */
			m0 = (val & 1 ? 0xff : 0x00) & mask;
			m1 = (val & 2 ? 0xff : 0x00) & mask;
			m2 = (val & 4 ? 0xff : 0x00) & mask;
			m3 = (val & 8 ? 0xff : 0x00) & mask;

			c0 &= ~mask;
			c1 &= ~mask;
			c2 &= ~mask;
			c3 &= ~mask;

			c0 |= m0;
			c1 |= m1;
			c2 |= m2;
			c3 |= m3;
			break;
		case 0x08:		/* AND */
			m0 = (val & 1 ? 0xff : 0x00) | ~mask;
			m1 = (val & 2 ? 0xff : 0x00) | ~mask;
			m2 = (val & 4 ? 0xff : 0x00) | ~mask;
			m3 = (val & 8 ? 0xff : 0x00) | ~mask;

			c0 &= m0;
			c1 &= m1;
			c2 &= m2;
			c3 &= m3;
			break;
		case 0x10:		/* OR */
			m0 = (val & 1 ? 0xff : 0x00) & mask;
			m1 = (val & 2 ? 0xff : 0x00) & mask;
			m2 = (val & 4 ? 0xff : 0x00) & mask;
			m3 = (val & 8 ? 0xff : 0x00) & mask;

			c0 |= m0;
			c1 |= m1;
			c2 |= m2;
			c3 |= m3;
			break;
		case 0x18:		/* XOR */
			m0 = (val & 1 ? 0xff : 0x00) & mask;
			m1 = (val & 2 ? 0xff : 0x00) & mask;
			m2 = (val & 4 ? 0xff : 0x00) & mask;
			m3 = (val & 8 ? 0xff : 0x00) & mask;

			c0 ^= m0;
			c1 ^= m1;
			c2 ^= m2;
			c3 ^= m3;
			break;
		}
		break;
	case 3:
		/* write mode 3 */
		mask = sc->vga_gc.gc_bit_mask & val;

		val = (uint8_t)(val >> sc->vga_gc.gc_rotate) |
		    (uint8_t)(val << (8 - sc->vga_gc.gc_rotate));

		switch (sc->vga_gc.gc_op) {
		case 0x00:		/* replace */
			m0 = (set_reset & 1 ? 0xff : 0x00) & mask;
			m1 = (set_reset & 2 ? 0xff : 0x00) & mask;
			m2 = (set_reset & 4 ? 0xff : 0x00) & mask;
			m3 = (set_reset & 8 ? 0xff : 0x00) & mask;

			c0 &= ~mask;
			c1 &= ~mask;
			c2 &= ~mask;
			c3 &= ~mask;

			c0 |= m0;
			c1 |= m1;
			c2 |= m2;
			c3 |= m3;
			break;
		case 0x08:		/* AND */
			m0 = (set_reset & 1 ? 0xff : 0x00) | ~mask;
			m1 = (set_reset & 2 ? 0xff : 0x00) | ~mask;
			m2 = (set_reset & 4 ? 0xff : 0x00) | ~mask;
			m3 = (set_reset & 8 ? 0xff : 0x00) | ~mask;

			c0 &= m0;
			c1 &= m1;
			c2 &= m2;
			c3 &= m3;
			break;
		case 0x10:		/* OR */
			m0 = (set_reset & 1 ? 0xff : 0x00) & mask;
			m1 = (set_reset & 2 ? 0xff : 0x00) & mask;
			m2 = (set_reset & 4 ? 0xff : 0x00) & mask;
			m3 = (set_reset & 8 ? 0xff : 0x00) & mask;

			c0 |= m0;
			c1 |= m1;
			c2 |= m2;
			c3 |= m3;
			break;
		case 0x18:		/* XOR */
			m0 = (set_reset & 1 ? 0xff : 0x00) & mask;
			m1 = (set_reset & 2 ? 0xff : 0x00) & mask;
			m2 = (set_reset & 4 ? 0xff : 0x00) & mask;
			m3 = (set_reset & 8 ? 0xff : 0x00) & mask;

			c0 ^= m0;
			c1 ^= m1;
			c2 ^= m2;
			c3 ^= m3;
			break;
		}
		break;
	}

	if (sc->vga_gc.gc_mode_oe) {
		if (offset & 1) {
			offset &= (uint64_t)~1;
			if (sc->vga_seq.seq_map_mask & 2)
				sc->vga_ram[offset + 1*64*KB] = c1;
			if (sc->vga_seq.seq_map_mask & 8)
				sc->vga_ram[offset + 3*64*KB] = c3;
		} else {
			if (sc->vga_seq.seq_map_mask & 1)
				sc->vga_ram[offset + 0*64*KB] = c0;
			if (sc->vga_seq.seq_map_mask & 4)
				sc->vga_ram[offset + 2*64*KB] = c2;
		}
	} else {
		if (sc->vga_seq.seq_map_mask & 1)
			sc->vga_ram[offset + 0*64*KB] = c0;
		if (sc->vga_seq.seq_map_mask & 2)
			sc->vga_ram[offset + 1*64*KB] = c1;
		if (sc->vga_seq.seq_map_mask & 4)
			sc->vga_ram[offset + 2*64*KB] = c2;
		if (sc->vga_seq.seq_map_mask & 8)
			sc->vga_ram[offset + 3*64*KB] = c3;
	}
}