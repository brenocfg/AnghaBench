#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ i_bitrate; scalar_t__ i_cat; } ;
struct TYPE_9__ {int b_reinit; int /*<<< orphan*/  i_pcr; TYPE_1__ fmt; int /*<<< orphan*/ * idx; int /*<<< orphan*/ * p_es; } ;
typedef  TYPE_2__ logical_stream_t ;
struct TYPE_10__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_11__ {scalar_t__ i_bitrate; int i_streams; int b_partial_bitrate; scalar_t__ i_total_frames; TYPE_2__** pp_stream; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ Ogg_FindLogicalStreams (TYPE_3__*) ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 

__attribute__((used)) static int Ogg_BeginningOfStream( demux_t *p_demux )
{
    demux_sys_t *p_ogg = p_demux->p_sys  ;
    int i_stream;

    /* Find the logical streams embedded in the physical stream and
     * initialize our p_ogg structure. */
    if( Ogg_FindLogicalStreams( p_demux ) != VLC_SUCCESS )
    {
        msg_Warn( p_demux, "couldn't find any ogg logical stream" );
        return VLC_EGENERIC;
    }

    p_ogg->i_bitrate = 0;

    for( i_stream = 0 ; i_stream < p_ogg->i_streams; i_stream++ )
    {
        logical_stream_t *p_stream = p_ogg->pp_stream[i_stream];

        p_stream->p_es = NULL;

        /* initialise kframe index */
        p_stream->idx=NULL;

        if ( p_stream->fmt.i_bitrate == 0  &&
             ( p_stream->fmt.i_cat == VIDEO_ES ||
               p_stream->fmt.i_cat == AUDIO_ES ) )
            p_ogg->b_partial_bitrate = true;
        else
            p_ogg->i_bitrate += p_stream->fmt.i_bitrate;

        p_stream->i_pcr = VLC_TICK_INVALID;
        p_stream->b_reinit = false;
    }

    /* get total frame count for video stream; we will need this for seeking */
    p_ogg->i_total_frames = 0;

    return VLC_SUCCESS;
}