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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CgaPalette2 ; 
 int /*<<< orphan*/ * EgaPalette__16Colors ; 
 int /*<<< orphan*/ * EgaPalette__HiRes ; 
 int /*<<< orphan*/ * VgaPalette ; 
 int /*<<< orphan*/  VgaSetPalette (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID VgaChangePalette(BYTE ModeNumber)
{
    const COLORREF* Palette;
    ULONG Size;

    if (ModeNumber >= 0x13)
    {
        /* VGA modes */
        Palette = VgaPalette;
        Size    = ARRAYSIZE(VgaPalette);
    }
    else if (ModeNumber == 0x10) // || (ModeNumber == 0x0D) || (ModeNumber == 0x0E)
    {
        /* EGA HiRes mode */
        Palette = EgaPalette__HiRes;
        Size    = ARRAYSIZE(EgaPalette__HiRes);
    }
#if 0
    else if ((ModeNumber == 0x04) || (ModeNumber == 0x05))
    {
        /*
         * CGA modes; this palette contains both normal and
         * bright versions of CGA palettes 0 and 1
         */
        Palette = CgaPalette2;
        Size    = ARRAYSIZE(CgaPalette2);
    }
#endif
    else // if ((ModeNumber == 0x0D) || (ModeNumber == 0x0E))
    {
        /* EGA modes */
        Palette = EgaPalette__16Colors;
        Size    = ARRAYSIZE(EgaPalette__16Colors);
    }

    VgaSetPalette(Palette, Size);
}