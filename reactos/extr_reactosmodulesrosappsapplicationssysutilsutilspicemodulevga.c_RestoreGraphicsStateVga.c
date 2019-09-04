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
 int /*<<< orphan*/  cGraphTable2 ; 
 int inb_p (int) ; 
 int /*<<< orphan*/  load_font (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 int /*<<< orphan*/  pScreenBufferHardwareVga ; 
 int /*<<< orphan*/  pScreenBufferSaveVga ; 
 int /*<<< orphan*/  pScreenBufferTempVga ; 
 int /*<<< orphan*/  pScreenBufferVga ; 
 int /*<<< orphan*/  pice_restore_current_registers () ; 

void RestoreGraphicsStateVga(void)
{
	UCHAR data;

	// unprotect crtc regs 0-7
	outb_p(0x11,0x3d4);
	data = inb_p(0x3d5);
	outb_p(data & 0x7F,0x3d5);

	// restore original regs
	pice_restore_current_registers();

	// load a font
	load_font(cGraphTable2,0);

    pScreenBufferVga = pScreenBufferSaveVga;
    // copy screen to the console
    PICE_memcpy(pScreenBufferVga,pScreenBufferHardwareVga,SCREEN_BUFFER_SIZE);
    // copy the temp area to the screen
    PICE_memcpy(pScreenBufferHardwareVga,pScreenBufferTempVga,SCREEN_BUFFER_SIZE);
}