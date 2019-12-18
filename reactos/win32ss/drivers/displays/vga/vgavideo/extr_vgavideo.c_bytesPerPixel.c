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
typedef  int UCHAR ;

/* Variables and functions */
#define  BMF_16BPP 135 
#define  BMF_1BPP 134 
#define  BMF_24BPP 133 
#define  BMF_32BPP 132 
#define  BMF_4BPP 131 
#define  BMF_4RLE 130 
#define  BMF_8BPP 129 
#define  BMF_8RLE 128 

UCHAR bytesPerPixel(ULONG Format)
{
    /* This function is taken from /subsys/win32k/eng/surface.c
     * FIXME: GDI bitmaps are supposed to be pixel-packed. Right now if the
     * pixel size if < 1 byte we expand it to 1 byte for simplicities sake */

    switch (Format)
    {
        case BMF_1BPP:
            return 1;

        case BMF_4BPP:
        case BMF_4RLE:
            return 1;

        case BMF_8BPP:
        case BMF_8RLE:
            return 1;

        case BMF_16BPP:
            return 2;

        case BMF_24BPP:
            return 3;

        case BMF_32BPP:
            return 4;

        default:
            return 0;
    }
}