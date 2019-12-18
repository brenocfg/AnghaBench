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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ GRA_D ; 
 scalar_t__ GRA_I ; 
 int /*<<< orphan*/  READ_REGISTER_UCHAR (size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_REGISTER_UCHAR (size_t,int /*<<< orphan*/ ) ; 
 int* maskbit ; 
 int /*<<< orphan*/  vgaSetBitMaskRegister (int) ; 
 size_t vidmem ; 
 size_t* xconv ; 
 size_t* y80 ; 

BOOL vgaVLine(INT x, INT y, INT len, UCHAR c)
{
    INT offset, i;

    offset = xconv[x]+y80[y];

#ifdef VGA_PERF
    vgaSetBitMaskRegister ( maskbit[x] );
#else
    WRITE_PORT_UCHAR((PUCHAR)GRA_I,0x08);       // set the mask
    WRITE_PORT_UCHAR((PUCHAR)GRA_D,maskbit[x]);
#endif

    for(i=y; i<y+len; i++)
    {
        READ_REGISTER_UCHAR(vidmem + offset);
        WRITE_REGISTER_UCHAR(vidmem + offset, c);
        offset += 80;
    }

    return TRUE;
}