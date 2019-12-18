#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_8__ {int i_nb_inputs; int /*<<< orphan*/  b_add_stream_any_time; TYPE_3__** pp_inputs; } ;
typedef  TYPE_2__ sout_mux_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_fifo; TYPE_1__* p_fmt; } ;
typedef  TYPE_3__ sout_input_t ;
struct TYPE_10__ {scalar_t__ i_dts; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_7__ {scalar_t__ i_cat; } ;

/* Variables and functions */
 scalar_t__ SPU_ES ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int block_FifoCount (int /*<<< orphan*/ ) ; 
 TYPE_4__* block_FifoShow (int /*<<< orphan*/ ) ; 

int sout_MuxGetStream( sout_mux_t *p_mux, unsigned i_blocks, vlc_tick_t *pi_dts )
{
    vlc_tick_t i_dts = 0;
    int     i_stream = -1;

    assert( i_blocks > 0 );

    for( int i = 0; i < p_mux->i_nb_inputs; i++ )
    {
        sout_input_t *p_input = p_mux->pp_inputs[i];
        block_t *p_data;

        if( block_FifoCount( p_input->p_fifo ) < i_blocks )
        {
            if( (!p_mux->b_add_stream_any_time) &&
                (p_input->p_fmt->i_cat != SPU_ES ) )
            {
                return -1;
            }
            /* FIXME: SPU muxing */
            continue;
        }

        p_data = block_FifoShow( p_input->p_fifo );
        if( i_stream < 0 || p_data->i_dts < i_dts )
        {
            i_stream = i;
            i_dts    = p_data->i_dts;
        }
    }

    if( pi_dts ) *pi_dts = i_dts;

    return i_stream;
}