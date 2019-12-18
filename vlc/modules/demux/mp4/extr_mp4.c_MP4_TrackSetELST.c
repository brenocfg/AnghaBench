#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {int i_elst; scalar_t__ i_elst_time; int /*<<< orphan*/  i_next_block_flags; TYPE_4__* (* BOXDATA ) (int /*<<< orphan*/ ) ;scalar_t__ p_elst; } ;
typedef  TYPE_1__ mp4_track_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_timescale; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_13__ {scalar_t__ i_entry_count; scalar_t__* i_segment_duration; scalar_t__* i_media_time; } ;
typedef  TYPE_4__ MP4_Box_data_elst_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 scalar_t__ MP4_rescale_qtime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  p_elst ; 
 TYPE_4__* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_4__* stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MP4_TrackSetELST( demux_t *p_demux, mp4_track_t *tk,
                              vlc_tick_t i_time )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int         i_elst_last = tk->i_elst;

    /* handle elst (find the correct one) */
    tk->i_elst      = 0;
    tk->i_elst_time = 0;
    if( tk->p_elst && tk->BOXDATA(p_elst)->i_entry_count > 0 )
    {
        MP4_Box_data_elst_t *elst = tk->BOXDATA(p_elst);
        int64_t i_mvt= MP4_rescale_qtime( i_time, p_sys->i_timescale );

        for( tk->i_elst = 0; (unsigned int)tk->i_elst < elst->i_entry_count; tk->i_elst++ )
        {
            uint64_t i_dur = elst->i_segment_duration[tk->i_elst];

            if( tk->i_elst_time <= i_mvt
             && i_mvt < (int64_t)(tk->i_elst_time + i_dur) )
            {
                break;
            }
            tk->i_elst_time += i_dur;
        }

        if( (unsigned int)tk->i_elst >= elst->i_entry_count )
        {
            /* msg_Dbg( p_demux, "invalid number of entry in elst" ); */
            tk->i_elst = elst->i_entry_count - 1;
            tk->i_elst_time -= elst->i_segment_duration[tk->i_elst];
        }

        if( elst->i_media_time[tk->i_elst] < 0 )
        {
            /* track offset */
            tk->i_elst_time += elst->i_segment_duration[tk->i_elst];
        }
    }
    if( i_elst_last != tk->i_elst )
    {
        msg_Warn( p_demux, "elst old=%d new=%d", i_elst_last, tk->i_elst );
        tk->i_next_block_flags |= BLOCK_FLAG_DISCONTINUITY;
    }
}