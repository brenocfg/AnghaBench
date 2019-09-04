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

/* Variables and functions */
 int /*<<< orphan*/  GRAPHICS ; 
 int /*<<< orphan*/  GRREGENABLESETRESET ; 
 int /*<<< orphan*/  GRREGMISC ; 
 int /*<<< orphan*/  GRREGREADMAPSEL ; 
 int /*<<< orphan*/  GRREGWRMODE ; 
 int /*<<< orphan*/  SEQUENCER ; 
 int /*<<< orphan*/  SQREGMAPMASK ; 
 int /*<<< orphan*/  SQREGMEMORY ; 
 void* oldgraphicsmisc ; 
 void* oldgraphicsmode ; 
 void* oldgraphicsreadmapsel ; 
 void* oldgraphicssetresetenable ; 
 void* oldsqregmapmask ; 
 void* oldsqregmemory ; 
 void* read_vga_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_vga_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void map_font_memory(void)
{
	oldgraphicssetresetenable = read_vga_reg(GRAPHICS, GRREGENABLESETRESET);
	oldgraphicsmode = read_vga_reg(GRAPHICS, GRREGWRMODE);
	oldgraphicsmisc = read_vga_reg(GRAPHICS, GRREGMISC);
	oldgraphicsreadmapsel = read_vga_reg(GRAPHICS, GRREGREADMAPSEL);
	oldsqregmapmask = read_vga_reg(SEQUENCER, SQREGMAPMASK);
	oldsqregmemory = read_vga_reg(SEQUENCER, SQREGMEMORY);


	/* Make sure set/reset enable is off */
	write_vga_reg(GRAPHICS,GRREGENABLESETRESET,0);
	/* Select read plane 2 */
	write_vga_reg(GRAPHICS,GRREGREADMAPSEL,0x02);
	/* Make sure write and read mode = 0 */
	write_vga_reg(GRAPHICS,GRREGWRMODE,0x00);
	/* Set mapping to 64K at a000:0 & turn off odd/even at the graphics reg */
	write_vga_reg(GRAPHICS,GRREGMISC, 0x04);
	/* Set sequencer plane to 2 */
	write_vga_reg(SEQUENCER,SQREGMAPMASK, 0x04);
	/* Turn off odd/even at the sequencer */
	write_vga_reg(SEQUENCER,SQREGMEMORY, 0x07);
}