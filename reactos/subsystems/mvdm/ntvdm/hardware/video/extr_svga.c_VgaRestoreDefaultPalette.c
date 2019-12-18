#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t USHORT ;
struct TYPE_3__ {scalar_t__ peFlags; void* peBlue; void* peGreen; void* peRed; } ;
typedef  TYPE_1__* PPALETTEENTRY ;

/* Variables and functions */
 void* GetBValue (int /*<<< orphan*/ ) ; 
 void* GetGValue (int /*<<< orphan*/ ) ; 
 void* GetRValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGA_COLOR_TO_DAC (void*) ; 
 int /*<<< orphan*/ * VgaDacRegisters ; 
 int /*<<< orphan*/ * VgaDefaultPalette ; 

__attribute__((used)) static VOID VgaRestoreDefaultPalette(PPALETTEENTRY Entries, USHORT NumOfEntries)
{
    USHORT i;

    /* Copy the colors of the default palette to the DAC and console palette */
    for (i = 0; i < NumOfEntries; i++)
    {
        /* Set the palette entries */
        Entries[i].peRed   = GetRValue(VgaDefaultPalette[i]);
        Entries[i].peGreen = GetGValue(VgaDefaultPalette[i]);
        Entries[i].peBlue  = GetBValue(VgaDefaultPalette[i]);
        Entries[i].peFlags = 0;

        /* Set the DAC registers */
        VgaDacRegisters[i * 3]     = VGA_COLOR_TO_DAC(GetRValue(VgaDefaultPalette[i]));
        VgaDacRegisters[i * 3 + 1] = VGA_COLOR_TO_DAC(GetGValue(VgaDefaultPalette[i]));
        VgaDacRegisters[i * 3 + 2] = VGA_COLOR_TO_DAC(GetBValue(VgaDefaultPalette[i]));
    }
}