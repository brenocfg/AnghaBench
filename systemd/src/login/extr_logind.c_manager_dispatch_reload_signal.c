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
struct signalfd_siginfo {int dummy; } ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int manager_parse_config_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_reset_config (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int manager_dispatch_reload_signal(sd_event_source *s, const struct signalfd_siginfo *si, void *userdata) {
        Manager *m = userdata;
        int r;

        manager_reset_config(m);
        r = manager_parse_config_file(m);
        if (r < 0)
                log_warning_errno(r, "Failed to parse config file, using defaults: %m");
        else
                log_info("Config file reloaded.");

        return 0;
}