#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_sendtime; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_7__ {TYPE_1__* p_demux; } ;
typedef  TYPE_3__ asf_packet_sys_t ;

/* Variables and functions */

__attribute__((used)) static void Packet_SetSendTime( asf_packet_sys_t *p_packetsys, vlc_tick_t i_time )
{
    demux_t *p_demux = p_packetsys->p_demux;
    demux_sys_t *p_sys = p_demux->p_sys;

    p_sys->i_sendtime = i_time;
}