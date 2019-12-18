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
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_Sleep (scalar_t__) ; 
 int /*<<< orphan*/  vlc_testcancel () ; 
 scalar_t__ vlc_tick_now () ; 

void vlc_tick_wait (vlc_tick_t deadline)
{
    vlc_tick_t delay;

    vlc_testcancel();
    while ((delay = (deadline - vlc_tick_now())) > 0)
    {
        delay /= 1000;
        if (unlikely(delay > 0x7fffffff))
            delay = 0x7fffffff;
        vlc_Sleep (delay);
        vlc_testcancel();
    }
}