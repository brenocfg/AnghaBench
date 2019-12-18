#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int msftime_t ;
struct TYPE_11__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_12__ {int i_seek_track; int i_wait_keyframe; scalar_t__ b_canfastseek; TYPE_6__** track; } ;
typedef  TYPE_5__ demux_sys_t ;
struct TYPE_10__ {TYPE_2__* p_esp; TYPE_1__* p_sp; } ;
struct TYPE_13__ {scalar_t__ i_cat; TYPE_3__ info; scalar_t__ b_selected; } ;
typedef  TYPE_6__ asf_track_t ;
struct TYPE_9__ {int i_average_time_per_frame; } ;
struct TYPE_8__ {int i_stream_number; } ;

/* Variables and functions */
 int MAX_ASF_TRACKS ; 
 int MSFTIME_FROM_SEC (int) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 scalar_t__ VIDEO_ES ; 
 int __MIN (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void WaitKeyframe( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    if ( ! p_sys->i_seek_track )
    {
        for ( int i=0; i<MAX_ASF_TRACKS; i++ )
        {
            asf_track_t *tk = p_sys->track[i];
            if ( tk && tk->info.p_sp && tk->i_cat == VIDEO_ES && tk->b_selected )
            {
                p_sys->i_seek_track = tk->info.p_sp->i_stream_number;
                break;
            }
        }
    }

    if ( p_sys->i_seek_track )
    {
        /* Skip forward at least 1 min */
        asf_track_t *tk = p_sys->track[p_sys->i_seek_track];
        if ( tk->info.p_esp && tk->info.p_esp->i_average_time_per_frame )
        {
            /* 1 min if fastseek, otherwise 5 sec */
            /* That's a guess for bandwidth */
            msftime_t i_maxwaittime = MSFTIME_FROM_SEC( p_sys->b_canfastseek ? 60 : 5);
            uint64_t frames = i_maxwaittime / tk->info.p_esp->i_average_time_per_frame;
            p_sys->i_wait_keyframe = __MIN( frames, UINT_MAX );
        }
        else
        {
            p_sys->i_wait_keyframe = ( p_sys->b_canfastseek ) ? 25 * 30 : 25 * 5;
        }
    }
    else
    {
        p_sys->i_wait_keyframe = 0;
    }

}