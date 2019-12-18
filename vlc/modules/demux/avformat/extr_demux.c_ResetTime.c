#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_11__ {scalar_t__ rem; int /*<<< orphan*/  quot; } ;
typedef  TYPE_3__ lldiv_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_13__ {unsigned int i_tracks; TYPE_2__* tracks; scalar_t__ i_pcr; TYPE_1__* ic; } ;
typedef  TYPE_5__ demux_sys_t ;
struct TYPE_10__ {scalar_t__ i_pcr; } ;
struct TYPE_9__ {scalar_t__ start_time; } ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE ; 
 int /*<<< orphan*/  ES_OUT_SET_NEXT_DISPLAY_TIME ; 
 scalar_t__ FROM_AV_TS (scalar_t__) ; 
 int /*<<< orphan*/  UpdateSeekPoint (TYPE_4__*,scalar_t__) ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__ lldiv (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_from_sec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ResetTime( demux_t *p_demux, int64_t i_time )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    vlc_tick_t t;

    if( p_sys->ic->start_time == (int64_t)AV_NOPTS_VALUE || i_time < 0 )
    {
        t = VLC_TICK_INVALID;
    }
    else
    {
#if CLOCK_FREQ == AV_TIME_BASE
        t = FROM_AV_TS(i_time);
#else
        lldiv_t q = lldiv( i_time, AV_TIME_BASE );
        t = vlc_tick_from_sec(q.quot) + FROM_AV_TS(q.rem);
#endif

        if( t == VLC_TICK_INVALID )
            t = VLC_TICK_0;
    }

    p_sys->i_pcr = t;
    for( unsigned i = 0; i < p_sys->i_tracks; i++ )
        p_sys->tracks[i].i_pcr = VLC_TICK_INVALID;

    if( t != VLC_TICK_INVALID )
    {
        es_out_Control( p_demux->out, ES_OUT_SET_NEXT_DISPLAY_TIME, t );
        UpdateSeekPoint( p_demux, t );
    }
}