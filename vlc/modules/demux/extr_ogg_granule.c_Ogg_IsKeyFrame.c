#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ bytes; int* packet; int granulepos; } ;
typedef  TYPE_4__ ogg_packet ;
struct TYPE_9__ {int /*<<< orphan*/  b_old; } ;
struct TYPE_10__ {TYPE_2__ dirac; } ;
struct TYPE_8__ {int i_codec; } ;
struct TYPE_12__ {TYPE_3__ special; TYPE_1__ fmt; scalar_t__ b_oggds; } ;
typedef  TYPE_5__ logical_stream_t ;

/* Variables and functions */
 int PACKET_IS_SYNCPOINT ; 
 int THEORA_FTYPE_INTERFRAME ; 
 int THEORA_FTYPE_NOTDATA ; 
#define  VLC_CODEC_DAALA 131 
#define  VLC_CODEC_DIRAC 130 
#define  VLC_CODEC_THEORA 129 
#define  VLC_CODEC_VP8 128 

bool Ogg_IsKeyFrame( const logical_stream_t *p_stream, const ogg_packet *p_packet )
{
    if ( p_stream->b_oggds )
    {
        return ( p_packet->bytes > 0 && p_packet->packet[0] & PACKET_IS_SYNCPOINT );
    }
    else switch ( p_stream->fmt.i_codec )
    {
        case VLC_CODEC_THEORA:
        case VLC_CODEC_DAALA: /* Same convention used in daala */
            if ( p_packet->bytes <= 0 || p_packet->packet[0] & THEORA_FTYPE_NOTDATA )
                return false;
            else
                return !( p_packet->packet[0] & THEORA_FTYPE_INTERFRAME );
        case VLC_CODEC_VP8:
            return ( ( ( p_packet->granulepos >> 3 ) & 0x07FFFFFF ) == 0 );
        case VLC_CODEC_DIRAC:
            if( p_stream->special.dirac.b_old )
                return (p_packet->granulepos & 0x3FFFFFFF) == 0;
            else
                return (p_packet->granulepos & 0xFF8000FF) == 0;
        default:
            return true;
    }
}