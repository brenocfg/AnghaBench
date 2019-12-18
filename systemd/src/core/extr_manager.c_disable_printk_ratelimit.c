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

/* Variables and functions */
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int sysctl_write (char*,char*) ; 

void disable_printk_ratelimit(void) {
        /* Disable kernel's printk ratelimit.
         *
         * Logging to /dev/kmsg is most useful during early boot and shutdown, where normal logging
         * mechanisms are not available. The semantics of this sysctl are such that any kernel command-line
         * setting takes precedence. */
        int r;

        r = sysctl_write("kernel/printk_devkmsg", "on");
        if (r < 0)
                log_debug_errno(r, "Failed to set sysctl kernel.printk_devkmsg=on: %m");
}