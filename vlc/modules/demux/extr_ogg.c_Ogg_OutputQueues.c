#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  logical_stream_t ;
struct TYPE_6__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {scalar_t__ i_pcr; int i_streams; int /*<<< orphan*/  b_slave; int /*<<< orphan*/ ** pp_stream; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ Ogg_GeneratePCR (TYPE_1__*,int) ; 
 int Ogg_HasQueuedBlocks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ogg_SendQueuedBlock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void Ogg_OutputQueues( demux_t *p_demux, bool b_drain )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    vlc_tick_t i_pcr;

    /* Generate First PCR */
    if( p_sys->i_pcr == VLC_TICK_INVALID )
    {
        i_pcr = Ogg_GeneratePCR( p_demux, b_drain );
        if( i_pcr != VLC_TICK_INVALID && i_pcr != p_sys->i_pcr )
        {
            p_sys->i_pcr = i_pcr;
            if( likely( !p_sys->b_slave ) )
                es_out_SetPCR( p_demux->out, p_sys->i_pcr );
        }
    }

    if( p_sys->i_pcr != VLC_TICK_INVALID )
    {
        bool b_continue;
        do
        {
            b_continue = false;
            for( int i_stream = 0; i_stream < p_sys->i_streams; i_stream++ )
            {
                logical_stream_t *p_stream = p_sys->pp_stream[i_stream];
                if( Ogg_HasQueuedBlocks( p_stream ) )
                    Ogg_SendQueuedBlock( p_demux, p_stream );
                b_continue |= Ogg_HasQueuedBlocks( p_stream );
            }

            /* Generate Current PCR */
            i_pcr = Ogg_GeneratePCR( p_demux, b_drain );
            if( i_pcr != VLC_TICK_INVALID && i_pcr != p_sys->i_pcr )
            {
                p_sys->i_pcr = i_pcr;
                if( likely( !p_sys->b_slave ) )
                    es_out_SetPCR( p_demux->out, p_sys->i_pcr );
            }
        } while ( b_continue );
    }
}