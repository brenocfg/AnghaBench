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
typedef  int /*<<< orphan*/  va_list ;
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int /*<<< orphan*/  pts; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int CDG_FRAME_RATE ; 
 int CDG_FRAME_SIZE ; 
 int DEMUX_SET_POSITION ; 
 int DEMUX_SET_TIME ; 
 int /*<<< orphan*/  PosToDate (TYPE_1__*) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int demux_vaControlHelper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int vlc_stream_Seek (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Control( demux_t *p_demux, int i_query, va_list args )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    uint64_t i_old_offset = vlc_stream_Tell( p_demux->s );
    int i_ret = demux_vaControlHelper( p_demux->s, 0, -1,
                                       8*CDG_FRAME_SIZE*CDG_FRAME_RATE, CDG_FRAME_SIZE,
                                       i_query, args );
    if( !i_ret && ( i_query == DEMUX_SET_POSITION || i_query == DEMUX_SET_TIME ) )
    {
        date_Set( &p_sys->pts, PosToDate( p_demux ) );
        if ( i_old_offset > vlc_stream_Tell( p_demux->s ) )
            i_ret = vlc_stream_Seek( p_demux->s, 0 );
        else
            i_ret = vlc_stream_Seek( p_demux->s, i_old_offset );
    }

    return i_ret;
}