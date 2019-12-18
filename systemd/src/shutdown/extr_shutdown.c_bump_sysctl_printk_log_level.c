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
 int /*<<< orphan*/  log_debug_errno (int,char*,int) ; 
 int read_current_sysctl_printk_log_level () ; 
 int sysctl_writef (char*,char*,int) ; 

__attribute__((used)) static void bump_sysctl_printk_log_level(int min_level) {
        int current_lvl, r;

        /* Set the logging level to be able to see messages with log level smaller or equal to min_level */

        current_lvl = read_current_sysctl_printk_log_level();
        if (current_lvl < 0 || current_lvl >= min_level + 1)
                return;

        r = sysctl_writef("kernel/printk", "%i", min_level + 1);
        if (r < 0)
                log_debug_errno(r, "Failed to bump kernel.printk to %i: %m", min_level + 1);
}