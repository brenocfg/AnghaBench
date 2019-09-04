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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dac_palette_rgb; } ;
struct TYPE_3__ {size_t atc_color_plane_enb; int atc_mode; int* atc_palette; size_t atc_color_select_45; size_t atc_color_select_67; } ;
struct vga_softc {int gc_width; int* vga_ram; TYPE_2__ vga_dac; TYPE_1__ vga_atc; } ;

/* Variables and functions */
 int ATC_MC_IPS ; 
 int KB ; 

__attribute__((used)) static uint32_t
vga_get_pixel(struct vga_softc *sc, uint16_t x, uint16_t y)
{
	unsigned int offset;
	int bit;
	uint8_t data;
	uint8_t idx;

	offset = (y * sc->gc_width / 8) + (x / 8);
	bit = 7 - (x % 8);

	data = (uint8_t)(((sc->vga_ram[offset + 0 * 64*KB] >> bit) & 0x1) << 0) |
		(uint8_t)(((sc->vga_ram[offset + 1 * 64*KB] >> bit) & 0x1) << 1) |
		(uint8_t)(((sc->vga_ram[offset + 2 * 64*KB] >> bit) & 0x1) << 2) |
		(uint8_t)(((sc->vga_ram[offset + 3 * 64*KB] >> bit) & 0x1) << 3);

	data &= sc->vga_atc.atc_color_plane_enb;

	if (sc->vga_atc.atc_mode & ATC_MC_IPS) {
		idx = sc->vga_atc.atc_palette[data] & 0x0f;
		idx |= sc->vga_atc.atc_color_select_45;
	} else {
		idx = sc->vga_atc.atc_palette[data];
	}
	idx |= sc->vga_atc.atc_color_select_67;

	return (sc->vga_dac.dac_palette_rgb[idx]);
}