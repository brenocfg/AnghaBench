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
typedef  int* PUCHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ mod2 (int) ; 
 int /*<<< orphan*/  vgaPutPixel (int,int,int) ; 

void DIB_TransparentBltToVGA(int x, int y, int w, int h, void *b, int Source_lDelta, ULONG trans)

{
    PUCHAR pb = b, opb = b;
    BOOLEAN edgePixel = FALSE;
    ULONG i, j;
    ULONG x2 = x + w;
    ULONG y2 = y + h;
    UCHAR b1, b2;

    /* Check if the width is odd */
    if(mod2(w) > 0)
    {
        edgePixel = TRUE;
        x2 -= 1;
    }

    for (j=y; j<y2; j++)
    {
        for (i=x; i<x2; i+=2)
        {
            b1 = (*pb & 0xf0) >> 4;
            b2 = *pb & 0x0f;
            if(b1 != trans) vgaPutPixel(i,   j, b1);
            if(b2 != trans) vgaPutPixel(i+1, j, b2);
            pb++;
        }

        if (edgePixel)
        {
            b1 = *pb;
            if(b1 != trans) vgaPutPixel(x2, j, b1);
            pb++;
        }

        opb += Source_lDelta;
        pb = opb; // new test code
    }
}