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
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  PICE_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCREEN_BUFFER_SIZE ; 
 int /*<<< orphan*/  cGraphTable ; 
 int /*<<< orphan*/  cGraphTable2 ; 
 int inb_p (int) ; 
 int /*<<< orphan*/  load_font (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 int /*<<< orphan*/  pScreenBufferHardwareVga ; 
 int /*<<< orphan*/  pScreenBufferSaveVga ; 
 int /*<<< orphan*/  pScreenBufferTempVga ; 
 int /*<<< orphan*/  pScreenBufferVga ; 
 int /*<<< orphan*/  pice_save_current_registers () ; 
 int /*<<< orphan*/  pice_set_mode_3_80x25 () ; 
 int /*<<< orphan*/  pice_set_mode_3_80x50 () ; 
 int /*<<< orphan*/  save_font (int /*<<< orphan*/ ) ; 

void SaveGraphicsStateVga(void)
{
	UCHAR data;

	// save current regs
	pice_save_current_registers();

	// unprotect crtc regs 0-7
	outb_p(0x11,0x3d4);
	data = inb_p(0x3d5);
	outb_p(data & 0x7F,0x3d5);

	// save current font
	save_font(cGraphTable2);

	// restore original regs
#ifdef VGA_EXTENDED
	pice_set_mode_3_80x50();
#else
	pice_set_mode_3_80x25();
#endif

	// load a font
	load_font(cGraphTable,1);

	// copy the screen content to temp area
    PICE_memcpy(pScreenBufferTempVga,pScreenBufferHardwareVga,SCREEN_BUFFER_SIZE);
    // copy the console to the screen
    PICE_memcpy(pScreenBufferHardwareVga,pScreenBufferVga,SCREEN_BUFFER_SIZE);
    // save original pointer
    pScreenBufferSaveVga = pScreenBufferVga;
    // pScreenBufferVga now points to screen
    pScreenBufferVga = pScreenBufferHardwareVga;
}