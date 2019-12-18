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
 scalar_t__ VLC_TICK_FROM_MS (unsigned int) ; 
 scalar_t__ vlc_tick_from_sec (unsigned int) ; 

__attribute__((used)) static vlc_tick_t MakeTime( unsigned t[4] )
{
    return vlc_tick_from_sec( t[0] * 3600 + t[1] * 60 + t[2] ) +
           VLC_TICK_FROM_MS(t[3]);
}