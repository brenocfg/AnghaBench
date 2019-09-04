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
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;

/* Variables and functions */
 int* PreCalcReverseByte ; 
 int SCREEN_X ; 
 int SCREEN_Y ; 
 int* UnpackPixel ; 
 int* bit8 ; 
 int* endmasks ; 
 int* maskbit ; 
 int* startmasks ; 
 int* xconv ; 
 int* y80 ; 

VOID vgaPreCalc()
{
    ULONG j;

    startmasks[0] = 255;
    startmasks[1] = 1;
    startmasks[2] = 3;
    startmasks[3] = 7;
    startmasks[4] = 15;
    startmasks[5] = 31;
    startmasks[6] = 63;
    startmasks[7] = 127;

    endmasks[0] = 0;
    endmasks[1] = 128;
    endmasks[2] = 192;
    endmasks[3] = 224;
    endmasks[4] = 240;
    endmasks[5] = 248;
    endmasks[6] = 252;
    endmasks[7] = 254;

    for (j = 0; j < 80; j++)
    {
        maskbit[j*8]   = 128;
        maskbit[j*8+1] = 64;
        maskbit[j*8+2] = 32;
        maskbit[j*8+3] = 16;
        maskbit[j*8+4] = 8;
        maskbit[j*8+5] = 4;
        maskbit[j*8+6] = 2;
        maskbit[j*8+7] = 1;

        bit8[j*8]   = 7;
        bit8[j*8+1] = 6;
        bit8[j*8+2] = 5;
        bit8[j*8+3] = 4;
        bit8[j*8+4] = 3;
        bit8[j*8+5] = 2;
        bit8[j*8+6] = 1;
        bit8[j*8+7] = 0;
    }
    for (j = 0; j < SCREEN_Y; j++)
        y80[j]  = j*80;
    for (j = 0; j < SCREEN_X; j++)
        xconv[j] = j >> 3;

    for (j = 0; j < 256; j++)
    {
        PreCalcReverseByte[j] =
            (((j >> 0) & 0x1) << 7) |
            (((j >> 1) & 0x1) << 6) |
            (((j >> 2) & 0x1) << 5) |
            (((j >> 3) & 0x1) << 4) |
            (((j >> 4) & 0x1) << 3) |
            (((j >> 5) & 0x1) << 2) |
            (((j >> 6) & 0x1) << 1) |
            (((j >> 7) & 0x1) << 0);
    }

    for (j = 0; j < 256; j++)
    {
        UnpackPixel[j] =
            (((j >> 0) & 0x1) << 4) |
            (((j >> 1) & 0x1) << 0) |
            (((j >> 2) & 0x1) << 12) |
            (((j >> 3) & 0x1) << 8) |
            (((j >> 4) & 0x1) << 20) |
            (((j >> 5) & 0x1) << 16) |
            (((j >> 6) & 0x1) << 28) |
            (((j >> 7) & 0x1) << 24);
    }
}