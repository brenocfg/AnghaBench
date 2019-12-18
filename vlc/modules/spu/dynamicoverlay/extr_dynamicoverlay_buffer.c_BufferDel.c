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
struct TYPE_3__ {scalar_t__ i_length; int p_begin; int p_memory; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 

int BufferDel( buffer_t *p_buffer, int i_len )
{
    p_buffer->i_length -= i_len;
    if( p_buffer->i_length == 0 )
    {
        /* No data, we can reset the buffer now. */
        p_buffer->p_begin = p_buffer->p_memory;
    }
    else
    {
        p_buffer->p_begin += i_len;
    }
    return VLC_SUCCESS;
}