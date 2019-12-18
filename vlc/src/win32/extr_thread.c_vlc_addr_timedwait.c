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
typedef  int vlc_tick_t ;
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 int WaitOnAddress (void*,unsigned int*,int,int) ; 

bool vlc_addr_timedwait(void *addr, unsigned val, vlc_tick_t delay)
{
    delay = (delay + (1000-1)) / 1000;

    if (delay > 0x7fffffff)
    {
        WaitOnAddress(addr, &val, sizeof (val), 0x7fffffff);
        return true; /* woke up early, claim spurious wake-up */
    }

    return WaitOnAddress(addr, &val, sizeof (val), delay);
}