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
struct TYPE_13__ {size_t i_current_subtitle; size_t i_subtitles; TYPE_1__* p_subtitles; } ;
typedef  TYPE_2__ vobsub_track_t ;
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_14__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_15__ {int i_tracks; scalar_t__ i_next_demux_date; int /*<<< orphan*/  p_vobsub_stream; TYPE_2__* track; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_16__ {int i_buffer; scalar_t__ i_pts; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_12__ {scalar_t__ i_start; int i_vobsub_location; } ;

/* Variables and functions */
 int /*<<< orphan*/  DemuxVobSub (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ VLC_TICK_0 ; 
 int /*<<< orphan*/  block_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*,int) ; 
 TYPE_5__* vlc_stream_Block (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    vlc_tick_t i_maxdate;

    for( int i = 0; i < p_sys->i_tracks; i++ )
    {
        vobsub_track_t *tk = &p_sys->track[i];

        if( tk->i_current_subtitle >= tk->i_subtitles )
            continue;

        i_maxdate = p_sys->i_next_demux_date;
        if( i_maxdate <= 0 && tk->i_current_subtitle < tk->i_subtitles )
        {
            /* Should not happen */
            i_maxdate = tk->p_subtitles[tk->i_current_subtitle].i_start + 1;
        }

        while( tk->i_current_subtitle < tk->i_subtitles &&
               tk->p_subtitles[tk->i_current_subtitle].i_start < i_maxdate )
        {
            int i_pos = tk->p_subtitles[tk->i_current_subtitle].i_vobsub_location;
            block_t *p_block;
            int i_size = 0;

            /* first compute SPU size */
            if( tk->i_current_subtitle + 1 < tk->i_subtitles )
            {
                i_size = tk->p_subtitles[tk->i_current_subtitle+1].i_vobsub_location - i_pos;
            }
            if( i_size <= 0 ) i_size = 65535;   /* Invalid or EOF */

            /* Seek at the right place */
            if( vlc_stream_Seek( p_sys->p_vobsub_stream, i_pos ) )
            {
                msg_Warn( p_demux,
                          "cannot seek in the VobSub to the correct time %d", i_pos );
                tk->i_current_subtitle++;
                continue;
            }

            /* read data */
            p_block = vlc_stream_Block( p_sys->p_vobsub_stream, i_size );
            if( p_block )
            {
                if( p_block->i_buffer > 6 )
                {
                    /* pts */
                    p_block->i_pts = VLC_TICK_0 + tk->p_subtitles[tk->i_current_subtitle].i_start;

                    /* demux this block */
                    DemuxVobSub( p_demux, p_block );
                }
                block_Release( p_block );
            }

            tk->i_current_subtitle++;
        }
    }

    /* */
    p_sys->i_next_demux_date = 0;

    return 1;
}