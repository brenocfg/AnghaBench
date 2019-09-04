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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int GetBValue (int /*<<< orphan*/  const) ; 
 int GetGValue (int /*<<< orphan*/  const) ; 
 int GetRValue (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  IOWriteB (int /*<<< orphan*/ ,size_t) ; 
 size_t VGA_COLOR_TO_DAC (int) ; 
 int /*<<< orphan*/  VGA_DAC_DATA ; 
 int /*<<< orphan*/  VGA_DAC_WRITE_INDEX ; 
 size_t VGA_MAX_COLORS ; 

__attribute__((used)) static VOID VgaSetPalette(const COLORREF* Palette, ULONG Size)
{
    ULONG i;

    // /* Disable screen and enable palette access */
    // IOReadB(VGA_INSTAT1_READ); // Put the AC register into index state
    // IOWriteB(VGA_AC_INDEX, 0x00);

    for (i = 0; i < Size; i++)
    {
        IOWriteB(VGA_DAC_WRITE_INDEX, i);
        IOWriteB(VGA_DAC_DATA, VGA_COLOR_TO_DAC(GetRValue(Palette[i])));
        IOWriteB(VGA_DAC_DATA, VGA_COLOR_TO_DAC(GetGValue(Palette[i])));
        IOWriteB(VGA_DAC_DATA, VGA_COLOR_TO_DAC(GetBValue(Palette[i])));
    }

    /* The following step might be optional */
    for (i = Size; i < VGA_MAX_COLORS; i++)
    {
        IOWriteB(VGA_DAC_WRITE_INDEX, i);
        IOWriteB(VGA_DAC_DATA, VGA_COLOR_TO_DAC(0x00));
        IOWriteB(VGA_DAC_DATA, VGA_COLOR_TO_DAC(0x00));
        IOWriteB(VGA_DAC_DATA, VGA_COLOR_TO_DAC(0x00));
    }

    /* Enable screen and disable palette access */
    // IOReadB(VGA_INSTAT1_READ); // Put the AC register into index state
    // IOWriteB(VGA_AC_INDEX, 0x20);
}