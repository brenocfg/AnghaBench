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
struct TYPE_3__ {scalar_t__ i_data; scalar_t__ i_size; scalar_t__ p_data; } ;
typedef  TYPE_1__ var_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int) ; 
 scalar_t__ xrealloc (scalar_t__,scalar_t__) ; 

void var_buffer_addmemory( var_buffer_t *p_buf, void *p_mem, int i_mem )
{
    /* check if there is enough data */
    if( p_buf->i_data + i_mem >= p_buf->i_size )
    {
        p_buf->i_size += i_mem + 1024;
        p_buf->p_data = xrealloc( p_buf->p_data, p_buf->i_size );
    }

    memcpy( p_buf->p_data + p_buf->i_data, p_mem, i_mem );
    p_buf->i_data += i_mem;
}