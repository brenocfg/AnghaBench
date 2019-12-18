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
 size_t HEVC_MIN_HVCC_SIZE ; 

__attribute__((used)) static inline bool hevc_ishvcC( const uint8_t *p_buf, size_t i_buf )
{
    return ( i_buf >= HEVC_MIN_HVCC_SIZE &&
             p_buf[0] != 0x00
/*          /!\Broken quicktime streams does not respect reserved bits
            (p_buf[13] & 0xF0) == 0xF0 && // Match all reserved bits
            (p_buf[15] & 0xFC) == 0xFC &&
            (p_buf[16] & 0xFC) == 0xFC &&
            (p_buf[17] & 0xF8) == 0xF8 &&
            (p_buf[18] & 0xF8) == 0xF8 &&
            (p_buf[21] & 0x03) != 0x02 */
           );
}