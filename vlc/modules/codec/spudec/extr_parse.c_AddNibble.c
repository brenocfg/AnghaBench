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

__attribute__((used)) static inline unsigned int AddNibble( unsigned int i_code,
                                      const uint8_t *p_src, unsigned int *pi_index )
{
    if( *pi_index & 0x1 )
    {
        return( i_code << 4 | ( p_src[(*pi_index)++ >> 1] & 0xf ) );
    }
    else
    {
        return( i_code << 4 | p_src[(*pi_index)++ >> 1] >> 4 );
    }
}