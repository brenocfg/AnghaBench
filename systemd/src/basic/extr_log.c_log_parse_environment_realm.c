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
typedef  int /*<<< orphan*/  LogRealm ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_CMDLINE_STRIP_RD_PREFIX ; 
 scalar_t__ get_ctty_devnr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int getpid_cached () ; 
 scalar_t__ log_set_max_level_from_string_realm (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ log_set_target_from_string (char const*) ; 
 scalar_t__ log_show_color_from_string (char const*) ; 
 scalar_t__ log_show_location_from_string (char const*) ; 
 int /*<<< orphan*/  log_warning (char*,char const*) ; 
 int /*<<< orphan*/  parse_proc_cmdline_item ; 
 int /*<<< orphan*/  proc_cmdline_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void log_parse_environment_realm(LogRealm realm) {
        /* Do not call from library code. */

        const char *e;

        if (getpid_cached() == 1 || get_ctty_devnr(0, NULL) < 0)
                /* Only try to read the command line in daemons. We assume that anything that has a
                 * controlling tty is user stuff. For PID1 we do a special check in case it hasn't
                 * closed the console yet. */
                (void) proc_cmdline_parse(parse_proc_cmdline_item, NULL, PROC_CMDLINE_STRIP_RD_PREFIX);

        e = getenv("SYSTEMD_LOG_TARGET");
        if (e && log_set_target_from_string(e) < 0)
                log_warning("Failed to parse log target '%s'. Ignoring.", e);

        e = getenv("SYSTEMD_LOG_LEVEL");
        if (e && log_set_max_level_from_string_realm(realm, e) < 0)
                log_warning("Failed to parse log level '%s'. Ignoring.", e);

        e = getenv("SYSTEMD_LOG_COLOR");
        if (e && log_show_color_from_string(e) < 0)
                log_warning("Failed to parse log color '%s'. Ignoring.", e);

        e = getenv("SYSTEMD_LOG_LOCATION");
        if (e && log_show_location_from_string(e) < 0)
                log_warning("Failed to parse log location '%s'. Ignoring.", e);
}