#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int vlc_tick_t ;
struct TYPE_13__ {scalar_t__ i_cat; } ;
struct TYPE_14__ {int i_data_start; int /*<<< orphan*/  os; TYPE_1__ fmt; } ;
typedef  TYPE_2__ logical_stream_t ;
typedef  int int64_t ;
struct TYPE_15__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_16__ {int i_streams; int i_bitrate; int i_total_length; int i_input_position; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int INT64_C (int) ; 
 int OggBisectSearchByTime (TYPE_3__*,TYPE_2__*,int,int,int) ; 
 scalar_t__ OggSeekIndexFind (TYPE_2__*,int,int*,int*) ; 
 int /*<<< orphan*/  Ogg_GetBoundsUsingSkeletonIndex (TYPE_2__*,int,int*,int*) ; 
 int Ogg_GetKeyframeGranule (TYPE_2__*,int) ; 
 int VLC_TICK_0 ; 
 int /*<<< orphan*/  ogg_stream_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seek_byte (TYPE_3__*,int) ; 

int Oggseek_BlindSeektoAbsoluteTime( demux_t *p_demux, logical_stream_t *p_stream,
                                     vlc_tick_t i_time, bool b_fastseek )
{
    demux_sys_t *p_sys  = p_demux->p_sys;
    int64_t i_lowerpos = -1;
    int64_t i_upperpos = -1;
    bool b_found = false;

    /* Search in skeleton */
    Ogg_GetBoundsUsingSkeletonIndex( p_stream, i_time, &i_lowerpos, &i_upperpos );
    if ( i_lowerpos != -1 ) b_found = true;

    /* And also search in our own index */
    if ( !b_found && OggSeekIndexFind( p_stream, i_time, &i_lowerpos, &i_upperpos ) )
    {
        b_found = true;
    }

    /* Or try to be smart with audio fixed bitrate streams */
    if ( !b_found && p_stream->fmt.i_cat == AUDIO_ES && p_sys->i_streams == 1
         && p_sys->i_bitrate && Ogg_GetKeyframeGranule( p_stream, 0xFF00FF00 ) == 0xFF00FF00 )
    {
        /* But only if there's no keyframe/preload requirements */
        /* FIXME: add function to get preload time by codec, ex: opus */
        i_lowerpos = VLC_TICK_0 + (i_time - VLC_TICK_0) * p_sys->i_bitrate / INT64_C(8000000);
        b_found = true;
    }

    /* or search */
    if ( !b_found && b_fastseek )
    {
        i_lowerpos = OggBisectSearchByTime( p_demux, p_stream, i_time,
                                            p_stream->i_data_start, p_sys->i_total_length );
        b_found = ( i_lowerpos != -1 );
    }

    if ( !b_found ) return -1;

    if ( i_lowerpos < p_stream->i_data_start || i_upperpos > p_sys->i_total_length )
        return -1;

    /* And really do seek */
    p_sys->i_input_position = i_lowerpos;
    seek_byte( p_demux, p_sys->i_input_position );
    ogg_stream_reset( &p_stream->os );

    return i_lowerpos;
}