#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ stime_t ;
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_8__ {unsigned int i_tracks; scalar_t__ p_fragsindex; TYPE_1__* track; int /*<<< orphan*/  p_moov; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_9__ {scalar_t__ i_sample_count; scalar_t__ i_duration; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_track_ID; } ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 TYPE_5__* BOXDATA (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * MP4_BoxGet (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ MP4_Fragment_Index_GetTrackDuration (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/ * MP4_GetTrakByTrackID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __MAX (scalar_t__,scalar_t__) ; 

__attribute__((used)) static stime_t GetCumulatedDuration( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    stime_t i_max_duration = 0;

    for ( unsigned int i=0; i<p_sys->i_tracks; i++ )
    {
        stime_t i_track_duration = 0;
        MP4_Box_t *p_trak = MP4_GetTrakByTrackID( p_sys->p_moov, p_sys->track[i].i_track_ID );
        const MP4_Box_t *p_stsz;
        const MP4_Box_t *p_tkhd;
        if ( (p_tkhd = MP4_BoxGet( p_trak, "tkhd" )) &&
             (p_stsz = MP4_BoxGet( p_trak, "mdia/minf/stbl/stsz" )) &&
             /* duration might be wrong an be set to whole duration :/ */
             BOXDATA(p_stsz)->i_sample_count > 0 )
        {
            i_max_duration = __MAX( (uint64_t)i_max_duration, BOXDATA(p_tkhd)->i_duration );
        }

        if( p_sys->p_fragsindex )
        {
            i_track_duration += MP4_Fragment_Index_GetTrackDuration( p_sys->p_fragsindex, i );
        }

        i_max_duration = __MAX( i_max_duration, i_track_duration );
    }

    return i_max_duration;
}