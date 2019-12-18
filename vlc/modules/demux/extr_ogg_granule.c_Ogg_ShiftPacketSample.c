#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int i_framesize; int i_framesperpacket; } ;
struct TYPE_7__ {scalar_t__ b_interlaced; } ;
struct TYPE_10__ {TYPE_3__ speex; TYPE_1__ dirac; } ;
struct TYPE_8__ {scalar_t__ i_cat; scalar_t__ i_codec; } ;
struct TYPE_11__ {TYPE_4__ special; TYPE_2__ fmt; scalar_t__ b_oggds; } ;
typedef  TYPE_5__ logical_stream_t ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ VIDEO_ES ; 
 scalar_t__ VLC_CODEC_DIRAC ; 
 scalar_t__ VLC_CODEC_SPEEX ; 

__attribute__((used)) static int64_t Ogg_ShiftPacketSample( const logical_stream_t *p_stream,
                                      int64_t i_sample, bool b_start )
{
    /* /!\ Packet Granule as sample value ! */

    /* granule always point to end time of packet
       Except with OggDS where it is reversed */
    int64_t i_endtostartoffset = 0; /* in interval # */
    if( p_stream->b_oggds )
        i_endtostartoffset = (b_start ? 0 : 1);
    else
        i_endtostartoffset = (b_start ? -1 : 0);

    if( p_stream->fmt.i_cat == VIDEO_ES )
    {
        if( p_stream->fmt.i_codec == VLC_CODEC_DIRAC ) /* points to start */
            i_sample += (p_stream->special.dirac.b_interlaced ? 1 : 2) * (i_endtostartoffset + 1);
        else
            i_sample += i_endtostartoffset * 1;
    }
    else if( p_stream->fmt.i_cat == AUDIO_ES )
    {
        if( p_stream->fmt.i_codec == VLC_CODEC_SPEEX )
        {
            i_sample += i_endtostartoffset *
                        p_stream->special.speex.i_framesize *
                        p_stream->special.speex.i_framesperpacket;
        }
        else /* we can't tell */
        {
            if( i_endtostartoffset != 0 )
                return -1;
        }
    }
    return i_sample;
}