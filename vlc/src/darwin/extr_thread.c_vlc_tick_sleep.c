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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct timespec {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int nanosleep (struct timespec*,struct timespec*) ; 
 struct timespec timespec_from_vlc_tick (int /*<<< orphan*/ ) ; 

void vlc_tick_sleep (vlc_tick_t delay)
{
    struct timespec ts = timespec_from_vlc_tick (delay);

    /* nanosleep uses mach_absolute_time and mach_wait_until internally,
       but also handles kernel errors. Thus we use just this. */
    while (nanosleep (&ts, &ts) == -1)
        assert (errno == EINTR);
}