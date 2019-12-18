#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* stream; } ;
typedef  TYPE_2__ asf_header_t ;
struct TYPE_4__ {scalar_t__ i_cat; int i_selected; scalar_t__ i_bitrate; } ;

/* Variables and functions */
 scalar_t__ ASF_CODEC_TYPE_AUDIO ; 
 scalar_t__ ASF_CODEC_TYPE_UNKNOWN ; 
 scalar_t__ ASF_CODEC_TYPE_VIDEO ; 

void  asf_StreamSelect  ( asf_header_t *hdr,
                              int i_bitrate_max,
                              bool b_all, bool b_audio, bool b_video )
{
    /* XXX FIXME use mututal eclusion information */
    unsigned i;
    int i_audio, i_video;
    int i_bitrate_total;
#if 0
    char *psz_stream;
#endif

    i_audio = 0;
    i_video = 0;
    i_bitrate_total = 0;
    if( b_all )
    {
        /* select all valid stream */
        for( i = 1; i < 128; i++ )
        {
            if( hdr->stream[i].i_cat != ASF_CODEC_TYPE_UNKNOWN )
            {
                hdr->stream[i].i_selected = 1;
            }
        }
        return;
    }
    else
    {
        for( i = 0; i < 128; i++ )
        {
            /* by default, not selected */
            hdr->stream[i].i_selected = 0;
        }
    }

    /* big test:
     * select a stream if
     *    - no audio nor video stream
     *    - or:
     *         - if i_bitrate_max not set keep the highest bitrate
     *         - if i_bitrate_max is set, keep stream that make we used best
     *           quality regarding i_bitrate_max
     *
     * XXX: little buggy:
     *        - it doesn't use mutual exclusion info..
     *        - when selecting a better stream we could select
     *        something that make i_bitrate_total> i_bitrate_max
     */
    for( i = 1; i < 128; i++ )
    {
        if( hdr->stream[i].i_cat == ASF_CODEC_TYPE_UNKNOWN )
        {
            continue;
        }
        else if( hdr->stream[i].i_cat == ASF_CODEC_TYPE_AUDIO && b_audio &&
                 ( i_audio <= 0 ||
                    ( ( ( hdr->stream[i].i_bitrate > hdr->stream[i_audio].i_bitrate &&
                          ( i_bitrate_total + hdr->stream[i].i_bitrate - hdr->stream[i_audio].i_bitrate
                                            < i_bitrate_max || !i_bitrate_max) ) ||
                        ( hdr->stream[i].i_bitrate < hdr->stream[i_audio].i_bitrate &&
                              i_bitrate_max != 0 && i_bitrate_total > i_bitrate_max )
                      ) )  ) )
        {
            /* unselect old stream */
            if( i_audio > 0 )
            {
                hdr->stream[i_audio].i_selected = 0;
                if( hdr->stream[i_audio].i_bitrate> 0 )
                {
                    i_bitrate_total -= hdr->stream[i_audio].i_bitrate;
                }
            }

            hdr->stream[i].i_selected = 1;
            if( hdr->stream[i].i_bitrate> 0 )
            {
                i_bitrate_total += hdr->stream[i].i_bitrate;
            }
            i_audio = i;
        }
        else if( hdr->stream[i].i_cat == ASF_CODEC_TYPE_VIDEO && b_video &&
                 ( i_video <= 0 ||
                    (
                        ( ( hdr->stream[i].i_bitrate > hdr->stream[i_video].i_bitrate &&
                            ( i_bitrate_total + hdr->stream[i].i_bitrate - hdr->stream[i_video].i_bitrate
                                            < i_bitrate_max || !i_bitrate_max) ) ||
                          ( hdr->stream[i].i_bitrate < hdr->stream[i_video].i_bitrate &&
                            i_bitrate_max != 0 && i_bitrate_total > i_bitrate_max )
                        ) ) )  )
        {
            /* unselect old stream */
            if( i_video > 0 )
            {
                hdr->stream[i_video].i_selected = 0;
                if( hdr->stream[i_video].i_bitrate> 0 )
                {
                    i_bitrate_total -= hdr->stream[i_video].i_bitrate;
                }
            }

            hdr->stream[i].i_selected = 1;
            if( hdr->stream[i].i_bitrate> 0 )
            {
                i_bitrate_total += hdr->stream[i].i_bitrate;
            }
            i_video = i;
        }

    }
}