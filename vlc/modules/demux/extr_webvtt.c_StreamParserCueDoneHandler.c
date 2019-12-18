#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ i_start; scalar_t__ i_stop; scalar_t__ psz_text; } ;
typedef  TYPE_1__ webvtt_cue_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_13__ {int b_first_time; scalar_t__ i_next_demux_time; int /*<<< orphan*/  es; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_14__ {scalar_t__ i_dts; scalar_t__ i_pts; scalar_t__ i_length; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 TYPE_4__* ConvertWEBVTT (TYPE_1__*,int) ; 
 scalar_t__ VLC_TICK_0 ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  webvtt_cue_Clean (TYPE_1__*) ; 

__attribute__((used)) static void StreamParserCueDoneHandler( void *priv, webvtt_cue_t *p_cue )
{
    demux_t *p_demux = (demux_t *) priv;
    demux_sys_t *p_sys = p_demux->p_sys;

    if( p_cue->psz_text )
    {
        block_t *p_block = ConvertWEBVTT( p_cue, true );
        if( p_block )
        {
            if ( p_sys->b_first_time )
            {
                es_out_SetPCR( p_demux->out, p_cue->i_start + VLC_TICK_0 );
                p_sys->b_first_time = false;
            }
            p_sys->i_next_demux_time = p_cue->i_start;
            p_block->i_dts =
                    p_block->i_pts = VLC_TICK_0 + p_cue->i_start;
            if( p_cue->i_stop >= 0 && p_cue->i_stop >= p_cue->i_start )
                p_block->i_length = p_cue->i_stop - p_cue->i_start;
            es_out_Send( p_demux->out, p_sys->es, p_block );
            es_out_SetPCR( p_demux->out, p_cue->i_start + VLC_TICK_0 );
        }
    }
    webvtt_cue_Clean( p_cue );
    free( p_cue );
}