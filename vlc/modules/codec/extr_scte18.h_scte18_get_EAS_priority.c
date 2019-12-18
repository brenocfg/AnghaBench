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

__attribute__((used)) static inline int scte18_get_EAS_priority( const uint8_t *p_buffer, size_t i_buffer )
{
    if( i_buffer < 17 || p_buffer[0] )
        return -1;

    size_t i_offset = 6;
    size_t i_len = p_buffer[i_offset]; /* EAS code Len */
    i_offset += i_len + 1; /* EAS code Text */
    if( i_offset >= i_buffer )
        return -1;

    i_len = p_buffer[i_offset]; /* NOA Len */
    i_offset += i_len + 1; /* NOA Text */

    i_offset += 1 + 4 + 2 + 1;

    if( i_offset >= i_buffer )
        return -1;

    return (p_buffer[i_offset] & 0x0f);
}