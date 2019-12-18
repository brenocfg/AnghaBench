#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int b_waiting_stream; scalar_t__ i_nb_inputs; int /*<<< orphan*/  (* pf_delstream ) (TYPE_1__*,TYPE_2__*) ;int /*<<< orphan*/  pp_inputs; int /*<<< orphan*/  (* pf_mux ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_12__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/  p_fifo; } ;
typedef  TYPE_2__ sout_input_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_ERASE (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TAB_FIND (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ block_FifoCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,TYPE_2__*) ; 

void sout_MuxDeleteStream( sout_mux_t *p_mux, sout_input_t *p_input )
{
    int i_index;

    if( p_mux->b_waiting_stream
     && block_FifoCount( p_input->p_fifo ) > 0 )
    {
        /* We stop waiting, and call the muxer for taking care of the data
         * before we remove this es */
        p_mux->b_waiting_stream = false;
        p_mux->pf_mux( p_mux );
    }

    TAB_FIND( p_mux->i_nb_inputs, p_mux->pp_inputs, p_input, i_index );
    if( i_index >= 0 )
    {
        /* remove the entry */
        TAB_ERASE( p_mux->i_nb_inputs, p_mux->pp_inputs, i_index );

        p_mux->pf_delstream( p_mux, p_input );

        if( p_mux->i_nb_inputs == 0 )
        {
            msg_Warn( p_mux, "no more input streams for this mux" );
        }

        block_FifoRelease( p_input->p_fifo );
        es_format_Clean( &p_input->fmt );
        free( p_input );
    }
}