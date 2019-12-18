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
struct timespec {scalar_t__ tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ clock_getres (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ unlikely (int) ; 
 int vlc_clock_prec ; 

__attribute__((used)) static void vlc_clock_setup_once (void)
{
    struct timespec res;
    if (unlikely(clock_getres(CLOCK_MONOTONIC, &res) != 0 || res.tv_sec != 0))
        abort ();
    vlc_clock_prec = (res.tv_nsec + 500) / 1000;
}