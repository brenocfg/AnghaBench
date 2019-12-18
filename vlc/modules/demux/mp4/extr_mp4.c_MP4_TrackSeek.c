#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int b_selected; int /*<<< orphan*/  i_track_ID; int /*<<< orphan*/  b_ok; } ;
typedef  TYPE_1__ mp4_track_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 scalar_t__ MP4_isMetadata (TYPE_1__*) ; 
 int /*<<< orphan*/  TrackGotoChunkSample (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TrackTimeToSampleChunk (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int MP4_TrackSeek( demux_t *p_demux, mp4_track_t *p_track,
                          vlc_tick_t i_start )
{
    uint32_t i_chunk;
    uint32_t i_sample;

    if( !p_track->b_ok || MP4_isMetadata( p_track ) )
        return VLC_EGENERIC;

    p_track->b_selected = false;

    if( TrackTimeToSampleChunk( p_demux, p_track, i_start,
                                &i_chunk, &i_sample ) )
    {
        msg_Warn( p_demux, "cannot select track[Id 0x%x]",
                  p_track->i_track_ID );
        return VLC_EGENERIC;
    }

    p_track->b_selected = true;
    if( !TrackGotoChunkSample( p_demux, p_track, i_chunk, i_sample ) )
        p_track->b_selected = true;

    return p_track->b_selected ? VLC_SUCCESS : VLC_EGENERIC;
}