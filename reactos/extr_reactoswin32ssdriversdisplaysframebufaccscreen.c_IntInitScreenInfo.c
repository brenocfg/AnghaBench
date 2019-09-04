#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int RedChromaticity_x; int RedChromaticity_y; int GreenChromaticity_x; int GreenChromaticity_y; int BlueChromaticity_x; int BlueChromaticity_y; int WhiteChromaticity_x; int WhiteChromaticity_y; int AttributeFlags; int RedGamma; int GreenGamma; int BlueGamma; int WhiteGamma; int /*<<< orphan*/  WhiteChromaticity_Y; } ;
typedef  TYPE_11__ VIDEO_COLOR_CAPABILITIES ;
typedef  scalar_t__ ULONG ;
struct TYPE_39__ {scalar_t__ Y; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_38__ {scalar_t__ Y; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_37__ {scalar_t__ Y; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_36__ {int x; int y; scalar_t__ Y; } ;
struct TYPE_35__ {int x; int y; scalar_t__ Y; } ;
struct TYPE_34__ {int x; int y; scalar_t__ Y; } ;
struct TYPE_33__ {int x; int y; int /*<<< orphan*/  Y; } ;
struct TYPE_32__ {scalar_t__ cy; scalar_t__ cx; } ;
struct TYPE_31__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_30__ {scalar_t__ dmPelsWidth; scalar_t__ dmPelsHeight; int dmBitsPerPel; scalar_t__ dmDisplayFrequency; int /*<<< orphan*/  dmLogPixels; } ;
struct TYPE_29__ {int /*<<< orphan*/  iDitherFormat; int /*<<< orphan*/  flGraphicsCaps; scalar_t__ flGraphicsCaps2; scalar_t__ hpalDefault; scalar_t__ cyDither; scalar_t__ cxDither; scalar_t__ cFonts; } ;
struct TYPE_24__ {int RedGamma; int GreenGamma; int BlueGamma; scalar_t__ MagentaInYellowDye; scalar_t__ CyanInYellowDye; scalar_t__ YellowInMagentaDye; scalar_t__ CyanInMagentaDye; scalar_t__ YellowInCyanDye; scalar_t__ MagentaInCyanDye; TYPE_9__ Yellow; TYPE_8__ Magenta; TYPE_7__ Cyan; TYPE_6__ Blue; TYPE_5__ Green; TYPE_4__ Red; TYPE_3__ AlignmentWhite; } ;
struct TYPE_28__ {scalar_t__ ulHorzRes; scalar_t__ ulVertRes; scalar_t__ ulPanningHorzRes; scalar_t__ ulPanningVertRes; int cBitsPixel; int cPlanes; scalar_t__ ulVRefresh; int ulBltAlignment; int ulAspectX; int ulAspectY; int ulAspectXY; int xStyleStep; int yStyleStep; int denStyleStep; int ulNumColors; int ulNumPalReg; int /*<<< orphan*/  ulHTOutputFormat; int /*<<< orphan*/  ulDACRed; int /*<<< orphan*/  flHTFlags; int /*<<< orphan*/  ulHTPatternSize; int /*<<< orphan*/  ulPrimaryOrder; scalar_t__ ulDevicePelsDPI; TYPE_10__ ciDevice; TYPE_2__ szlPhysSize; TYPE_1__ ptlPhysOffset; int /*<<< orphan*/  ulDACBlue; int /*<<< orphan*/  ulDACGreen; scalar_t__ flRaster; int /*<<< orphan*/  flTextCaps; int /*<<< orphan*/  ulLogPixelsY; int /*<<< orphan*/  ulLogPixelsX; int /*<<< orphan*/  ulVertSize; int /*<<< orphan*/  ulHorzSize; int /*<<< orphan*/  ulTechnology; int /*<<< orphan*/  ulVersion; } ;
struct TYPE_27__ {scalar_t__ ScreenWidth; scalar_t__ ScreenHeight; int BitsPerPixel; scalar_t__ PaletteShift; int /*<<< orphan*/  hDriver; int /*<<< orphan*/  BlueMask; int /*<<< orphan*/  GreenMask; int /*<<< orphan*/  RedMask; int /*<<< orphan*/  MemHeight; int /*<<< orphan*/  MemWidth; int /*<<< orphan*/  ScreenDelta; int /*<<< orphan*/  ModeIndex; } ;
struct TYPE_26__ {scalar_t__ Length; scalar_t__ VisScreenWidth; scalar_t__ VisScreenHeight; int BitsPerPlane; int NumberOfPlanes; scalar_t__ Frequency; int /*<<< orphan*/  NumberBlueBits; int /*<<< orphan*/  NumberGreenBits; int /*<<< orphan*/  NumberRedBits; int /*<<< orphan*/  YMillimeter; int /*<<< orphan*/  XMillimeter; int /*<<< orphan*/  BlueMask; int /*<<< orphan*/  GreenMask; int /*<<< orphan*/  RedMask; int /*<<< orphan*/  VideoMemoryBitmapHeight; int /*<<< orphan*/  VideoMemoryBitmapWidth; int /*<<< orphan*/  ScreenStride; int /*<<< orphan*/  ModeIndex; } ;
typedef  TYPE_12__* PVIDEO_MODE_INFORMATION ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_13__* PPDEV ;
typedef  TYPE_14__* PGDIINFO ;
typedef  TYPE_15__* PDEVINFO ;
typedef  TYPE_16__* LPDEVMODEW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BMF_16BPP ; 
 int /*<<< orphan*/  BMF_24BPP ; 
 int /*<<< orphan*/  BMF_32BPP ; 
 int /*<<< orphan*/  BMF_8BPP ; 
 int /*<<< orphan*/  DT_RASDISPLAY ; 
 int /*<<< orphan*/  EngDeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_11__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  EngFreeMem (TYPE_12__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GCAPS_PALMANAGED ; 
 int /*<<< orphan*/  GDI_DRIVER_VERSION ; 
 scalar_t__ GetAvailableModes (int /*<<< orphan*/ ,TYPE_12__**,scalar_t__*) ; 
 int /*<<< orphan*/  HT_FLAG_ADDITIVE_PRIMS ; 
 int /*<<< orphan*/  HT_FORMAT_16BPP ; 
 int /*<<< orphan*/  HT_FORMAT_24BPP ; 
 int /*<<< orphan*/  HT_FORMAT_32BPP ; 
 int /*<<< orphan*/  HT_FORMAT_8BPP ; 
 int /*<<< orphan*/  HT_PATSIZE_4x4_M ; 
 int /*<<< orphan*/  IOCTL_VIDEO_QUERY_COLOR_CAPABILITIES ; 
 int /*<<< orphan*/  PRIMARY_ORDER_CBA ; 
 int /*<<< orphan*/  TC_RA_ABLE ; 
 int /*<<< orphan*/  TRUE ; 
 int VIDEO_DEVICE_COLOR ; 

BOOL
IntInitScreenInfo(
   PPDEV ppdev,
   LPDEVMODEW pDevMode,
   PGDIINFO pGdiInfo,
   PDEVINFO pDevInfo)
{
   ULONG ModeCount;
   ULONG ModeInfoSize;
   PVIDEO_MODE_INFORMATION ModeInfo, ModeInfoPtr, SelectedMode = NULL;
   VIDEO_COLOR_CAPABILITIES ColorCapabilities;
/* hack 
   LOGFONTW SystemFont = {16, 7, 0, 0, 700, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, L"System"};
   LOGFONTW AnsiVariableFont = {12, 9, 0, 0, 400, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_STROKE_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_DONTCARE, L"MS Sans Serif"};
   LOGFONTW AnsiFixedFont = {12, 9, 0, 0, 400, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_STROKE_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_DONTCARE, L"Courier"};
*/
   ULONG Temp;

   /*
    * Call miniport to get information about video modes.
    */

   ModeCount = GetAvailableModes(ppdev->hDriver, &ModeInfo, &ModeInfoSize);
   if (ModeCount == 0)
   {
      return FALSE;
   }

   /*
    * Select the video mode depending on the info passed in pDevMode.
    */

   if (pDevMode->dmPelsWidth == 0 && pDevMode->dmPelsHeight == 0 &&
       pDevMode->dmBitsPerPel == 0 && pDevMode->dmDisplayFrequency == 0)
   {
      ModeInfoPtr = ModeInfo;
      while (ModeCount-- > 0)
      {
         if (ModeInfoPtr->Length == 0)
         {
            ModeInfoPtr = (PVIDEO_MODE_INFORMATION)
               (((PUCHAR)ModeInfoPtr) + ModeInfoSize);
            continue;
         }
         SelectedMode = ModeInfoPtr;
         break;
      }
   }
   else
   {
      ModeInfoPtr = ModeInfo;
      while (ModeCount-- > 0)
      {
         if (ModeInfoPtr->Length > 0 &&
	     pDevMode->dmPelsWidth == ModeInfoPtr->VisScreenWidth &&
             pDevMode->dmPelsHeight == ModeInfoPtr->VisScreenHeight &&
             pDevMode->dmBitsPerPel == (ModeInfoPtr->BitsPerPlane *
                                        ModeInfoPtr->NumberOfPlanes) &&
             pDevMode->dmDisplayFrequency == ModeInfoPtr->Frequency)
         {
            SelectedMode = ModeInfoPtr;
            break;
         }

         ModeInfoPtr = (PVIDEO_MODE_INFORMATION)
            (((PUCHAR)ModeInfoPtr) + ModeInfoSize);
      }
   }

   if (SelectedMode == NULL)
   {
      EngFreeMem(ModeInfo);
      return FALSE;
   }

   /*
    * Fill in the GDIINFO data structure with the information returned from
    * the kernel driver.
    */

   ppdev->ModeIndex = SelectedMode->ModeIndex;
   ppdev->ScreenWidth = SelectedMode->VisScreenWidth;
   ppdev->ScreenHeight = SelectedMode->VisScreenHeight;
   ppdev->ScreenDelta = SelectedMode->ScreenStride;
   ppdev->BitsPerPixel = SelectedMode->BitsPerPlane * SelectedMode->NumberOfPlanes;

   ppdev->MemWidth = SelectedMode->VideoMemoryBitmapWidth;
   ppdev->MemHeight = SelectedMode->VideoMemoryBitmapHeight;

   ppdev->RedMask = SelectedMode->RedMask;
   ppdev->GreenMask = SelectedMode->GreenMask;
   ppdev->BlueMask = SelectedMode->BlueMask;

   pGdiInfo->ulVersion = GDI_DRIVER_VERSION;
   pGdiInfo->ulTechnology = DT_RASDISPLAY;
   pGdiInfo->ulHorzSize = SelectedMode->XMillimeter;
   pGdiInfo->ulVertSize = SelectedMode->YMillimeter;
   pGdiInfo->ulHorzRes = SelectedMode->VisScreenWidth;
   pGdiInfo->ulVertRes = SelectedMode->VisScreenHeight;
   pGdiInfo->ulPanningHorzRes = SelectedMode->VisScreenWidth;
   pGdiInfo->ulPanningVertRes = SelectedMode->VisScreenHeight;
   pGdiInfo->cBitsPixel = SelectedMode->BitsPerPlane;
   pGdiInfo->cPlanes = SelectedMode->NumberOfPlanes;
   pGdiInfo->ulVRefresh = SelectedMode->Frequency;
   pGdiInfo->ulBltAlignment = 1;
   pGdiInfo->ulLogPixelsX = pDevMode->dmLogPixels;
   pGdiInfo->ulLogPixelsY = pDevMode->dmLogPixels;
   pGdiInfo->flTextCaps = TC_RA_ABLE;
   pGdiInfo->flRaster = 0;
   pGdiInfo->ulDACRed = SelectedMode->NumberRedBits;
   pGdiInfo->ulDACGreen = SelectedMode->NumberGreenBits;
   pGdiInfo->ulDACBlue = SelectedMode->NumberBlueBits;
   pGdiInfo->ulAspectX = 0x24;
   pGdiInfo->ulAspectY = 0x24;
   pGdiInfo->ulAspectXY = 0x33;
   pGdiInfo->xStyleStep = 1;
   pGdiInfo->yStyleStep = 1;
   pGdiInfo->denStyleStep = 3;
   pGdiInfo->ptlPhysOffset.x = 0;
   pGdiInfo->ptlPhysOffset.y = 0;
   pGdiInfo->szlPhysSize.cx = 0;
   pGdiInfo->szlPhysSize.cy = 0;

   /*
    * Try to get the color info from the miniport.
    */

   if (!EngDeviceIoControl(ppdev->hDriver, IOCTL_VIDEO_QUERY_COLOR_CAPABILITIES,
                           NULL, 0, &ColorCapabilities,
                           sizeof(VIDEO_COLOR_CAPABILITIES), &Temp))
   {
      pGdiInfo->ciDevice.Red.x = ColorCapabilities.RedChromaticity_x;
      pGdiInfo->ciDevice.Red.y = ColorCapabilities.RedChromaticity_y;
      pGdiInfo->ciDevice.Green.x = ColorCapabilities.GreenChromaticity_x;
      pGdiInfo->ciDevice.Green.y = ColorCapabilities.GreenChromaticity_y;
      pGdiInfo->ciDevice.Blue.x = ColorCapabilities.BlueChromaticity_x;
      pGdiInfo->ciDevice.Blue.y = ColorCapabilities.BlueChromaticity_y;
      pGdiInfo->ciDevice.AlignmentWhite.x = ColorCapabilities.WhiteChromaticity_x;
      pGdiInfo->ciDevice.AlignmentWhite.y = ColorCapabilities.WhiteChromaticity_y;
      pGdiInfo->ciDevice.AlignmentWhite.Y = ColorCapabilities.WhiteChromaticity_Y;
      if (ColorCapabilities.AttributeFlags & VIDEO_DEVICE_COLOR)
      {
         pGdiInfo->ciDevice.RedGamma = ColorCapabilities.RedGamma;
         pGdiInfo->ciDevice.GreenGamma = ColorCapabilities.GreenGamma;
         pGdiInfo->ciDevice.BlueGamma = ColorCapabilities.BlueGamma;
      }
      else
      {
         pGdiInfo->ciDevice.RedGamma = ColorCapabilities.WhiteGamma;
         pGdiInfo->ciDevice.GreenGamma = ColorCapabilities.WhiteGamma;
         pGdiInfo->ciDevice.BlueGamma = ColorCapabilities.WhiteGamma;
      }
   }
   else
   {
      pGdiInfo->ciDevice.Red.x = 6700;
      pGdiInfo->ciDevice.Red.y = 3300;
      pGdiInfo->ciDevice.Green.x = 2100;
      pGdiInfo->ciDevice.Green.y = 7100;
      pGdiInfo->ciDevice.Blue.x = 1400;
      pGdiInfo->ciDevice.Blue.y = 800;
      pGdiInfo->ciDevice.AlignmentWhite.x = 3127;
      pGdiInfo->ciDevice.AlignmentWhite.y = 3290;
      pGdiInfo->ciDevice.AlignmentWhite.Y = 0;
      pGdiInfo->ciDevice.RedGamma = 20000;
      pGdiInfo->ciDevice.GreenGamma = 20000;
      pGdiInfo->ciDevice.BlueGamma = 20000;
   }

   pGdiInfo->ciDevice.Red.Y = 0;
   pGdiInfo->ciDevice.Green.Y = 0;
   pGdiInfo->ciDevice.Blue.Y = 0;
   pGdiInfo->ciDevice.Cyan.x = 0;
   pGdiInfo->ciDevice.Cyan.y = 0;
   pGdiInfo->ciDevice.Cyan.Y = 0;
   pGdiInfo->ciDevice.Magenta.x = 0;
   pGdiInfo->ciDevice.Magenta.y = 0;
   pGdiInfo->ciDevice.Magenta.Y = 0;
   pGdiInfo->ciDevice.Yellow.x = 0;
   pGdiInfo->ciDevice.Yellow.y = 0;
   pGdiInfo->ciDevice.Yellow.Y = 0;
   pGdiInfo->ciDevice.MagentaInCyanDye = 0;
   pGdiInfo->ciDevice.YellowInCyanDye = 0;
   pGdiInfo->ciDevice.CyanInMagentaDye = 0;
   pGdiInfo->ciDevice.YellowInMagentaDye = 0;
   pGdiInfo->ciDevice.CyanInYellowDye = 0;
   pGdiInfo->ciDevice.MagentaInYellowDye = 0;
   pGdiInfo->ulDevicePelsDPI = 0;
   pGdiInfo->ulPrimaryOrder = PRIMARY_ORDER_CBA;
   pGdiInfo->ulHTPatternSize = HT_PATSIZE_4x4_M;
   pGdiInfo->flHTFlags = HT_FLAG_ADDITIVE_PRIMS;

   pDevInfo->flGraphicsCaps = 0;
/* hack 
   pDevInfo->lfDefaultFont = SystemFont;
   pDevInfo->lfAnsiVarFont = AnsiVariableFont;
   pDevInfo->lfAnsiFixFont = AnsiFixedFont;
*/
   pDevInfo->cFonts = 0;
   pDevInfo->cxDither = 0;
   pDevInfo->cyDither = 0;
   pDevInfo->hpalDefault = 0;
   pDevInfo->flGraphicsCaps2 = 0;

   if (ppdev->BitsPerPixel == 8)
   {
      pGdiInfo->ulNumColors = 20;
      pGdiInfo->ulNumPalReg = 1 << ppdev->BitsPerPixel;
      pGdiInfo->ulHTOutputFormat = HT_FORMAT_8BPP;
      pDevInfo->flGraphicsCaps |= GCAPS_PALMANAGED;
      pDevInfo->iDitherFormat = BMF_8BPP;
      /* Assuming palette is orthogonal - all colors are same size. */
      ppdev->PaletteShift = 8 - pGdiInfo->ulDACRed;
   }
   else
   {
      pGdiInfo->ulNumColors = (ULONG)(-1);
      pGdiInfo->ulNumPalReg = 0;
      switch (ppdev->BitsPerPixel)
      {
         case 16:
            pGdiInfo->ulHTOutputFormat = HT_FORMAT_16BPP;
            pDevInfo->iDitherFormat = BMF_16BPP;
            break;

         case 24:
            pGdiInfo->ulHTOutputFormat = HT_FORMAT_24BPP;
            pDevInfo->iDitherFormat = BMF_24BPP;
            break;

         default:
            pGdiInfo->ulHTOutputFormat = HT_FORMAT_32BPP;
            pDevInfo->iDitherFormat = BMF_32BPP;
      }
   }

   EngFreeMem(ModeInfo);
   return TRUE;
}