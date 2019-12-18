#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_10__ {TYPE_4__** track; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_11__ {TYPE_6__* p_fmt; scalar_t__ p_es; } ;
typedef  TYPE_4__ asf_track_t ;
struct TYPE_12__ {TYPE_2__* p_demux; } ;
typedef  TYPE_5__ asf_packet_sys_t ;
struct TYPE_8__ {size_t i_sar_num; size_t i_sar_den; } ;
struct TYPE_13__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_SET_ES_FMT ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_6__*) ; 

__attribute__((used)) static void Packet_SetAR( asf_packet_sys_t *p_packetsys, uint8_t i_stream_number,
                          uint8_t i_ratio_x, uint8_t i_ratio_y )
{
    demux_t *p_demux = p_packetsys->p_demux;
    demux_sys_t *p_sys = p_demux->p_sys;
    asf_track_t *tk = p_sys->track[i_stream_number];

    if ( !tk->p_fmt || (tk->p_fmt->video.i_sar_num == i_ratio_x && tk->p_fmt->video.i_sar_den == i_ratio_y ) )
        return;

    tk->p_fmt->video.i_sar_num = i_ratio_x;
    tk->p_fmt->video.i_sar_den = i_ratio_y;
    if( tk->p_es )
        es_out_Control( p_demux->out, ES_OUT_SET_ES_FMT, tk->p_es, tk->p_fmt );
}