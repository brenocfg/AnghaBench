#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* packet; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_2__ ogg_packet ;
struct TYPE_7__ {int i_sar_num; int i_sar_den; int i_frame_rate; int i_frame_rate_base; void* i_height; void* i_visible_height; void* i_width; void* i_visible_width; } ;
struct TYPE_10__ {TYPE_1__ video; } ;
struct TYPE_9__ {int i_granule_shift; TYPE_6__ fmt; int /*<<< orphan*/  dts; } ;
typedef  TYPE_3__ logical_stream_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int GetDWBE (int*) ; 
 void* GetWBE (int*) ; 
 int /*<<< orphan*/  Ogg_ExtractMeta (int /*<<< orphan*/ *,TYPE_6__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static bool Ogg_ReadVP8Header( demux_t *p_demux, logical_stream_t *p_stream,
                               ogg_packet *p_oggpacket )
{
    switch( p_oggpacket->packet[5] )
    {
    /* STREAMINFO */
    case 0x01:
        /* Mapping version */
        if ( p_oggpacket->packet[6] != 0x01 || p_oggpacket->packet[7] != 0x00 )
            return false;
        p_stream->i_granule_shift = 32;
        p_stream->fmt.video.i_width = GetWBE( &p_oggpacket->packet[8] );
        p_stream->fmt.video.i_height = GetWBE( &p_oggpacket->packet[10] );
        p_stream->fmt.video.i_visible_width = p_stream->fmt.video.i_width;
        p_stream->fmt.video.i_visible_height = p_stream->fmt.video.i_height;
        p_stream->fmt.video.i_sar_num = GetDWBE( &p_oggpacket->packet[12 - 1] ) & 0x0FFF;
        p_stream->fmt.video.i_sar_den = GetDWBE( &p_oggpacket->packet[15 - 1] ) & 0x0FFF;
        p_stream->fmt.video.i_frame_rate = GetDWBE( &p_oggpacket->packet[18] );
        p_stream->fmt.video.i_frame_rate_base = GetDWBE( &p_oggpacket->packet[22] );
        if ( !p_stream->fmt.video.i_frame_rate || !p_stream->fmt.video.i_frame_rate_base )
            return false;
        date_Init( &p_stream->dts, p_stream->fmt.video.i_frame_rate,
                                   p_stream->fmt.video.i_frame_rate_base );
        return true;
    /* METADATA */
    case 0x02:
        Ogg_ExtractMeta( p_demux, & p_stream->fmt,
                         p_oggpacket->packet + 7, p_oggpacket->bytes - 7 );
        return true;
    default:
        return false;
    }
}