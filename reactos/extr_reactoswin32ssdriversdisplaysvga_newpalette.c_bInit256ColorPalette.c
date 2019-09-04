#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_10__ {int ulBitCount; int cPaletteShift; int /*<<< orphan*/  hDriver; TYPE_1__* pPal; } ;
struct TYPE_9__ {int NumEntries; int /*<<< orphan*/ * LookupTable; scalar_t__ FirstEntry; } ;
struct TYPE_8__ {int Red; int Green; int Blue; scalar_t__ Unused; } ;
struct TYPE_7__ {int peRed; int peGreen; int peBlue; } ;
typedef  TYPE_2__* PVIDEO_CLUTDATA ;
typedef  TYPE_3__* PVIDEO_CLUT ;
typedef  TYPE_4__* PPDEV ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISPDBG (int) ; 
 scalar_t__ EngDeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IOCTL_VIDEO_SET_COLOR_REGISTERS ; 
 int MAX_CLUT_SIZE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL bInit256ColorPalette(PPDEV ppdev)
{
    BYTE        ajClutSpace[MAX_CLUT_SIZE];
    PVIDEO_CLUT pScreenClut;
    ULONG       ulReturnedDataLength;
    ULONG       cColors;
    PVIDEO_CLUTDATA pScreenClutData;

    if (ppdev->ulBitCount == 8)
    {
        //
        // Fill in pScreenClut header info:
        //

        pScreenClut             = (PVIDEO_CLUT) ajClutSpace;
        pScreenClut->NumEntries = 256;
        pScreenClut->FirstEntry = 0;

        //
        // Copy colours in:
        //

        cColors = 256;
        pScreenClutData = (PVIDEO_CLUTDATA) (&(pScreenClut->LookupTable[0]));

        while(cColors--)
        {
            pScreenClutData[cColors].Red =    ppdev->pPal[cColors].peRed >>
                                              ppdev->cPaletteShift;
            pScreenClutData[cColors].Green =  ppdev->pPal[cColors].peGreen >>
                                              ppdev->cPaletteShift;
            pScreenClutData[cColors].Blue =   ppdev->pPal[cColors].peBlue >>
                                              ppdev->cPaletteShift;
            pScreenClutData[cColors].Unused = 0;
        }

        //
        // Set palette registers:
        //

        if (EngDeviceIoControl(ppdev->hDriver,
                               IOCTL_VIDEO_SET_COLOR_REGISTERS,
                               pScreenClut,
                               MAX_CLUT_SIZE,
                               NULL,
                               0,
                               &ulReturnedDataLength))
        {
            DISPDBG((0, "Failed bEnablePalette"));
            return(FALSE);
        }
    }

    DISPDBG((5, "Passed bEnablePalette"));

    return(TRUE);
}