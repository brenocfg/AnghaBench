#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int* p_data; size_t i_data; int i_mask; } ;
typedef  TYPE_1__ bits_buffer_t ;

/* Variables and functions */

__attribute__((used)) static inline void bits_write( bits_buffer_t *p_buffer,
                               int i_count, uint64_t i_bits )
{
    while( i_count > 0 )
    {
        i_count--;

        if( ( i_bits >> i_count )&0x01 )
        {
            p_buffer->p_data[p_buffer->i_data] |= p_buffer->i_mask;
        }
        else
        {
            p_buffer->p_data[p_buffer->i_data] &= ~p_buffer->i_mask;
        }
        p_buffer->i_mask >>= 1;
        if( p_buffer->i_mask == 0 )
        {
            p_buffer->i_data++;
            p_buffer->i_mask = 0x80;
        }
    }
}