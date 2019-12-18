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
typedef  scalar_t__ vlc_tick_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {scalar_t__ pulse; int /*<<< orphan*/  pts; scalar_t__ tick; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ ReadEvents (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ SeekSet0 (TYPE_1__*) ; 
 scalar_t__ TICK ; 
 scalar_t__ UINT64_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Seek (demux_t *demux, vlc_tick_t pts)
{
    demux_sys_t *sys = demux->p_sys;

    /* Rewind if needed */
    if (pts < date_Get (&sys->pts) && SeekSet0 (demux))
        return VLC_EGENERIC;

    /* Fast forward */
    uint64_t pulse = sys->pulse;

    while (pts > date_Get (&sys->pts))
    {
        if (pulse == UINT64_MAX)
            return VLC_SUCCESS; /* premature end */
        if (ReadEvents (demux, &pulse, NULL))
            return VLC_EGENERIC;
    }

    sys->pulse = pulse;
    sys->tick = ((date_Get (&sys->pts) - VLC_TICK_0) / TICK) * TICK + VLC_TICK_0;
    return VLC_SUCCESS;
}