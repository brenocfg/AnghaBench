#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ coeff; scalar_t__ rate; } ;
typedef  TYPE_1__ vlc_clock_main_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 

__attribute__((used)) static vlc_tick_t main_stream_to_system(vlc_clock_main_t *main_clock,
                                        vlc_tick_t ts)
{
    if (main_clock->offset == VLC_TICK_INVALID)
        return VLC_TICK_INVALID;
    return (vlc_tick_t)
        (ts * main_clock->coeff / main_clock->rate + main_clock->offset);
}