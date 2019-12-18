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
struct TYPE_7__ {int /*<<< orphan*/  b_old; } ;
struct TYPE_8__ {TYPE_2__ dirac; } ;
struct TYPE_6__ {int i_codec; } ;
struct TYPE_9__ {int i_granule_shift; TYPE_3__ special; TYPE_1__ fmt; scalar_t__ b_oggds; } ;
typedef  TYPE_4__ logical_stream_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  VLC_CODEC_DAALA 130 
#define  VLC_CODEC_DIRAC 129 
#define  VLC_CODEC_THEORA 128 

int64_t Ogg_GetKeyframeGranule( const logical_stream_t *p_stream, int64_t i_granule )
{
    if ( p_stream->b_oggds )
    {
           return -1; /* We have no way to know */
    }
    else switch( p_stream->fmt.i_codec )
    {
        case VLC_CODEC_THEORA:
        case VLC_CODEC_DAALA:
            return ( i_granule >> p_stream->i_granule_shift ) << p_stream->i_granule_shift;
        case VLC_CODEC_DIRAC:
            if( p_stream->special.dirac.b_old )
                return ( i_granule >> 30 ) << 30;
            else
                return ( i_granule >> 31 ) << 31;
        default:
            /* No change, that's keyframe */
            return i_granule;
    }
}