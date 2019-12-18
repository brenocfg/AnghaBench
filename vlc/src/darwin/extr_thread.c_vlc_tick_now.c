#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int quotient; int remainder; int divider; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_FROM_NS (int) ; 
 int mach_absolute_time () ; 
 TYPE_1__ vlc_clock_conversion ; 
 int /*<<< orphan*/  vlc_clock_setup () ; 

vlc_tick_t vlc_tick_now (void)
{
    vlc_clock_setup();
    uint64_t date = mach_absolute_time();

    date = date * vlc_clock_conversion.quotient +
        date * vlc_clock_conversion.remainder / vlc_clock_conversion.divider;
    return VLC_TICK_FROM_NS(date);
}