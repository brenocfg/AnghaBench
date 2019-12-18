#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_timescale; int /*<<< orphan*/  i_cumulated_duration; int /*<<< orphan*/  i_duration; int /*<<< orphan*/  b_fragments_probed; int /*<<< orphan*/  b_seekable; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int FragSeekToTime (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 double MP4_rescale_mtime (scalar_t__,int /*<<< orphan*/ ) ; 
 int ProbeFragmentsChecked (TYPE_1__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ __MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int FragSeekToPos( demux_t *p_demux, double f, bool b_accurate )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if ( !p_sys->b_seekable || !p_sys->i_timescale )
        return VLC_EGENERIC;

    uint64_t i_duration = __MAX(p_sys->i_duration, p_sys->i_cumulated_duration);
    if( !i_duration && !p_sys->b_fragments_probed )
    {
        int i_ret = ProbeFragmentsChecked( p_demux );
        if( i_ret != VLC_SUCCESS )
            return i_ret;
        i_duration = __MAX(p_sys->i_duration, p_sys->i_cumulated_duration);
    }

    if( !i_duration )
        return VLC_EGENERIC;

    return FragSeekToTime( p_demux, (vlc_tick_t)( f *
                           MP4_rescale_mtime( i_duration, p_sys->i_timescale ) ), b_accurate );
}