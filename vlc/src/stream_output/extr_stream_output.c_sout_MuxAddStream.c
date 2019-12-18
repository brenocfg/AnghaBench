#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ (* pf_addstream ) (TYPE_1__*,TYPE_2__*) ;int /*<<< orphan*/  pp_inputs; int /*<<< orphan*/  i_nb_inputs; int /*<<< orphan*/  b_waiting_stream; int /*<<< orphan*/  b_add_stream_any_time; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_14__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/  p_fifo; int /*<<< orphan*/ * p_sys; int /*<<< orphan*/ * p_fmt; } ;
typedef  TYPE_2__ sout_input_t ;
typedef  int /*<<< orphan*/  es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TAB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  block_FifoNew () ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 scalar_t__ stub1 (TYPE_1__*,TYPE_2__*) ; 

sout_input_t *sout_MuxAddStream( sout_mux_t *p_mux, const es_format_t *p_fmt )
{
    sout_input_t *p_input;

    if( !p_mux->b_add_stream_any_time && !p_mux->b_waiting_stream )
    {
        msg_Err( p_mux, "cannot add a new stream (unsupported while muxing "
                        "to this format). You can try increasing sout-mux-caching value" );
        return NULL;
    }

    msg_Dbg( p_mux, "adding a new input" );

    /* create a new sout input */
    p_input = malloc( sizeof( sout_input_t ) );
    if( !p_input )
        return NULL;

    // FIXME: remove either fmt or p_fmt...
    es_format_Copy( &p_input->fmt, p_fmt );
    p_input->p_fmt = &p_input->fmt;

    p_input->p_fifo = block_FifoNew();
    p_input->p_sys  = NULL;

    TAB_APPEND( p_mux->i_nb_inputs, p_mux->pp_inputs, p_input );
    if( p_mux->pf_addstream( p_mux, p_input ) < 0 )
    {
        msg_Err( p_mux, "cannot add this stream" );
        TAB_REMOVE( p_mux->i_nb_inputs, p_mux->pp_inputs, p_input );
        block_FifoRelease( p_input->p_fifo );
        es_format_Clean( &p_input->fmt );
        free( p_input );
        return NULL;
    }

    return p_input;
}