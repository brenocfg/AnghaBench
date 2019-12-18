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
struct TYPE_3__ {scalar_t__ pPal; scalar_t__ hpalDefault; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PPDEV ;
typedef  scalar_t__ PPALETTEENTRY ;
typedef  scalar_t__ HPALETTE ;

/* Variables and functions */
 int /*<<< orphan*/  EngDeletePalette (scalar_t__) ; 
 int /*<<< orphan*/  EngFreeMem (int /*<<< orphan*/ ) ; 

VOID vDisablePalette(PPDEV ppdev)
{
// Delete the default palette if we created one.

    if (ppdev->hpalDefault)
    {
        EngDeletePalette(ppdev->hpalDefault);
        ppdev->hpalDefault = (HPALETTE) 0;
    }

// eVb: 4.2 [VGARISC Change] - VGA Palette is static, no need to free
#if 0
    if (ppdev->pPal != (PPALETTEENTRY)NULL)
        EngFreeMem((PVOID)ppdev->pPal);
#endif
// eVb: 4.2 [END]
}