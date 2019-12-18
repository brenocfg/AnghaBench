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
typedef  int /*<<< orphan*/  sout_mux_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_fifo; } ;
typedef  TYPE_1__ sout_input_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_FifoEmpty (int /*<<< orphan*/ ) ; 

void sout_MuxFlush( sout_mux_t *p_mux, sout_input_t *p_input )
{
    VLC_UNUSED(p_mux);
    block_FifoEmpty( p_input->p_fifo );
}