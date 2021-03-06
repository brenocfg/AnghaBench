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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  US_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

int64_t libvlc_clock(void)
{
    return US_FROM_VLC_TICK(vlc_tick_now());
}