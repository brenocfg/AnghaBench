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
typedef  int /*<<< orphan*/  XLATEOBJ ;
typedef  size_t ULONG ;
typedef  int* PUCHAR ;

/* Variables and functions */
 scalar_t__ GRA_D ; 
 scalar_t__ GRA_I ; 
 int /*<<< orphan*/  READ_REGISTER_UCHAR (size_t) ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (int*,int) ; 
 int /*<<< orphan*/  WRITE_REGISTER_UCHAR (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLATEOBJ_iXlate (int /*<<< orphan*/ *,int) ; 
 int* maskbit ; 
 size_t vidmem ; 
 size_t* xconv ; 
 size_t* y80 ; 

void DIB_BltToVGAWithXlate(int x, int y, int w, int h, void *b, int Source_lDelta, XLATEOBJ* Xlate)
{
    PUCHAR pb, opb = b;
    ULONG i, j;
    ULONG x2 = x + w;
    ULONG y2 = y + h;
    ULONG offset;

    for (i = x; i < x2; i++)
    {
        pb = opb;
        offset = xconv[i] + y80[y];

        WRITE_PORT_UCHAR((PUCHAR)GRA_I, 0x08);       // set the mask
        WRITE_PORT_UCHAR((PUCHAR)GRA_D, maskbit[i]);

        if (0 == ((i - x) % 2))
        {
            for (j = y; j < y2; j++)
            {
                READ_REGISTER_UCHAR(vidmem + offset);
                WRITE_REGISTER_UCHAR(vidmem + offset, XLATEOBJ_iXlate(Xlate, (*pb & 0xf0) >> 4));
                offset += 80;
                pb += Source_lDelta;
            }
        }
        else
        {
            for (j = y; j < y2; j++)
            {
                READ_REGISTER_UCHAR(vidmem + offset);
                WRITE_REGISTER_UCHAR(vidmem + offset, XLATEOBJ_iXlate(Xlate, *pb & 0x0f));
                offset += 80;
                pb += Source_lDelta;
            }
        }

        if (0 != ((i - x) % 2))
            opb++;
    }
}