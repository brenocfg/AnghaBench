#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  p_access; TYPE_4__** pp_inputs; int /*<<< orphan*/  i_nb_inputs; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ sout_mux_t ;
struct TYPE_14__ {int b_header; int /*<<< orphan*/  pi_chan_table; int /*<<< orphan*/  i_chans_to_reorder; int /*<<< orphan*/  i_data; } ;
typedef  TYPE_3__ sout_mux_sys_t ;
struct TYPE_15__ {TYPE_1__* p_fmt; int /*<<< orphan*/  p_fifo; } ;
typedef  TYPE_4__ sout_input_t ;
struct TYPE_16__ {scalar_t__ i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_codec; } ;

/* Variables and functions */
 TYPE_5__* GetHeader (TYPE_2__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  aout_ChannelReorder (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ block_FifoCount (int /*<<< orphan*/ ) ; 
 TYPE_5__* block_FifoGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sout_AccessOutWrite (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int Mux( sout_mux_t *p_mux )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;
    sout_input_t *p_input;

    if( !p_mux->i_nb_inputs ) return VLC_SUCCESS;

    if( p_sys->b_header )
    {
        msg_Dbg( p_mux, "writing header data" );
        sout_AccessOutWrite( p_mux->p_access, GetHeader( p_mux ) );
    }
    p_sys->b_header = false;

    p_input = p_mux->pp_inputs[0];
    while( block_FifoCount( p_input->p_fifo ) > 0 )
    {
        block_t *p_block = block_FifoGet( p_input->p_fifo );
        p_sys->i_data += p_block->i_buffer;

        /* Do the channel reordering */
        if( p_sys->i_chans_to_reorder )
            aout_ChannelReorder( p_block->p_buffer, p_block->i_buffer,
                                 p_sys->i_chans_to_reorder,
                                 p_sys->pi_chan_table, p_input->p_fmt->i_codec );

        sout_AccessOutWrite( p_mux->p_access, p_block );
    }

    return VLC_SUCCESS;
}