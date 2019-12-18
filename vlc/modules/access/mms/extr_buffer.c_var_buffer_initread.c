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
struct TYPE_3__ {int i_size; void* p_data; scalar_t__ i_data; } ;
typedef  TYPE_1__ var_buffer_t ;

/* Variables and functions */

void var_buffer_initread( var_buffer_t *p_buf, void *p_data, int i_data )
{
    p_buf->i_size = i_data;
    p_buf->i_data = 0;
    p_buf->p_data = p_data;
}