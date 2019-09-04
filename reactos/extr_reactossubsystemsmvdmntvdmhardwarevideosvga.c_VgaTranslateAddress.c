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
typedef  int DWORD ;

/* Variables and functions */
 int LOWORD (int) ; 
 int SVGA_GC_EXT_MODE_GRAN ; 
 size_t SVGA_GC_EXT_MODE_REG ; 
 int SVGA_GC_EXT_MODE_WND_B ; 
 size_t SVGA_GC_OFFSET_0_REG ; 
 size_t SVGA_GC_OFFSET_1_REG ; 
 int VGA_GC_MODE_OE ; 
 size_t VGA_GC_MODE_REG ; 
 int VGA_SEQ_MEM_C4 ; 
 size_t VGA_SEQ_MEM_REG ; 
 int* VgaGcRegisters ; 
 int VgaGetVideoBaseAddress () ; 
 int* VgaSeqRegisters ; 

__attribute__((used)) static inline DWORD VgaTranslateAddress(DWORD Address)
{
    DWORD Offset = LOWORD(Address - VgaGetVideoBaseAddress());
    DWORD ExtOffset = ((VgaGcRegisters[SVGA_GC_EXT_MODE_REG] & SVGA_GC_EXT_MODE_WND_B) && (Offset & (1 << 15)))
                      ? VgaGcRegisters[SVGA_GC_OFFSET_1_REG]
                      : VgaGcRegisters[SVGA_GC_OFFSET_0_REG];

    /* Check for chain-4 and odd-even mode */
    if (VgaSeqRegisters[VGA_SEQ_MEM_REG] & VGA_SEQ_MEM_C4)
    {
        /* Clear the lowest two bits since they're used to select the bank */
        Offset &= ~3;
    }
    else if (VgaGcRegisters[VGA_GC_MODE_REG] & VGA_GC_MODE_OE)
    {
        /* Clear the lowest bit since it's used to select odd/even */
        Offset &= ~1;
    }

    if (ExtOffset)
    {
        /* Add the extended offset */
        Offset += ExtOffset << ((VgaGcRegisters[SVGA_GC_EXT_MODE_REG] & SVGA_GC_EXT_MODE_GRAN) ? 14 : 12);
    }

    /* Return the offset on plane 0 */
    return Offset;
}