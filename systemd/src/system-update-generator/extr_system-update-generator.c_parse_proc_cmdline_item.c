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
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_warning (char*,...) ; 
 int /*<<< orphan*/  proc_cmdline_value_missing (char const*,char const*) ; 
 scalar_t__ runlevel_to_target (char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int parse_proc_cmdline_item(const char *key, const char *value, void *data) {
        assert(key);

        /* Check if a run level is specified on the kernel command line. The
         * command line has higher priority than any on-disk configuration, so
         * it'll make any symlink we create moot.
         */

        if (streq(key, "systemd.unit") && !proc_cmdline_value_missing(key, value))
                log_warning("Offline system update overridden by kernel command line systemd.unit= setting");
        else if (!value && runlevel_to_target(key))
                log_warning("Offline system update overridden by runlevel \"%s\" on the kernel command line", key);

        return 0;
}