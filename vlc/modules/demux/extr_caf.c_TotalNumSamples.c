#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_12__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_11__ {int i_num_valid_frames; int i_num_priming_frames; int i_num_remainder_frames; } ;
struct TYPE_9__ {int i_frame_length; } ;
struct TYPE_10__ {TYPE_1__ audio; } ;
struct TYPE_13__ {TYPE_3__ packet_table; TYPE_2__ fmt; } ;
typedef  TYPE_5__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  NeedsPacketTable (TYPE_5__*) ; 
 int TotalNumFrames (TYPE_4__*) ; 

__attribute__((used)) static uint64_t TotalNumSamples( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if( !NeedsPacketTable( p_sys ))
    {
        return TotalNumFrames( p_demux ) * p_sys->fmt.audio.i_frame_length;
    }
    else
    {
        return p_sys->packet_table.i_num_valid_frames + p_sys->packet_table.i_num_priming_frames +
                p_sys->packet_table.i_num_remainder_frames;
    }
}