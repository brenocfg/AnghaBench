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
struct TYPE_3__ {scalar_t__ i_buffer_size; int /*<<< orphan*/ * pf_window_table; } ;
typedef  TYPE_1__ window_context ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void window_close( window_context * p_ctx )
{
    if( p_ctx->pf_window_table )
    {
        free( p_ctx->pf_window_table );
        p_ctx->pf_window_table = NULL;
        p_ctx->i_buffer_size = 0;
    }
}