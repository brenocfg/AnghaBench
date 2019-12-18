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
struct TYPE_3__ {int i_buffer_size; int /*<<< orphan*/ * pf_window_table; } ;
typedef  TYPE_1__ window_context ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

void window_scale_in_place( int16_t * p_buffer, window_context * p_ctx )
{
    for( int i = 0; i < p_ctx->i_buffer_size; i++ )
    {
        p_buffer[i] *= p_ctx->pf_window_table[i];
    }
}