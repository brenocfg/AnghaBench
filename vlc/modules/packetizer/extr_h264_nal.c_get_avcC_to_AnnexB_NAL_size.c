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
typedef  size_t uint16_t ;

/* Variables and functions */
 size_t H264_MIN_AVCC_SIZE ; 

__attribute__((used)) static size_t get_avcC_to_AnnexB_NAL_size( const uint8_t *p_buf, size_t i_buf )
{
    size_t i_total = 0;

    if( i_buf < H264_MIN_AVCC_SIZE )
        return 0;

    p_buf += 5;
    i_buf -= 5;

    for ( unsigned int j = 0; j < 2; j++ )
    {
        /* First time is SPS, Second is PPS */
        const unsigned int i_loop_end = p_buf[0] & (j == 0 ? 0x1f : 0xff);
        p_buf++; i_buf--;

        for ( unsigned int i = 0; i < i_loop_end; i++ )
        {
            if( i_buf < 2 )
                return 0;

            uint16_t i_nal_size = (p_buf[0] << 8) | p_buf[1];
            if(i_nal_size > i_buf - 2)
                return 0;
            i_total += i_nal_size + 4;
            p_buf += i_nal_size + 2;
            i_buf -= i_nal_size + 2;
        }

        if( j == 0 && i_buf < 1 )
            return 0;
    }
    return i_total;
}