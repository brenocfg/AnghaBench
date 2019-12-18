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
typedef  int uint8_t ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static inline void XDeint8x8FieldC( uint8_t *dst, int i_dst,
                                    uint8_t *src, int i_src )
{
    int y, x;

    /* Interlaced */
    for( y = 0; y < 8; y += 2 )
    {
        memcpy( dst, src, 8 );
        dst += i_dst;

        for( x = 0; x < 8; x++ )
        {
            uint8_t *src2 = &src[2*i_src];
            /* I use 8 pixels just to match the MMX version, but it's overkill
             * 5 would be enough (less isn't good) */
            const int c0 = abs(src[x-4]-src2[x-2]) + abs(src[x-3]-src2[x-1]) +
                           abs(src[x-2]-src2[x+0]) + abs(src[x-1]-src2[x+1]) +
                           abs(src[x+0]-src2[x+2]) + abs(src[x+1]-src2[x+3]) +
                           abs(src[x+2]-src2[x+4]) + abs(src[x+3]-src2[x+5]);

            const int c1 = abs(src[x-3]-src2[x-3]) + abs(src[x-2]-src2[x-2]) +
                           abs(src[x-1]-src2[x-1]) + abs(src[x+0]-src2[x+0]) +
                           abs(src[x+1]-src2[x+1]) + abs(src[x+2]-src2[x+2]) +
                           abs(src[x+3]-src2[x+3]) + abs(src[x+4]-src2[x+4]);

            const int c2 = abs(src[x-2]-src2[x-4]) + abs(src[x-1]-src2[x-3]) +
                           abs(src[x+0]-src2[x-2]) + abs(src[x+1]-src2[x-1]) +
                           abs(src[x+2]-src2[x+0]) + abs(src[x+3]-src2[x+1]) +
                           abs(src[x+4]-src2[x+2]) + abs(src[x+5]-src2[x+3]);

            if( c0 < c1 && c1 <= c2 )
                dst[x] = (src[x-1] + src2[x+1]) >> 1;
            else if( c2 < c1 && c1 <= c0 )
                dst[x] = (src[x+1] + src2[x-1]) >> 1;
            else
                dst[x] = (src[x+0] + src2[x+0]) >> 1;
        }

        dst += 1*i_dst;
        src += 2*i_src;
    }
}