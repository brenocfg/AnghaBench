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
typedef  size_t uint8_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {TYPE_3__** track; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_8__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_3__ asf_track_t ;
typedef  int /*<<< orphan*/  asf_track_info_t ;
struct TYPE_9__ {TYPE_1__* p_demux; } ;
typedef  TYPE_4__ asf_packet_sys_t ;

/* Variables and functions */

__attribute__((used)) static asf_track_info_t * Packet_GetTrackInfo( asf_packet_sys_t *p_packetsys,
                                               uint8_t i_stream_number )
{
    demux_t *p_demux = p_packetsys->p_demux;
    demux_sys_t *p_sys = p_demux->p_sys;
    asf_track_t *tk = p_sys->track[i_stream_number];

    if (!tk)
        return NULL;
    else
        return & tk->info;
}