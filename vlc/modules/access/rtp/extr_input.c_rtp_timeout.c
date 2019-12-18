#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;

/* Variables and functions */
 scalar_t__ CLOCK_FREQ ; 
 scalar_t__ INT64_C (int) ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static int rtp_timeout (vlc_tick_t deadline)
{
    if (deadline == VLC_TICK_INVALID)
        return -1; /* infinite */

    vlc_tick_t t = vlc_tick_now ();
    if (t >= deadline)
        return 0;

    t = (deadline - t) / (CLOCK_FREQ / INT64_C(1000));
    if (unlikely(t > INT_MAX))
        return INT_MAX;
    return t;
}