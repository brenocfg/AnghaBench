#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  rgbBlue; int /*<<< orphan*/  rgbGreen; int /*<<< orphan*/  rgbRed; } ;
struct TYPE_10__ {int /*<<< orphan*/  rgbBlue; int /*<<< orphan*/  rgbGreen; int /*<<< orphan*/  rgbRed; } ;
struct TYPE_9__ {int /*<<< orphan*/  rgbBlue; int /*<<< orphan*/  rgbGreen; int /*<<< orphan*/  rgbRed; } ;
struct TYPE_8__ {int palVersion; int palNumEntries; TYPE_1__* palPalEntry; } ;
struct TYPE_7__ {int /*<<< orphan*/  peFlags; int /*<<< orphan*/  peBlue; int /*<<< orphan*/  peGreen; int /*<<< orphan*/  peRed; } ;
typedef  TYPE_1__ PALETTEENTRY ;
typedef  TYPE_2__ LOGPALETTE ;
typedef  int /*<<< orphan*/  HPALETTE ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePalette (TYPE_2__*) ; 
 TYPE_5__* default_palette_1 ; 
 TYPE_4__* default_palette_4 ; 
 TYPE_3__* default_palette_8 ; 

__attribute__((used)) static HPALETTE create_default_palette( int bpp )
{
    char pal_buffer[sizeof(LOGPALETTE) + 255 * sizeof(PALETTEENTRY)];
    LOGPALETTE *pal = (LOGPALETTE *)pal_buffer;
    PALETTEENTRY *entries = pal->palPalEntry;
    int i;

    pal->palVersion = 0x300;
    pal->palNumEntries = 1 << bpp;
    switch (bpp)
    {
    case 1:
        for (i = 0; i < 2; i++)
        {
            entries[i].peRed   = default_palette_1[i].rgbRed;
            entries[i].peGreen = default_palette_1[i].rgbGreen;
            entries[i].peBlue  = default_palette_1[i].rgbBlue;
            entries[i].peFlags = 0;
        }
        break;
    case 4:
        for (i = 0; i < 16; i++)
        {
            entries[i].peRed   = default_palette_4[i].rgbRed;
            entries[i].peGreen = default_palette_4[i].rgbGreen;
            entries[i].peBlue  = default_palette_4[i].rgbBlue;
            entries[i].peFlags = 0;
        }
        break;
    case 8:
        for (i = 0; i < 256; i++)
        {
            entries[i].peRed   = default_palette_8[i].rgbRed;
            entries[i].peGreen = default_palette_8[i].rgbGreen;
            entries[i].peBlue  = default_palette_8[i].rgbBlue;
            entries[i].peFlags = 0;
        }
        break;
    }
    return CreatePalette( pal );
}