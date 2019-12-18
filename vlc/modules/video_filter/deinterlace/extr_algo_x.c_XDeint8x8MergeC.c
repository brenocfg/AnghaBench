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
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static inline void XDeint8x8MergeC( uint8_t *dst,  int i_dst,
                                    uint8_t *src1, int i_src1,
                                    uint8_t *src2, int i_src2 )
{
    int y, x;

    /* Progressive */
    for( y = 0; y < 8; y += 2 )
    {
        memcpy( dst, src1, 8 );
        dst  += i_dst;

        for( x = 0; x < 8; x++ )
            dst[x] = (src1[x] + 6*src2[x] + src1[i_src1+x] + 4 ) >> 3;
        dst += i_dst;

        src1 += i_src1;
        src2 += i_src2;
    }
}