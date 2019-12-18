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

/* Variables and functions */
 unsigned int LowPassMul (unsigned short,unsigned char,int*) ; 

__attribute__((used)) static void deNoiseTemporal(
                    unsigned char *Frame,        // mpi->planes[x]
                    unsigned char *FrameDest,    // dmpi->planes[x]
                    unsigned short *FrameAnt,
                    int W, int H, int sStride, int dStride,
                    int *Temporal)
{
    unsigned int PixelDst;

    for (long Y = 0; Y < H; Y++){
        for (long X = 0; X < W; X++){
            PixelDst = LowPassMul(FrameAnt[X]<<8, Frame[X]<<16, Temporal);
            FrameAnt[X] = ((PixelDst+0x1000007F)>>8);
            FrameDest[X]= ((PixelDst+0x10007FFF)>>16);
        }
        Frame += sStride;
        FrameDest += dStride;
        FrameAnt += W;
    }
}