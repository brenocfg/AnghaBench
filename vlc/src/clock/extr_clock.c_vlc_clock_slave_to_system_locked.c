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
struct TYPE_6__ {double delay; TYPE_2__* owner; } ;
typedef  TYPE_1__ vlc_clock_t ;
struct TYPE_7__ {scalar_t__ pause_date; double delay; } ;
typedef  TYPE_2__ vlc_clock_main_t ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ main_stream_to_system (TYPE_2__*,scalar_t__) ; 
 scalar_t__ vlc_clock_monotonic_to_system_locked (TYPE_1__*,scalar_t__,scalar_t__,double) ; 

__attribute__((used)) static vlc_tick_t vlc_clock_slave_to_system_locked(vlc_clock_t *clock,
                                                   vlc_tick_t now,
                                                   vlc_tick_t ts, double rate)
{
    vlc_clock_main_t *main_clock = clock->owner;
    if (main_clock->pause_date != VLC_TICK_INVALID)
        return INT64_MAX;

    vlc_tick_t system = main_stream_to_system(main_clock, ts);
    if (system == VLC_TICK_INVALID)
    {
        /* We don't have a master sync point, let's fallback to a monotonic ref
         * point */
        system = vlc_clock_monotonic_to_system_locked(clock, now, ts, rate);
    }

    return system + (clock->delay - main_clock->delay) * rate;
}