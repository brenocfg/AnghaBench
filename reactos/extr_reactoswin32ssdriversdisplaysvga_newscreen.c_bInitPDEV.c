#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_14__ {scalar_t__ dmPelsWidth; scalar_t__ dmPelsHeight; int dmBitsPerPel; scalar_t__ dmDisplayFrequency; int /*<<< orphan*/  dmLogPixels; } ;
struct TYPE_13__ {scalar_t__ ulHorzRes; scalar_t__ ulVertRes; scalar_t__ ulPanningHorzRes; scalar_t__ ulPanningVertRes; int cBitsPixel; int cPlanes; scalar_t__ ulVRefresh; int ulBltAlignment; int /*<<< orphan*/  ulDACBlue; int /*<<< orphan*/  ulDACGreen; int /*<<< orphan*/  ulDACRed; int /*<<< orphan*/  ulLogPixelsY; int /*<<< orphan*/  ulLogPixelsX; int /*<<< orphan*/  ulVertSize; int /*<<< orphan*/  ulHorzSize; int /*<<< orphan*/  ulTechnology; int /*<<< orphan*/  ulVersion; } ;
struct TYPE_12__ {scalar_t__ cxScreen; scalar_t__ cyScreen; int /*<<< orphan*/  lDeltaScreen; int /*<<< orphan*/  ulMode; int /*<<< orphan*/  hDriver; } ;
struct TYPE_11__ {scalar_t__ Length; scalar_t__ VisScreenWidth; scalar_t__ VisScreenHeight; int BitsPerPlane; int NumberOfPlanes; scalar_t__ Frequency; int /*<<< orphan*/  NumberBlueBits; int /*<<< orphan*/  NumberGreenBits; int /*<<< orphan*/  NumberRedBits; int /*<<< orphan*/  YMillimeter; int /*<<< orphan*/  XMillimeter; int /*<<< orphan*/  ScreenStride; int /*<<< orphan*/  ModeIndex; } ;
typedef  TYPE_1__* PVIDEO_MODE_INFORMATION ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_2__* PPDEV ;
typedef  TYPE_3__ GDIINFO ;
typedef  TYPE_4__ DEVMODEW ;
typedef  int /*<<< orphan*/  DEVINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISPDBG (int) ; 
 int /*<<< orphan*/  DT_RASDISPLAY ; 
 int /*<<< orphan*/  EngFreeMem (TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GDI_DRIVER_VERSION ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  gDevInfoFrameBuffer ; 
 TYPE_3__ gaulCap ; 
 scalar_t__ getAvailableModes (int /*<<< orphan*/ ,TYPE_1__**,scalar_t__*) ; 

BOOL bInitPDEV(
PPDEV ppdev,
DEVMODEW *pDevMode,
GDIINFO *pGdiInfo,
DEVINFO *pDevInfo)
{
    ULONG cModes;
    PVIDEO_MODE_INFORMATION pVideoBuffer, pVideoModeSelected, pVideoTemp;
#if 0
    VIDEO_COLOR_CAPABILITIES colorCapabilities;
    ULONG ulTemp;
#endif
    BOOL bSelectDefault;
    ULONG cbModeSize;

    //
    // calls the miniport to get mode information.
    //

    cModes = getAvailableModes(ppdev->hDriver, &pVideoBuffer, &cbModeSize);

    if (cModes == 0)
    {
        return(FALSE);
    }

    //
    // Now see if the requested mode has a match in that table.
    //

    pVideoModeSelected = NULL;
    pVideoTemp = pVideoBuffer;

    if ((pDevMode->dmPelsWidth        == 0) &&
        (pDevMode->dmPelsHeight       == 0) &&
        (pDevMode->dmBitsPerPel       == 0) &&
        (pDevMode->dmDisplayFrequency == 0))
    {
        DISPDBG((2, "Default mode requested"));
        bSelectDefault = TRUE;
    }
    else
    {
// eVb: 2.5 [DDK Change] - Add missing newlines to debug output
        DISPDBG((2, "Requested mode...\n"));
        DISPDBG((2, "   Screen width  -- %li\n", pDevMode->dmPelsWidth));
        DISPDBG((2, "   Screen height -- %li\n", pDevMode->dmPelsHeight));
        DISPDBG((2, "   Bits per pel  -- %li\n", pDevMode->dmBitsPerPel));
        DISPDBG((2, "   Frequency     -- %li\n", pDevMode->dmDisplayFrequency));
// eVb: 2.5 [END]
        bSelectDefault = FALSE;
    }

    while (cModes--)
    {
        if (pVideoTemp->Length != 0)
        {
            if (bSelectDefault ||
                ((pVideoTemp->VisScreenWidth  == pDevMode->dmPelsWidth) &&
                 (pVideoTemp->VisScreenHeight == pDevMode->dmPelsHeight) &&
                 (pVideoTemp->BitsPerPlane *
                  pVideoTemp->NumberOfPlanes  == pDevMode->dmBitsPerPel) &&
                 (pVideoTemp->Frequency  == pDevMode->dmDisplayFrequency)))
            {
                pVideoModeSelected = pVideoTemp;
                DISPDBG((3, "Found a match\n")) ;
                break;
            }
        }

        pVideoTemp = (PVIDEO_MODE_INFORMATION)
            (((PUCHAR)pVideoTemp) + cbModeSize);
    }

    //
    // If no mode has been found, return an error
    //

    if (pVideoModeSelected == NULL)
    {
        EngFreeMem(pVideoBuffer);
        DISPDBG((0,"DISP bInitPDEV failed - no valid modes\n"));
        return(FALSE);
    }

    //
    // Fill in the GDIINFO data structure with the information returned from
    // the kernel driver.
    //

    ppdev->ulMode = pVideoModeSelected->ModeIndex;
    ppdev->cxScreen = pVideoModeSelected->VisScreenWidth;
    ppdev->cyScreen = pVideoModeSelected->VisScreenHeight;
    ppdev->lDeltaScreen = pVideoModeSelected->ScreenStride;
// eVb: 2.8 [VGARISC CHANGE] - Extra fields not required on VGA, start with defaults
#if 0
    ppdev->ulBitCount = pVideoModeSelected->BitsPerPlane *
                        pVideoModeSelected->NumberOfPlanes;
    ppdev->flRed = pVideoModeSelected->RedMask;
    ppdev->flGreen = pVideoModeSelected->GreenMask;
    ppdev->flBlue = pVideoModeSelected->BlueMask;
#else
    *pGdiInfo = gaulCap;
#endif
// eVb: 2.8 [END]


    pGdiInfo->ulVersion    = GDI_DRIVER_VERSION;
    pGdiInfo->ulTechnology = DT_RASDISPLAY;
    pGdiInfo->ulHorzSize   = pVideoModeSelected->XMillimeter;
    pGdiInfo->ulVertSize   = pVideoModeSelected->YMillimeter;

    pGdiInfo->ulHorzRes        = ppdev->cxScreen;
    pGdiInfo->ulVertRes        = ppdev->cyScreen;
    pGdiInfo->ulPanningHorzRes = ppdev->cxScreen;
    pGdiInfo->ulPanningVertRes = ppdev->cyScreen;
    pGdiInfo->cBitsPixel       = pVideoModeSelected->BitsPerPlane;
    pGdiInfo->cPlanes          = pVideoModeSelected->NumberOfPlanes;
    pGdiInfo->ulVRefresh       = pVideoModeSelected->Frequency;
    pGdiInfo->ulBltAlignment   = 1;     // We don't have accelerated screen-
                                        //   to-screen blts, and any
                                        //   window alignment is okay

    pGdiInfo->ulLogPixelsX = pDevMode->dmLogPixels;
    pGdiInfo->ulLogPixelsY = pDevMode->dmLogPixels;

// eVb: 2.9 [VGARISC CHANGE] - Extra fields not required on VGA
#if 0
#ifdef MIPS
    if (ppdev->ulBitCount == 8)
        pGdiInfo->flTextCaps = (TC_RA_ABLE | TC_SCROLLBLT);
    else
#endif
    pGdiInfo->flTextCaps = TC_RA_ABLE;

    pGdiInfo->flRaster = 0;           // flRaster is reserved by DDI
#endif
// eVb: 2.9 [END]

    pGdiInfo->ulDACRed   = pVideoModeSelected->NumberRedBits;
    pGdiInfo->ulDACGreen = pVideoModeSelected->NumberGreenBits;
    pGdiInfo->ulDACBlue  = pVideoModeSelected->NumberBlueBits;

// eVb: 2.7 [VGARISC CHANGE] - Extra fields not required on VGA
#if 0
    pGdiInfo->ulAspectX    = 0x24;    // One-to-one aspect ratio
    pGdiInfo->ulAspectY    = 0x24;
    pGdiInfo->ulAspectXY   = 0x33;

    pGdiInfo->xStyleStep   = 1;       // A style unit is 3 pels
    pGdiInfo->yStyleStep   = 1;
    pGdiInfo->denStyleStep = 3;

    pGdiInfo->ptlPhysOffset.x = 0;
    pGdiInfo->ptlPhysOffset.y = 0;
    pGdiInfo->szlPhysSize.cx  = 0;
    pGdiInfo->szlPhysSize.cy  = 0;

    // RGB and CMY color info.

    //
    // try to get it from the miniport.
    // if the miniport doesn ot support this feature, use defaults.
    //

    if (EngDeviceIoControl(ppdev->hDriver,
                           IOCTL_VIDEO_QUERY_COLOR_CAPABILITIES,
                           NULL,
                           0,
                           &colorCapabilities,
                           sizeof(VIDEO_COLOR_CAPABILITIES),
                           &ulTemp))
    {

        DISPDBG((2, "getcolorCapabilities failed \n"));

        pGdiInfo->ciDevice.Red.x = 6700;
        pGdiInfo->ciDevice.Red.y = 3300;
        pGdiInfo->ciDevice.Red.Y = 0;
        pGdiInfo->ciDevice.Green.x = 2100;
        pGdiInfo->ciDevice.Green.y = 7100;
        pGdiInfo->ciDevice.Green.Y = 0;
        pGdiInfo->ciDevice.Blue.x = 1400;
        pGdiInfo->ciDevice.Blue.y = 800;
        pGdiInfo->ciDevice.Blue.Y = 0;
        pGdiInfo->ciDevice.AlignmentWhite.x = 3127;
        pGdiInfo->ciDevice.AlignmentWhite.y = 3290;
        pGdiInfo->ciDevice.AlignmentWhite.Y = 0;

        pGdiInfo->ciDevice.RedGamma = 20000;
        pGdiInfo->ciDevice.GreenGamma = 20000;
        pGdiInfo->ciDevice.BlueGamma = 20000;

    }
    else
    {
        pGdiInfo->ciDevice.Red.x = colorCapabilities.RedChromaticity_x;
        pGdiInfo->ciDevice.Red.y = colorCapabilities.RedChromaticity_y;
        pGdiInfo->ciDevice.Red.Y = 0;
        pGdiInfo->ciDevice.Green.x = colorCapabilities.GreenChromaticity_x;
        pGdiInfo->ciDevice.Green.y = colorCapabilities.GreenChromaticity_y;
        pGdiInfo->ciDevice.Green.Y = 0;
        pGdiInfo->ciDevice.Blue.x = colorCapabilities.BlueChromaticity_x;
        pGdiInfo->ciDevice.Blue.y = colorCapabilities.BlueChromaticity_y;
        pGdiInfo->ciDevice.Blue.Y = 0;
        pGdiInfo->ciDevice.AlignmentWhite.x = colorCapabilities.WhiteChromaticity_x;
        pGdiInfo->ciDevice.AlignmentWhite.y = colorCapabilities.WhiteChromaticity_y;
        pGdiInfo->ciDevice.AlignmentWhite.Y = colorCapabilities.WhiteChromaticity_Y;

        // if we have a color device store the three color gamma values,
        // otherwise store the unique gamma value in all three.

        if (colorCapabilities.AttributeFlags & VIDEO_DEVICE_COLOR)
        {
            pGdiInfo->ciDevice.RedGamma = colorCapabilities.RedGamma;
            pGdiInfo->ciDevice.GreenGamma = colorCapabilities.GreenGamma;
            pGdiInfo->ciDevice.BlueGamma = colorCapabilities.BlueGamma;
        }
        else
        {
            pGdiInfo->ciDevice.RedGamma = colorCapabilities.WhiteGamma;
            pGdiInfo->ciDevice.GreenGamma = colorCapabilities.WhiteGamma;
            pGdiInfo->ciDevice.BlueGamma = colorCapabilities.WhiteGamma;
        }

    };

    pGdiInfo->ciDevice.Cyan.x = 0;
    pGdiInfo->ciDevice.Cyan.y = 0;
    pGdiInfo->ciDevice.Cyan.Y = 0;
    pGdiInfo->ciDevice.Magenta.x = 0;
    pGdiInfo->ciDevice.Magenta.y = 0;
    pGdiInfo->ciDevice.Magenta.Y = 0;
    pGdiInfo->ciDevice.Yellow.x = 0;
    pGdiInfo->ciDevice.Yellow.y = 0;
    pGdiInfo->ciDevice.Yellow.Y = 0;

    // No dye correction for raster displays.

    pGdiInfo->ciDevice.MagentaInCyanDye = 0;
    pGdiInfo->ciDevice.YellowInCyanDye = 0;
    pGdiInfo->ciDevice.CyanInMagentaDye = 0;
    pGdiInfo->ciDevice.YellowInMagentaDye = 0;
    pGdiInfo->ciDevice.CyanInYellowDye = 0;
    pGdiInfo->ciDevice.MagentaInYellowDye = 0;

    pGdiInfo->ulDevicePelsDPI = 0;   // For printers only
    pGdiInfo->ulPrimaryOrder = PRIMARY_ORDER_CBA;

    // BUGBUG this should be modified to take into account the size
    // of the display and the resolution.

    pGdiInfo->ulHTPatternSize = HT_PATSIZE_4x4_M;

    pGdiInfo->flHTFlags = HT_FLAG_ADDITIVE_PRIMS;
// eVb: 2.7 [END]
#endif

    // Fill in the basic devinfo structure

    *pDevInfo = gDevInfoFrameBuffer;

// eVb: 2.6 [VGARISC CHANGE] - Use defaults in gaulCap for GDI Info
#if 0
    // Fill in the rest of the devinfo and GdiInfo structures.

    if (ppdev->ulBitCount == 8)
    {
        // It is Palette Managed.

        pGdiInfo->ulNumColors = 20;
        pGdiInfo->ulNumPalReg = 1 << ppdev->ulBitCount;
// eVb: 2.7 [DDK CHANGE] - No dithering support
        pDevInfo->flGraphicsCaps |= GCAPS_PALMANAGED;
// eVb: 2.7 [END]
        pGdiInfo->ulHTOutputFormat = HT_FORMAT_8BPP;
        pDevInfo->iDitherFormat = BMF_8BPP;

        // Assuming palette is orthogonal - all colors are same size.

        ppdev->cPaletteShift   = 8 - pGdiInfo->ulDACRed;
    }
    else
    {
        pGdiInfo->ulNumColors = (ULONG) (-1);
        pGdiInfo->ulNumPalReg = 0;

        if (ppdev->ulBitCount == 16)
        {
            pGdiInfo->ulHTOutputFormat = HT_FORMAT_16BPP;
            pDevInfo->iDitherFormat = BMF_16BPP;
        }
        else if (ppdev->ulBitCount == 24)
        {
            pGdiInfo->ulHTOutputFormat = HT_FORMAT_24BPP;
            pDevInfo->iDitherFormat = BMF_24BPP;
        }
        else
        {
            pGdiInfo->ulHTOutputFormat = HT_FORMAT_32BPP;
            pDevInfo->iDitherFormat = BMF_32BPP;
        }
    }
#endif
// eVb: 2.6 [END]

    EngFreeMem(pVideoBuffer);

    return(TRUE);
}