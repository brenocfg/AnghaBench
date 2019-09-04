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
 int /*<<< orphan*/  oldgraphicsmisc ; 
 int /*<<< orphan*/  oldgraphicsmode ; 
 int /*<<< orphan*/  oldgraphicsreadmapsel ; 
 int /*<<< orphan*/  oldgraphicssetresetenable ; 
 int /*<<< orphan*/  oldsqregmapmask ; 
 int /*<<< orphan*/  oldsqregmemory ; 
 int /*<<< orphan*/  write_vga_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void unmap_font_memory(void)
{
	write_vga_reg(GRAPHICS,GRREGENABLESETRESET,oldgraphicssetresetenable);
	write_vga_reg(GRAPHICS,GRREGWRMODE,oldgraphicsmode);
	write_vga_reg(GRAPHICS,GRREGREADMAPSEL,oldgraphicsreadmapsel);
	write_vga_reg(GRAPHICS,GRREGMISC, oldgraphicsmisc);
	write_vga_reg(SEQUENCER,SQREGMAPMASK, oldsqregmapmask);
	write_vga_reg(SEQUENCER,SQREGMEMORY, oldsqregmemory);
}