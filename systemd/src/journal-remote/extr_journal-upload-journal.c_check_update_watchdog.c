#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int usec_t ;
struct TYPE_3__ {int watchdog_usec; int watchdog_timestamp; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_notify (int,char*) ; 
 int usec_sub_unsigned (int,int) ; 

__attribute__((used)) static void check_update_watchdog(Uploader *u) {
        usec_t after;
        usec_t elapsed_time;

        if (u->watchdog_usec <= 0)
                return;

        after = now(CLOCK_MONOTONIC);
        elapsed_time = usec_sub_unsigned(after, u->watchdog_timestamp);
        if (elapsed_time > u->watchdog_usec / 2) {
                log_debug("Update watchdog timer");
                sd_notify(false, "WATCHDOG=1");
                u->watchdog_timestamp = after;
        }
}