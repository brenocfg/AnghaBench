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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ TIME_EPOCH_USEC ; 
 scalar_t__ clock_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec_store (struct timespec*,scalar_t__) ; 

int clock_apply_epoch(void) {
        struct timespec ts;

        if (now(CLOCK_REALTIME) >= TIME_EPOCH_USEC)
                return 0;

        if (clock_settime(CLOCK_REALTIME, timespec_store(&ts, TIME_EPOCH_USEC)) < 0)
                return -errno;

        return 1;
}