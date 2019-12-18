#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {size_t i_seek_track; scalar_t__ i_wait_keyframe; TYPE_3__** track; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_es; } ;
typedef  TYPE_3__ asf_track_t ;
struct TYPE_10__ {TYPE_1__* p_demux; } ;
typedef  TYPE_4__ asf_packet_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,size_t) ; 

__attribute__((used)) static bool Packet_DoSkip( asf_packet_sys_t *p_packetsys, uint8_t i_stream_number, bool b_packet_keyframe )
{
    demux_t *p_demux = p_packetsys->p_demux;
    demux_sys_t *p_sys = p_demux->p_sys;
    const asf_track_t *tk = p_sys->track[i_stream_number];

    if( tk == NULL )
    {
        msg_Warn( p_demux, "undeclared stream[Id 0x%x]", i_stream_number );
        return true;
    }

    if( p_sys->i_wait_keyframe )
    {
        if ( i_stream_number == p_sys->i_seek_track )
        {
            if ( !b_packet_keyframe )
            {
                p_sys->i_wait_keyframe--;
                return true;
            }
            else
                p_sys->i_wait_keyframe = 0;
        }
        else
            return true;
    }

    if( !tk->p_es )
        return true;

    return false;
}