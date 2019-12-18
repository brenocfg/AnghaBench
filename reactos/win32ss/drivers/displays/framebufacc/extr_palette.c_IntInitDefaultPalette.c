#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_10__ {int /*<<< orphan*/ * hpalDefault; } ;
struct TYPE_9__ {int peRed; int peGreen; int peBlue; scalar_t__ peFlags; } ;
struct TYPE_8__ {int BitsPerPixel; int /*<<< orphan*/ * DefaultPalette; TYPE_2__* PaletteEntries; int /*<<< orphan*/  BlueMask; int /*<<< orphan*/  GreenMask; int /*<<< orphan*/  RedMask; } ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  TYPE_1__* PPDEV ;
typedef  TYPE_2__* PPALETTEENTRY ;
typedef  TYPE_3__* PDEVINFO ;
typedef  int /*<<< orphan*/  PALETTEENTRY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 scalar_t__ BASEPALETTE ; 
 TYPE_2__* EngAllocMem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* EngCreatePalette (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PAL_BITFIELDS ; 
 int /*<<< orphan*/  PAL_INDEXED ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,scalar_t__,int) ; 

BOOL
IntInitDefaultPalette(
   PPDEV ppdev,
   PDEVINFO pDevInfo)
{
   ULONG ColorLoop;
   PPALETTEENTRY PaletteEntryPtr;

   if (ppdev->BitsPerPixel > 8)
   {
      ppdev->DefaultPalette = pDevInfo->hpalDefault =
         EngCreatePalette(PAL_BITFIELDS, 0, NULL,
            ppdev->RedMask, ppdev->GreenMask, ppdev->BlueMask);
   }
   else
   {
      ppdev->PaletteEntries = EngAllocMem(0, sizeof(PALETTEENTRY) << 8, ALLOC_TAG);
      if (ppdev->PaletteEntries == NULL)
      {
         return FALSE;
      }

      for (ColorLoop = 256, PaletteEntryPtr = ppdev->PaletteEntries;
           ColorLoop != 0;
           ColorLoop--, PaletteEntryPtr++)
      {
         PaletteEntryPtr->peRed = ((ColorLoop >> 5) & 7) * 255 / 7;
         PaletteEntryPtr->peGreen = ((ColorLoop >> 3) & 3) * 255 / 3;
         PaletteEntryPtr->peBlue = (ColorLoop & 7) * 255 / 7;
         PaletteEntryPtr->peFlags = 0;
      }

      memcpy(ppdev->PaletteEntries, BASEPALETTE, 10 * sizeof(PALETTEENTRY));
      memcpy(ppdev->PaletteEntries + 246, BASEPALETTE + 10, 10 * sizeof(PALETTEENTRY));

      ppdev->DefaultPalette = pDevInfo->hpalDefault =
         EngCreatePalette(PAL_INDEXED, 256, (PULONG)ppdev->PaletteEntries, 0, 0, 0);
    }

    return ppdev->DefaultPalette != NULL;
}