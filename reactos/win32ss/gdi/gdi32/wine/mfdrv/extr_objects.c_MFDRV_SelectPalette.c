#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_5__ {int palNumEntries; int /*<<< orphan*/  palPalEntry; int /*<<< orphan*/  palVersion; } ;
typedef  TYPE_1__* PLOGPALETTE ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  PALETTEENTRY ;
typedef  int /*<<< orphan*/  LOGPALETTE ;
typedef  int /*<<< orphan*/  HPALETTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetObjectA (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  GetPaletteEntries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ MFDRV_CreatePalette (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  PALVERSION ; 

HPALETTE MFDRV_SelectPalette( PHYSDEV dev, HPALETTE hPalette, BOOL bForceBackground )
{
#define PALVERSION 0x0300

    PLOGPALETTE logPalette;
    WORD        wNumEntries = 0;
    BOOL        creationSucceed;
    int         sizeofPalette;

    GetObjectA(hPalette, sizeof(WORD), &wNumEntries);

    if (wNumEntries == 0) return 0;

    sizeofPalette = sizeof(LOGPALETTE) + ((wNumEntries-1) * sizeof(PALETTEENTRY));
    logPalette = HeapAlloc( GetProcessHeap(), 0, sizeofPalette );

    if (logPalette == NULL) return 0;

    logPalette->palVersion = PALVERSION;
    logPalette->palNumEntries = wNumEntries;

    GetPaletteEntries(hPalette, 0, wNumEntries, logPalette->palPalEntry);

    creationSucceed = MFDRV_CreatePalette( dev, hPalette, logPalette, sizeofPalette );

    HeapFree( GetProcessHeap(), 0, logPalette );

    if (creationSucceed)
        return hPalette;

    return 0;
}