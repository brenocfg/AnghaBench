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
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_tick_from_timespec (struct timespec*) ; 

vlc_tick_t vlc_tick_now (void)
{
    struct timespec ts;

    if (unlikely(clock_gettime (CLOCK_MONOTONIC, &ts) != 0))
        abort ();

    return vlc_tick_from_timespec( &ts );
}