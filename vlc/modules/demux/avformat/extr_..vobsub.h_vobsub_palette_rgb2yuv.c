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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ __MIN (int,int) ; 
 int abs (int) ; 

__attribute__((used)) static inline void vobsub_palette_rgb2yuv( const uint32_t *src, uint32_t *dst )
{
    int i;
    for( i = 0; i < 16; i++ )
    {
        uint8_t r, g, b, y, u, v;
        r = (src[i] >> 16) & 0xff;
        g = (src[i] >> 8) & 0xff;
        b = (src[i] >> 0) & 0xff;
        y = (uint8_t) __MIN(abs(r * 2104 + g * 4130 + b * 802 + 4096 + 131072) >> 13, 235);
        u = (uint8_t) __MIN(abs(r * -1214 + g * -2384 + b * 3598 + 4096 + 1048576) >> 13, 240);
        v = (uint8_t) __MIN(abs(r * 3598 + g * -3013 + b * -585 + 4096 + 1048576) >> 13, 240);
        dst[i] = (y&0xff)<<16 | (v&0xff)<<8 | (u&0xff);
    }
}