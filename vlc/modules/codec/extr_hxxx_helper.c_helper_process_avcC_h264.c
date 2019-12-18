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
struct hxxx_helper {int dummy; } ;

/* Variables and functions */
 size_t H264_MIN_AVCC_SIZE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int h264_helper_parse_nal (struct hxxx_helper*,int const*,size_t,int,int*) ; 

__attribute__((used)) static int
helper_process_avcC_h264(struct hxxx_helper *hh, const uint8_t *p_buf,
                         size_t i_buf)
{
    if (i_buf < H264_MIN_AVCC_SIZE)
        return VLC_EGENERIC;

    p_buf += 5; i_buf -= 5;

    for (unsigned int j = 0; j < 2 && i_buf > 0; j++)
    {
        /* First time is SPS, Second is PPS */
        const unsigned int i_num_nal = p_buf[0] & (j == 0 ? 0x1f : 0xff);
        p_buf++; i_buf--;

        for (unsigned int i = 0; i < i_num_nal && i_buf >= 2; i++)
        {
            uint16_t i_nal_size = (p_buf[0] << 8) | p_buf[1];
            if (i_nal_size > i_buf - 2)
                return VLC_EGENERIC;
            bool b_unused;
            int i_ret = h264_helper_parse_nal(hh, p_buf, i_nal_size + 2, 2,
                                              &b_unused);
            if (i_ret != VLC_SUCCESS)
                return i_ret;
            p_buf += i_nal_size + 2;
            i_buf -= i_nal_size + 2;
        }
    }

    return VLC_SUCCESS;
}