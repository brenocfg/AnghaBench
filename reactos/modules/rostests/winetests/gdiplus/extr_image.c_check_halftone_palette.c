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
typedef  int UINT ;
struct TYPE_3__ {int Count; int* Entries; } ;
typedef  TYPE_1__ ColorPalette ;
typedef  int BYTE ;
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,int,int,int,int) ; 

__attribute__((used)) static void check_halftone_palette(ColorPalette *palette)
{
    static const BYTE halftone_values[6]={0x00,0x33,0x66,0x99,0xcc,0xff};
    UINT i;

    for (i=0; i<palette->Count; i++)
    {
        ARGB expected=0xff000000;
        if (i<8)
        {
            if (i&1) expected |= 0x800000;
            if (i&2) expected |= 0x8000;
            if (i&4) expected |= 0x80;
        }
        else if (i == 8)
        {
            expected = 0xffc0c0c0;
        }
        else if (i < 16)
        {
            if (i&1) expected |= 0xff0000;
            if (i&2) expected |= 0xff00;
            if (i&4) expected |= 0xff;
        }
        else if (i < 40)
        {
            expected = 0x00000000;
        }
        else
        {
            expected |= halftone_values[(i-40)%6];
            expected |= halftone_values[((i-40)/6)%6] << 8;
            expected |= halftone_values[((i-40)/36)%6] << 16;
        }
        ok(expected == palette->Entries[i], "Expected %.8x, got %.8x, i=%u/%u\n",
            expected, palette->Entries[i], i, palette->Count);
    }
}