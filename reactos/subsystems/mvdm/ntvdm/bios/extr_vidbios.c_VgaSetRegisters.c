#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {int VGAOptions; int CrtModeControl; int /*<<< orphan*/  CrtBasePort; } ;
struct TYPE_4__ {int Misc; int* Attribute; int* Sequencer; int* CRT; int* Graphics; } ;
typedef  TYPE_1__* PVGA_REGISTERS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_3__* Bda ; 
 int /*<<< orphan*/  FALSE ; 
 int IOReadB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOWriteB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int VGA_AC_CONTROL_BLINK ; 
 size_t VGA_AC_CONTROL_REG ; 
 int /*<<< orphan*/  VGA_AC_INDEX ; 
 size_t VGA_AC_MAX_REG ; 
 int /*<<< orphan*/  VGA_CRTC_DATA ; 
 size_t VGA_CRTC_END_HORZ_BLANKING_REG ; 
 size_t VGA_CRTC_END_VERT_RETRACE_REG ; 
 int /*<<< orphan*/  VGA_CRTC_INDEX ; 
 int /*<<< orphan*/  VGA_CRTC_INDEX_COLOR ; 
 int /*<<< orphan*/  VGA_CRTC_INDEX_MONO ; 
 size_t VGA_CRTC_MAX_REG ; 
 int /*<<< orphan*/  VGA_DAC_MASK ; 
 int /*<<< orphan*/  VGA_GC_DATA ; 
 int /*<<< orphan*/  VGA_GC_INDEX ; 
 size_t VGA_GC_MAX_REG ; 
 int /*<<< orphan*/  VGA_INSTAT1_READ ; 
 int /*<<< orphan*/  VGA_MISC_WRITE ; 
 int VGA_SEQ_CLOCK_REG ; 
 int VGA_SEQ_CLOCK_SD ; 
 int /*<<< orphan*/  VGA_SEQ_DATA ; 
 int /*<<< orphan*/  VGA_SEQ_INDEX ; 
 size_t VGA_SEQ_MAX_REG ; 
 int VGA_SEQ_RESET_AR ; 
 int VGA_SEQ_RESET_REG ; 
 int VGA_SEQ_RESET_SR ; 
 int /*<<< orphan*/  VgaSetSinglePaletteRegister (size_t,int) ; 
 int /*<<< orphan*/  setIF (int) ; 

__attribute__((used)) static BOOLEAN VgaSetRegisters(PVGA_REGISTERS Registers)
{
    UINT i;

    if (Registers == NULL) return FALSE;

    /* Disable interrupts */
    setIF(0);

    /*
     * Set the CRT base address according to the selected mode,
     * monochrome or color. The following macros:
     * VGA_INSTAT1_READ, VGA_CRTC_INDEX and VGA_CRTC_DATA are then
     * used to access the correct VGA I/O ports.
     */
    Bda->CrtBasePort = (Registers->Misc & 0x01) ? VGA_CRTC_INDEX_COLOR
                                                : VGA_CRTC_INDEX_MONO;
    /* Bit 1 indicates whether display is color (0) or monochrome (1) */
    Bda->VGAOptions     = (Bda->VGAOptions     & 0xFD) | (!(Registers->Misc & 0x01) << 1);
    Bda->CrtModeControl = (Bda->CrtModeControl & 0xFB) | (!(Registers->Misc & 0x01) << 1);

    /* Update blink bit in BDA */
    if (Registers->Attribute[VGA_AC_CONTROL_REG] & VGA_AC_CONTROL_BLINK)
        Bda->CrtModeControl |= (1 << 5);
    else
        Bda->CrtModeControl &= ~(1 << 5);

    /* Turn the video off */
    IOWriteB(VGA_SEQ_INDEX, VGA_SEQ_CLOCK_REG);
    IOWriteB(VGA_SEQ_DATA , IOReadB(VGA_SEQ_DATA) | VGA_SEQ_CLOCK_SD);

    /* Write the misc register */
    IOWriteB(VGA_MISC_WRITE, Registers->Misc);

    /* Synchronous reset on */
    IOWriteB(VGA_SEQ_INDEX, VGA_SEQ_RESET_REG);
    IOWriteB(VGA_SEQ_DATA , VGA_SEQ_RESET_AR );

    /* Write the sequencer registers */
    for (i = 1; i < VGA_SEQ_MAX_REG; i++)
    {
        IOWriteB(VGA_SEQ_INDEX, i);
        IOWriteB(VGA_SEQ_DATA , Registers->Sequencer[i]);
    }

    /* Synchronous reset off */
    IOWriteB(VGA_SEQ_INDEX, VGA_SEQ_RESET_REG);
    IOWriteB(VGA_SEQ_DATA , VGA_SEQ_RESET_SR | VGA_SEQ_RESET_AR);

    /* Unlock CRTC registers 0-7 */
    IOWriteB(VGA_CRTC_INDEX, VGA_CRTC_END_HORZ_BLANKING_REG);
    IOWriteB(VGA_CRTC_DATA , IOReadB(VGA_CRTC_DATA) | 0x80);
    IOWriteB(VGA_CRTC_INDEX, VGA_CRTC_END_VERT_RETRACE_REG);
    IOWriteB(VGA_CRTC_DATA , IOReadB(VGA_CRTC_DATA) & ~0x80);
    // Make sure they remain unlocked
    Registers->CRT[VGA_CRTC_END_HORZ_BLANKING_REG] |= 0x80;
    Registers->CRT[VGA_CRTC_END_VERT_RETRACE_REG] &= ~0x80;

    /* Write the CRTC registers */
    for (i = 0; i < VGA_CRTC_MAX_REG; i++)
    {
        IOWriteB(VGA_CRTC_INDEX, i);
        IOWriteB(VGA_CRTC_DATA , Registers->CRT[i]);
    }

    /* Write the GC registers */
    for (i = 0; i < VGA_GC_MAX_REG; i++)
    {
        IOWriteB(VGA_GC_INDEX, i);
        IOWriteB(VGA_GC_DATA , Registers->Graphics[i]);
    }

    /* Write the AC registers */
    for (i = 0; i < VGA_AC_MAX_REG; i++)
    {
        VgaSetSinglePaletteRegister(i, Registers->Attribute[i]);
    }

    /* Set the PEL mask */
    IOWriteB(VGA_DAC_MASK, 0xFF);

    /* Enable screen and disable palette access */
    IOReadB(VGA_INSTAT1_READ); // Put the AC register into index state
    IOWriteB(VGA_AC_INDEX, 0x20);

    /* Turn the video on */
    IOWriteB(VGA_SEQ_INDEX, VGA_SEQ_CLOCK_REG);
    IOWriteB(VGA_SEQ_DATA , IOReadB(VGA_SEQ_DATA) & ~VGA_SEQ_CLOCK_SD);

    /* Enable interrupts */
    setIF(1);

    return TRUE;
}