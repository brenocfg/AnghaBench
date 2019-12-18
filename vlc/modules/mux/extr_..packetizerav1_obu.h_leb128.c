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
typedef  size_t uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t leb128(const uint8_t *p_buf, size_t i_buf, uint8_t *pi_len)
{
    uint64_t i_val = 0;
    *pi_len = 0;
    for(size_t i=0; i<8; i++)
    {
        if(i >= i_buf)
            break;
        i_val |= ((uint64_t)(p_buf[i] & 0x7F) << (i * 7));
        if((p_buf[i] & 0x80) == 0)
        {
            *pi_len = i + 1;
            break;
        }
    }
    return *pi_len ? i_val : 0;
}