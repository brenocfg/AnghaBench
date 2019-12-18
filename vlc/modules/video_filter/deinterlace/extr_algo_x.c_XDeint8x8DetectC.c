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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ ssd (scalar_t__) ; 

__attribute__((used)) static inline int XDeint8x8DetectC( uint8_t *src, int i_src )
{
    int y, x;
    int ff, fr;
    int fc;

    /* Detect interlacing */
    fc = 0;
    for( y = 0; y < 7; y += 2 )
    {
        ff = fr = 0;
        for( x = 0; x < 8; x++ )
        {
            fr += ssd(src[      x] - src[1*i_src+x]) +
                  ssd(src[i_src+x] - src[2*i_src+x]);
            ff += ssd(src[      x] - src[2*i_src+x]) +
                  ssd(src[i_src+x] - src[3*i_src+x]);
        }
        if( ff < 6*fr/8 && fr > 32 )
            fc++;

        src += 2*i_src;
    }

    return fc < 1 ? false : true;
}