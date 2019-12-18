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
struct TYPE_5__ {int i_flags; int /*<<< orphan*/  i_pid; } ;
typedef  TYPE_1__ ts_pid_t ;
struct TYPE_6__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  b_access_control; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int FLAG_FILTERED ; 
 int /*<<< orphan*/  STREAM_SET_PRIVATE_ID_STATE ; 
 int VLC_EGENERIC ; 
 int vlc_stream_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int UpdateHWFilter( demux_sys_t *p_sys, ts_pid_t *p_pid )
{
    if( !p_sys->b_access_control )
        return VLC_EGENERIC;

    return vlc_stream_Control( p_sys->stream, STREAM_SET_PRIVATE_ID_STATE,
                           p_pid->i_pid, !!(p_pid->i_flags & FLAG_FILTERED) );
}