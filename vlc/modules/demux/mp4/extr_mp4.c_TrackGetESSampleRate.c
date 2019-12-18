#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {int i_sample_count; size_t i_chunk_count; int i_timescale; TYPE_2__ const* chunk; int /*<<< orphan*/  i_track_ID; } ;
typedef  TYPE_1__ mp4_track_t ;
struct TYPE_9__ {unsigned int i_sample_description_index; int i_duration; scalar_t__ i_sample_count; } ;
typedef  TYPE_2__ const mp4_chunk_t ;
struct TYPE_10__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_11__ {int /*<<< orphan*/ * p_root; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_12__ {scalar_t__ i_duration; scalar_t__ i_timescale; } ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 TYPE_7__* BOXDATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MP4_BoxGet (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * MP4_GetTrakByTrackID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT16_MAX ; 
 int /*<<< orphan*/  vlc_ureduce (unsigned int*,unsigned int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void TrackGetESSampleRate( demux_t *p_demux,
                                  unsigned *pi_num, unsigned *pi_den,
                                  const mp4_track_t *p_track,
                                  unsigned i_sd_index,
                                  unsigned i_chunk )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    *pi_num = 0;
    *pi_den = 0;

    MP4_Box_t *p_trak = MP4_GetTrakByTrackID( MP4_BoxGet( p_sys->p_root,
                                                          "/moov" ),
                                              p_track->i_track_ID );
    MP4_Box_t *p_mdhd = MP4_BoxGet( p_trak, "mdia/mdhd" );
    if ( p_mdhd && BOXDATA(p_mdhd) )
    {
        vlc_ureduce( pi_num, pi_den,
                     (uint64_t) BOXDATA(p_mdhd)->i_timescale * p_track->i_sample_count,
                     (uint64_t) BOXDATA(p_mdhd)->i_duration,
                     UINT16_MAX );
        return;
    }

    if( p_track->i_chunk_count == 0 )
        return;

    /* */
    const mp4_chunk_t *p_chunk = &p_track->chunk[i_chunk];
    while( p_chunk > &p_track->chunk[0] &&
           p_chunk[-1].i_sample_description_index == i_sd_index )
    {
        p_chunk--;
    }

    uint64_t i_sample = 0;
    uint64_t i_total_duration = 0;
    do
    {
        i_sample += p_chunk->i_sample_count;
        i_total_duration += p_chunk->i_duration;
        p_chunk++;
    }
    while( p_chunk < &p_track->chunk[p_track->i_chunk_count] &&
           p_chunk->i_sample_description_index == i_sd_index );

    if( i_sample > 0 && i_total_duration )
        vlc_ureduce( pi_num, pi_den,
                     i_sample * p_track->i_timescale,
                     i_total_duration,
                     UINT16_MAX);
}