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
struct TYPE_3__ {int i_mask; size_t i_data; size_t i_size; int* p_data; } ;
typedef  TYPE_1__ bits_buffer_t ;

/* Variables and functions */

__attribute__((used)) static inline void bits_align( bits_buffer_t *p_buffer )
{
    if( p_buffer->i_mask != 0x80 && p_buffer->i_data < p_buffer->i_size )
    {
        p_buffer->i_mask = 0x80;
        p_buffer->i_data++;
        p_buffer->p_data[p_buffer->i_data] = 0x00;
    }
}