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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  log_set_max_level (int /*<<< orphan*/ ) ; 
 scalar_t__ log_set_max_level_from_string (char const*) ; 
 scalar_t__ log_set_target_from_string (char const*) ; 
 scalar_t__ log_show_color_from_string (char*) ; 
 scalar_t__ log_show_location_from_string (char*) ; 
 int /*<<< orphan*/  log_warning (char*,char const*) ; 
 scalar_t__ proc_cmdline_key_streq (char const*,char*) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int parse_proc_cmdline_item(const char *key, const char *value, void *data) {

        /*
         * The systemd.log_xyz= settings are parsed by all tools, and
         * so is "debug".
         *
         * However, "quiet" is only parsed by PID 1, and only turns of
         * status output to /dev/console, but does not alter the log
         * level.
         */

        if (streq(key, "debug") && !value)
                log_set_max_level(LOG_DEBUG);

        else if (proc_cmdline_key_streq(key, "systemd.log_target")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (log_set_target_from_string(value) < 0)
                        log_warning("Failed to parse log target '%s'. Ignoring.", value);

        } else if (proc_cmdline_key_streq(key, "systemd.log_level")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (log_set_max_level_from_string(value) < 0)
                        log_warning("Failed to parse log level '%s'. Ignoring.", value);

        } else if (proc_cmdline_key_streq(key, "systemd.log_color")) {

                if (log_show_color_from_string(value ?: "1") < 0)
                        log_warning("Failed to parse log color setting '%s'. Ignoring.", value);

        } else if (proc_cmdline_key_streq(key, "systemd.log_location")) {

                if (log_show_location_from_string(value ?: "1") < 0)
                        log_warning("Failed to parse log location setting '%s'. Ignoring.", value);
        }

        return 0;
}