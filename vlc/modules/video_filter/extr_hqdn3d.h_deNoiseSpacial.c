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
 unsigned int LowPassMul (unsigned int,unsigned int,int*) ; 

__attribute__((used)) static void deNoiseSpacial(
                    unsigned char *Frame,        // mpi->planes[x]
                    unsigned char *FrameDest,    // dmpi->planes[x]
                    unsigned int *LineAnt,       // vf->priv->Line (width bytes)
                    int W, int H, int sStride, int dStride,
                    int *Horizontal, int *Vertical)
{
    long sLineOffs = 0, dLineOffs = 0;
    unsigned int PixelAnt;
    unsigned int PixelDst;

    /* First pixel has no left nor top neighbor. */
    PixelDst = LineAnt[0] = PixelAnt = Frame[0]<<16;
    FrameDest[0]= ((PixelDst+0x10007FFF)>>16);

    /* First line has no top neighbor, only left. */
    for (long X = 1; X < W; X++){
        PixelDst = LineAnt[X] = LowPassMul(PixelAnt, Frame[X]<<16, Horizontal);
        FrameDest[X]= ((PixelDst+0x10007FFF)>>16);
    }

    for (long Y = 1; Y < H; Y++){
        sLineOffs += sStride, dLineOffs += dStride;
        /* First pixel on each line doesn't have previous pixel */
        PixelAnt = Frame[sLineOffs]<<16;
        PixelDst = LineAnt[0] = LowPassMul(LineAnt[0], PixelAnt, Vertical);
        FrameDest[dLineOffs]= ((PixelDst+0x10007FFF)>>16);

        for (long X = 1; X < W; X++){
            /* The rest are normal */
            PixelAnt = LowPassMul(PixelAnt, Frame[sLineOffs+X]<<16, Horizontal);
            PixelDst = LineAnt[X] = LowPassMul(LineAnt[X], PixelAnt, Vertical);
            FrameDest[dLineOffs+X]= ((PixelDst+0x10007FFF)>>16);
        }
    }
}