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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {int /*<<< orphan*/  s; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_10__ {scalar_t__ i_num_packets; } ;
struct TYPE_8__ {scalar_t__ i_bytes_per_frame; } ;
struct TYPE_9__ {TYPE_1__ audio; } ;
struct TYPE_12__ {scalar_t__ i_data_size; scalar_t__ i_data_offset; TYPE_3__ packet_table; TYPE_2__ fmt; } ;
typedef  TYPE_5__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  NeedsPacketTable (TYPE_5__*) ; 
 scalar_t__ kCHUNK_SIZE_EOF ; 
 scalar_t__ stream_Size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t TotalNumFrames( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if( !NeedsPacketTable( p_sys ))
    {
        uint64_t i_data_size;

        if( p_sys->i_data_size != kCHUNK_SIZE_EOF)
        {
            i_data_size = p_sys->i_data_size;
        }
        else
        {
            int64_t i_stream_size = stream_Size( p_demux->s );
            if(i_stream_size >= 0 && (uint64_t)i_stream_size >= p_sys->i_data_offset)
                i_data_size = i_stream_size - p_sys->i_data_offset;
            else
                i_data_size = 0;
        }

        return i_data_size / p_sys->fmt.audio.i_bytes_per_frame;
    }
    else
    {
        return p_sys->packet_table.i_num_packets;
    }
}