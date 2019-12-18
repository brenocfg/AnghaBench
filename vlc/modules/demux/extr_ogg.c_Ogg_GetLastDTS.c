#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_5__ {scalar_t__ i_pcr; scalar_t__ b_initializing; } ;
typedef  TYPE_1__ logical_stream_t ;
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_7__ {int i_streams; TYPE_1__** pp_stream; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 

__attribute__((used)) static vlc_tick_t Ogg_GetLastDTS( demux_t * p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    vlc_tick_t i_dts = VLC_TICK_INVALID;
    for( int i_stream = 0; i_stream < p_sys->i_streams; i_stream++ )
    {
        logical_stream_t *p_stream = p_sys->pp_stream[i_stream];
        if ( p_stream->b_initializing )
            continue;
        if( p_stream->i_pcr > i_dts )
            i_dts = p_stream->i_pcr;
    }

    return i_dts;
}