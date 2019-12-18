#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ogg_int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  b_old; } ;
struct TYPE_7__ {TYPE_1__ dirac; } ;
struct TYPE_8__ {int i_codec; } ;
struct TYPE_9__ {int i_granule_shift; TYPE_2__ special; int /*<<< orphan*/  b_oggds; int /*<<< orphan*/  i_first_frame_index; TYPE_3__ fmt; } ;
typedef  TYPE_4__ logical_stream_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  VLC_CODEC_DAALA 137 
#define  VLC_CODEC_DIRAC 136 
#define  VLC_CODEC_FLAC 135 
#define  VLC_CODEC_KATE 134 
#define  VLC_CODEC_OGGSPOTS 133 
#define  VLC_CODEC_OPUS 132 
#define  VLC_CODEC_SPEEX 131 
#define  VLC_CODEC_THEORA 130 
#define  VLC_CODEC_VORBIS 129 
#define  VLC_CODEC_VP8 128 

__attribute__((used)) static int64_t Ogg_GranuleToSample( const logical_stream_t *p_stream, int64_t i_granule )
{
    switch( p_stream->fmt.i_codec )
    {
        case VLC_CODEC_THEORA:
            if( p_stream->i_first_frame_index == 0 && !p_stream->b_oggds )
                i_granule++;
            /* fallthrough */
        case VLC_CODEC_DAALA:
        case VLC_CODEC_KATE:
        {
            ogg_int64_t iframe = i_granule >> p_stream->i_granule_shift;
            ogg_int64_t pframe = i_granule - ( iframe << p_stream->i_granule_shift );
            return iframe + pframe;
        }
        case VLC_CODEC_VP8:
        case VLC_CODEC_OGGSPOTS:
            return i_granule >> p_stream->i_granule_shift;
        case VLC_CODEC_DIRAC:
            if( p_stream->special.dirac.b_old )
                return (i_granule >> 30) + (i_granule & 0x3FFFFFFF);
            else
                return (i_granule >> 31);
        case VLC_CODEC_OPUS:
        case VLC_CODEC_VORBIS:
        case VLC_CODEC_SPEEX:
        case VLC_CODEC_FLAC:
            return i_granule/* - p_stream->i_pre_skip*/;
        default:
            return i_granule;
    }
}