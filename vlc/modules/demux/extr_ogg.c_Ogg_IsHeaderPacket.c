#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bytes; int* packet; scalar_t__ granulepos; } ;
typedef  TYPE_1__ ogg_packet ;
struct TYPE_6__ {scalar_t__ i_first_frame_index; scalar_t__ b_oggds; } ;
typedef  TYPE_2__ logical_stream_t ;

/* Variables and functions */
 int PACKET_TYPE_HEADER ; 

__attribute__((used)) static bool Ogg_IsHeaderPacket( const logical_stream_t *p_stream,
                                const ogg_packet *p_oggpacket )
{
    if ( p_stream->b_oggds )
    {
        return p_oggpacket->bytes > 0 &&
               (p_oggpacket->packet[0] & PACKET_TYPE_HEADER);
    }
    else return ( p_oggpacket->granulepos == 0 && p_stream->i_first_frame_index > 0 );
}