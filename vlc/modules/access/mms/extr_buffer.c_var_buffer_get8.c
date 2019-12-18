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
struct TYPE_3__ {size_t i_data; size_t i_size; int /*<<< orphan*/ * p_data; } ;
typedef  TYPE_1__ var_buffer_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

uint8_t var_buffer_get8 ( var_buffer_t *p_buf )
{
    uint8_t  i_byte;
    if( p_buf->i_data >= p_buf->i_size )
    {
        return( 0 );
    }
    i_byte = p_buf->p_data[p_buf->i_data];
    p_buf->i_data++;
    return( i_byte );
}