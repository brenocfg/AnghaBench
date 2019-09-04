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
typedef  int /*<<< orphan*/  UTIL_time_t ;

/* Variables and functions */
 scalar_t__ TIME_UTC ; 
 int /*<<< orphan*/  UTIL_TIME_INITIALIZER ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ timespec_get (int /*<<< orphan*/ *,scalar_t__) ; 

UTIL_time_t UTIL_getTime(void)
{
    /* time must be initialized, othersize it may fail msan test.
     * No good reason, likely a limitation of timespec_get() for some target */
    UTIL_time_t time = UTIL_TIME_INITIALIZER;
    if (timespec_get(&time, TIME_UTC) != TIME_UTC) {
        perror("timefn::timespec_get");
        abort();
    }
    return time;
}