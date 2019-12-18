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
struct TYPE_5__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int i_data_peeked; int i_frame_size_estimate; int /*<<< orphan*/  p_peek; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool Peek( demux_t *p_demux, bool b_first )
{
    int i_data;
    demux_sys_t *p_sys = p_demux->p_sys;

    if( b_first )
    {
        p_sys->i_data_peeked = 0;
    }
    else if( p_sys->i_data_peeked == p_sys->i_frame_size_estimate )
    {
        p_sys->i_frame_size_estimate += 5120;
    }
    i_data = vlc_stream_Peek( p_demux->s, &p_sys->p_peek,
                          p_sys->i_frame_size_estimate );
    if( i_data == p_sys->i_data_peeked )
    {
        msg_Warn( p_demux, "no more data" );
        return false;
    }
    p_sys->i_data_peeked = i_data;
    if( i_data <= 0 )
    {
        msg_Warn( p_demux, "cannot peek data" );
        return false;
    }
    return true;
}