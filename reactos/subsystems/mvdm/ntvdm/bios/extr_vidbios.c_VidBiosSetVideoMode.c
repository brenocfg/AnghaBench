#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int VideoMode; int VideoPageSize; int VideoPage; int VideoPageOffset; int VGAOptions; int VGASwitches; int ScreenRows; int CharacterHeight; int /*<<< orphan*/  ScreenColumns; } ;
struct TYPE_6__ {int PageSize; int CharacterHeight; int /*<<< orphan*/  CharacterWidth; int /*<<< orphan*/  VgaRegisters; } ;
struct TYPE_5__ {int Y; int /*<<< orphan*/  X; } ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  TYPE_1__ COORD ;
typedef  int BYTE ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int ARRAYSIZE (int /*<<< orphan*/ ) ; 
 int BIOS_MAX_PAGES ; 
 int BIOS_MAX_VIDEO_MODE ; 
 int /*<<< orphan*/  BaseAddress ; 
 TYPE_4__* Bda ; 
 int /*<<< orphan*/  DPRINT1 (char*,int,int,char*,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  FONT_8x14_OFFSET ; 
 int /*<<< orphan*/  FONT_8x16_OFFSET ; 
 int /*<<< orphan*/  FONT_8x8_OFFSET ; 
 int /*<<< orphan*/  Font8x14 ; 
 int /*<<< orphan*/  Font8x16 ; 
 int /*<<< orphan*/  Font8x8 ; 
 int /*<<< orphan*/  HIBYTE (int) ; 
 int /*<<< orphan*/  IOWriteB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_TEXT_MODE (int) ; 
 int /*<<< orphan*/  LOBYTE (int) ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  VGA_CRTC_DATA ; 
 int /*<<< orphan*/  VGA_CRTC_INDEX ; 
 int /*<<< orphan*/  VGA_CRTC_START_ADDR_HIGH_REG ; 
 int /*<<< orphan*/  VGA_CRTC_START_ADDR_LOW_REG ; 
 int VGA_FONT_CHARACTERS ; 
 int /*<<< orphan*/  VIDEO_BIOS_DATA_SEG ; 
 scalar_t__ VbeInitialized ; 
 int /*<<< orphan*/  VbeResetExtendedRegisters () ; 
 int VbeSetExtendedVideoMode (int) ; 
 int /*<<< orphan*/  VgaChangePalette (int) ; 
 int /*<<< orphan*/  VgaClearMemory () ; 
 TYPE_1__ VgaGetDisplayResolution () ; 
 int /*<<< orphan*/  VgaRefreshDisplay () ; 
 int /*<<< orphan*/  VgaSetRegisters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VgaWriteTextModeFont (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VidBiosClearScreen () ; 
 int /*<<< orphan*/  VidBiosSetCursorPosition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VidBiosSetCursorShape (int /*<<< orphan*/ ) ; 
 TYPE_2__* VideoModes ; 
 int getBL () ; 
 int /*<<< orphan*/  getDL () ; 

__attribute__((used)) static BOOLEAN VidBiosSetVideoMode(BYTE ModeNumber)
{
    BYTE Page;
    COORD Resolution;
    BYTE OrgModeNumber = ModeNumber;

    /*
     * IBM standard modes do not clear the screen if the
     * high bit of AL is set (EGA or higher only).
     * See Ralf Brown: http://www.ctyme.com/intr/rb-0069.htm
     * for more information.
     */
    BOOLEAN DoNotClear = !!(ModeNumber & 0x80);

    /* Retrieve the real mode number and check its validity */
    ModeNumber &= 0x7F;
    // if (ModeNumber >= ARRAYSIZE(VideoModes))

    DPRINT1("Switching to mode %02Xh (%02Xh) %s clearing the screen; VgaRegisters = 0x%p\n",
            ModeNumber, OrgModeNumber, (DoNotClear ? "without" : "and"), VideoModes[ModeNumber].VgaRegisters);

    if (ModeNumber > BIOS_MAX_VIDEO_MODE)
    {
        /* This could be an extended video mode, so call the VBE BIOS */
        return VbeSetExtendedVideoMode(ModeNumber);
    }

    if (!VgaSetRegisters(VideoModes[ModeNumber].VgaRegisters)) return FALSE;
    if (VbeInitialized && Bda->VideoMode > BIOS_MAX_VIDEO_MODE)
    {
        /*
         * Since we're switching from an extended video mode to a standard VGA
         * mode, tell the VBE BIOS to reset the extended registers.
         */
        VbeResetExtendedRegisters();
    }

    VgaChangePalette(ModeNumber);

    /* Clear the VGA memory if needed */
    if (!DoNotClear) VgaClearMemory();

    /* Update the values in the BDA */
    Bda->VideoMode       = ModeNumber;
    Bda->VideoPageSize   = VideoModes[ModeNumber].PageSize;
    Bda->VideoPage       = 0;
    Bda->VideoPageOffset = Bda->VideoPage * Bda->VideoPageSize;

    /* 256 KB Video RAM; set bit 7 if we do not clear the screen */
    Bda->VGAOptions      = 0x60 | (Bda->VGAOptions & 0x7F) | (DoNotClear ? 0x80 : 0x00);
    Bda->VGASwitches     = 0xF9;    /* High-resolution  */

    // Bda->VGAFlags;
    // Bda->CrtModeControl;
    // Bda->CrtColorPaletteMask;

    /* Set the start address in the CRTC */
    IOWriteB(VGA_CRTC_INDEX, VGA_CRTC_START_ADDR_LOW_REG);
    IOWriteB(VGA_CRTC_DATA , LOBYTE(Bda->VideoPageOffset));
    IOWriteB(VGA_CRTC_INDEX, VGA_CRTC_START_ADDR_HIGH_REG);
    IOWriteB(VGA_CRTC_DATA , HIBYTE(Bda->VideoPageOffset));

    /* Update the screen size */
    Resolution = VgaGetDisplayResolution();
    // This could be simplified if the VGA helper always returned the resolution
    // in number of pixels, instead of in number of cells for text-modes only...
    if (!IS_TEXT_MODE(ModeNumber))
    {
        Resolution.X /= VideoModes[ModeNumber].CharacterWidth ;
        Resolution.Y /= VideoModes[ModeNumber].CharacterHeight;
    }
    Bda->ScreenColumns = Resolution.X;
    Bda->ScreenRows    = Resolution.Y - 1;

    /* Update the current font */
    Bda->CharacterHeight = VideoModes[ModeNumber].CharacterHeight;
    switch (Bda->CharacterHeight)
    {
        /*
         * Write the default font to the VGA font plane for text-modes only.
         * Update the BIOS INT 43h vector (far pointer to the character range 00h-...).
         */
        case 8:
        {
            if (IS_TEXT_MODE(ModeNumber))
                VgaWriteTextModeFont(0, Font8x8, ARRAYSIZE(Font8x8) / VGA_FONT_CHARACTERS);

            ((PULONG)BaseAddress)[0x43] = MAKELONG(FONT_8x8_OFFSET, VIDEO_BIOS_DATA_SEG);
            break;
        }
        case 14:
        {
            if (IS_TEXT_MODE(ModeNumber))
                VgaWriteTextModeFont(0, Font8x14, ARRAYSIZE(Font8x14) / VGA_FONT_CHARACTERS);

            ((PULONG)BaseAddress)[0x43] = MAKELONG(FONT_8x14_OFFSET, VIDEO_BIOS_DATA_SEG);
            break;
        }
        case 16:
        {
            if (IS_TEXT_MODE(ModeNumber))
                VgaWriteTextModeFont(0, Font8x16, ARRAYSIZE(Font8x16) / VGA_FONT_CHARACTERS);

            ((PULONG)BaseAddress)[0x43] = MAKELONG(FONT_8x16_OFFSET, VIDEO_BIOS_DATA_SEG);
            break;
        }
    }

#if 0 // Commented, because I need to think about how to change correctly the ScreenRows
      // in the code that really use it (the Font generator functions of INT 10h, AH=11h)
      // so that it also changes the screen resolution *in text mode only*.
    switch (getBL())
    {
        case 0x00: Bda->ScreenRows = getDL()-1; break;
        case 0x01: Bda->ScreenRows = 13;        break;
        case 0x03: Bda->ScreenRows = 42;        break;
        case 0x02:
        default  : Bda->ScreenRows = 24;        break;
    }
#endif

    /*
     * Update the cursor shape (text-mode only).
     * Use the default CGA cursor scanline values,
     * see: http://vitaly_filatov.tripod.com/ng/asm/asm_023.2.html
     */
    if (IS_TEXT_MODE(ModeNumber))
        // FIXME: we might read the CRT registers and do the adjustment?
        VidBiosSetCursorShape(MAKEWORD(0x07, 0x06));

    /* Set the cursor position for each page */
    for (Page = 0; Page < BIOS_MAX_PAGES; ++Page)
        VidBiosSetCursorPosition(0, 0, Page);

    if (!DoNotClear) VidBiosClearScreen();

    /* Refresh display */
    VgaRefreshDisplay();

    return TRUE;
}