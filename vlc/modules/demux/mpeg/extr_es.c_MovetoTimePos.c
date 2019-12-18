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
typedef  scalar_t__ vlc_tick_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  s; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_5__ {scalar_t__ i_current; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_demux_flags; TYPE_1__ chapters; int /*<<< orphan*/ * p_packetized_data; scalar_t__ i_pts; scalar_t__ i_time_offset; scalar_t__ i_stream_offset; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_UPDATE_SEEKPOINT ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int vlc_stream_Seek (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int MovetoTimePos( demux_t *p_demux, vlc_tick_t i_time, uint64_t i_pos )
{
    demux_sys_t *p_sys  = p_demux->p_sys;
    int i_ret = vlc_stream_Seek( p_demux->s, p_sys->i_stream_offset + i_pos );
    if( i_ret != VLC_SUCCESS )
        return i_ret;
    p_sys->i_time_offset = i_time - p_sys->i_pts;
    /* And reset buffered data */
    if( p_sys->p_packetized_data )
        block_ChainRelease( p_sys->p_packetized_data );
    p_sys->p_packetized_data = NULL;
    p_sys->chapters.i_current = 0;
    p_sys->i_demux_flags |= INPUT_UPDATE_SEEKPOINT;
    return VLC_SUCCESS;
}