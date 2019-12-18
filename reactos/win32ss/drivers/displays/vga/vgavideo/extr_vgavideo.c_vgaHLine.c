#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int LONG ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ GRA_D ; 
 scalar_t__ GRA_I ; 
 int /*<<< orphan*/  READ_REGISTER_UCHAR (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_REGISTER_UCHAR (int,int /*<<< orphan*/ ) ; 
 int* endmasks ; 
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,int) ; 
 int mod8 (int) ; 
 int* startmasks ; 
 int vidmem ; 
 int* xconv ; 
 int* y80 ; 

BOOL vgaHLine(INT x, INT y, INT len, UCHAR c)
{
    ULONG orgx, pre1, midpre1;
    //ULONG orgpre1;
    LONG ileftpix, imidpix, irightpix;

    orgx = x;

    /*if ( len < 8 )
    {
        for (i = x; i < x+len; i++ )
            vgaPutPixel ( i, y, c );

        return TRUE;
    }*/

    /* Calculate the left mask pixels, middle bytes and right mask pixel */
    ileftpix = 7 - mod8(x-1);
    irightpix = mod8(x+len);
    imidpix = (len-ileftpix-irightpix) / 8;

    pre1 = xconv[(x-1)&~7] + y80[y];
    //orgpre1=pre1;

    /* check for overlap ( very short line ) */
    if ( (ileftpix+irightpix) > len )
    {
        int mask = startmasks[ileftpix] & endmasks[irightpix];
        /* Write left pixels */
        WRITE_PORT_UCHAR((PUCHAR)GRA_I,0x08);     // set the mask
        WRITE_PORT_UCHAR((PUCHAR)GRA_D,mask);

        READ_REGISTER_UCHAR(vidmem + pre1);
        WRITE_REGISTER_UCHAR(vidmem + pre1, c);

        return TRUE;
    }

    /* Left */
    if ( ileftpix > 0 )
    {
        /* Write left pixels */
        WRITE_PORT_UCHAR((PUCHAR)GRA_I,0x08);     // set the mask
        WRITE_PORT_UCHAR((PUCHAR)GRA_D,startmasks[ileftpix]);

        READ_REGISTER_UCHAR(vidmem + pre1);
        WRITE_REGISTER_UCHAR(vidmem + pre1, c);

        /* Prepare new x for the middle */
        x = orgx + 8;
    }

    if ( imidpix > 0 )
    {
        midpre1 = xconv[x] + y80[y];

        /* Set mask to all pixels in byte */
        WRITE_PORT_UCHAR((PUCHAR)GRA_I, 0x08);
        WRITE_PORT_UCHAR((PUCHAR)GRA_D, 0xff);
        memset(vidmem+midpre1, c, imidpix); // write middle pixels, no need to read in latch because of the width
    }

    if ( irightpix > 0 )
    {
        x = orgx + len - irightpix;
        pre1 = xconv[x] + y80[y];

        /* Write right pixels */
        WRITE_PORT_UCHAR((PUCHAR)GRA_I,0x08);     // set the mask bits
        WRITE_PORT_UCHAR((PUCHAR)GRA_D, endmasks[irightpix]);
        READ_REGISTER_UCHAR(vidmem + pre1);
        WRITE_REGISTER_UCHAR(vidmem + pre1, c);
    }

    return TRUE;
}