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
typedef  int ULONG ;
struct TYPE_10__ {int /*<<< orphan*/  palPalEntry; } ;
struct TYPE_9__ {scalar_t__ hpalDefault; } ;
struct TYPE_8__ {void* peFlags; void* peBlue; void* peGreen; void* peRed; } ;
struct TYPE_7__ {int ulBitCount; scalar_t__ hpalDefault; int /*<<< orphan*/  flBlue; int /*<<< orphan*/  flGreen; int /*<<< orphan*/  flRed; TYPE_2__* pPal; } ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  TYPE_1__* PPDEV ;
typedef  TYPE_2__* PPALETTEENTRY ;
typedef  int /*<<< orphan*/  PALETTEENTRY ;
typedef  scalar_t__ HPALETTE ;
typedef  TYPE_3__ DEVINFO ;
typedef  void* BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 void** BASEPALETTE ; 
 scalar_t__ EngAllocMem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* EngCreatePalette (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PAL_BITFIELDS ; 
 int /*<<< orphan*/  PAL_INDEXED ; 
 int /*<<< orphan*/  RIP (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ logPalVGA ; 

BOOL bInitDefaultPalette(PPDEV ppdev, DEVINFO *pDevInfo)
{
// eVb: 4.3 [VGARISC Change] - VGA Palette is static, no need to build
#if 0
    if (ppdev->ulBitCount == 8)
    {
        ULONG ulLoop;
        BYTE jRed,jGre,jBlu;

        //
        // Allocate our palette
        //

        ppdev->pPal = (PPALETTEENTRY)EngAllocMem(0, sizeof(PALETTEENTRY) * 256,
                                                 ALLOC_TAG);

        if ((ppdev->pPal) == NULL) {
            RIP("DISP bInitDefaultPalette() failed EngAllocMem\n");
            return(FALSE);
        }

        //
        // Generate 256 (8*4*4) RGB combinations to fill the palette
        //

        jRed = jGre = jBlu = 0;

        for (ulLoop = 0; ulLoop < 256; ulLoop++)
        {
            ppdev->pPal[ulLoop].peRed   = jRed;
            ppdev->pPal[ulLoop].peGreen = jGre;
            ppdev->pPal[ulLoop].peBlue  = jBlu;
            ppdev->pPal[ulLoop].peFlags = (BYTE)0;

            if (!(jRed += 32))
            if (!(jGre += 32))
            jBlu += 64;
        }

        //
        // Fill in Windows Reserved Colors from the WIN 3.0 DDK
        // The Window Manager reserved the first and last 10 colors for
        // painting windows borders and for non-palette managed applications.
        //

        for (ulLoop = 0; ulLoop < 10; ulLoop++)
        {
            //
            // First 10
            //

            ppdev->pPal[ulLoop] = BASEPALETTE[ulLoop];

            //
            // Last 10
            //

            ppdev->pPal[246 + ulLoop] = BASEPALETTE[ulLoop+10];
        }

#endif
// eVb: 4.3 [END]
        //
        // Create handle for palette.
        //

        ppdev->hpalDefault =
        pDevInfo->hpalDefault = EngCreatePalette(PAL_INDEXED,
// eVb: 4.4 [VGARISC Change] - VGA Palette is 16 colors, not 256, and static
                                                   16,
                                                   (PULONG) &logPalVGA.palPalEntry,
// eVb: 4.4 [END]
                                                   0,0,0);

        if (ppdev->hpalDefault == (HPALETTE) 0)
        {
            RIP("DISP bInitDefaultPalette failed EngCreatePalette\n");
// eVb: 4.5 [VGARISC Change] - VGA Palette is static, no need to free
            //EngFreeMem(ppdev->pPal);
// eVb: 4.5 [END]        
            return(FALSE);
        }

        //
        // Initialize the hardware with the initial palette.
        //

        return(TRUE);

// eVb: 4.6 [VGARISC Change] - VGA Palette is static, no bitfield palette needed
#if 0
    } else {

        ppdev->hpalDefault =
        pDevInfo->hpalDefault = EngCreatePalette(PAL_BITFIELDS,
                                                   0,(PULONG) NULL,
                                                   ppdev->flRed,
                                                   ppdev->flGreen,
                                                   ppdev->flBlue);

        if (ppdev->hpalDefault == (HPALETTE) 0)
        {
            RIP("DISP bInitDefaultPalette failed EngCreatePalette\n");
            return(FALSE);
        }
    }

    return(TRUE);
#endif
// eVb: 4.6 [END]  
}