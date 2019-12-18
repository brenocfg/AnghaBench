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
 size_t H264_MIN_AVCC_SIZE ; 

bool h264_isavcC( const uint8_t *p_buf, size_t i_buf )
{
    return ( i_buf >= H264_MIN_AVCC_SIZE &&
             p_buf[0] != 0x00 &&
             p_buf[1] != 0x00
/*          /!\Broken quicktime streams does not respect reserved bits
            (p_buf[4] & 0xFC) == 0xFC &&
            (p_buf[4] & 0x03) != 0x02 &&
            (p_buf[5] & 0x1F) > 0x00 */
            );
}