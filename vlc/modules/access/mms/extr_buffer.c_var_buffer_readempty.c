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
struct TYPE_3__ {scalar_t__ i_data; scalar_t__ i_size; } ;
typedef  TYPE_1__ var_buffer_t ;

/* Variables and functions */

int var_buffer_readempty( var_buffer_t *p_buf )
{
    return( ( p_buf->i_data >= p_buf->i_size ) ? 1 : 0 );
}