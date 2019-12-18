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
 int /*<<< orphan*/  LOG_TARGET_CONSOLE ; 
 scalar_t__ SHOW_STATUS_AUTO ; 
 scalar_t__ SHOW_STATUS_YES ; 
 scalar_t__ STR_IN_SET (char const*,char*,char*) ; 
 int UNIT_NAME_INSTANCE ; 
 int UNIT_NAME_PLAIN ; 
 scalar_t__ USEC_INFINITY ; 
 scalar_t__ _SHOW_STATUS_INVALID ; 
 int /*<<< orphan*/  arg_confirm_spawn ; 
 scalar_t__ arg_crash_chvt ; 
 int arg_crash_reboot ; 
 int arg_crash_shell ; 
 char** arg_default_environment ; 
 int arg_default_std_error ; 
 int arg_default_std_output ; 
 scalar_t__ arg_default_timeout_start_usec ; 
 int /*<<< orphan*/  arg_default_unit ; 
 int arg_dump_core ; 
 int /*<<< orphan*/  arg_early_core_pattern ; 
 int arg_service_watchdogs ; 
 scalar_t__ arg_show_status ; 
 int arg_status_unit_format ; 
 int /*<<< orphan*/  arg_watchdog_device ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ detect_container () ; 
 scalar_t__ env_assignment_is_valid (char const*) ; 
 int exec_output_from_string (char const*) ; 
 int /*<<< orphan*/  free_and_replace (int /*<<< orphan*/ ,char*) ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int in_initrd () ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_set_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warning (char*,char const*,...) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,char const*,...) ; 
 int parse_boolean (char const*) ; 
 int parse_confirm_spawn (char const*,char**) ; 
 int parse_crash_chvt (char const*,scalar_t__*) ; 
 int /*<<< orphan*/  parse_path_argument_and_warn (char const*,int,int /*<<< orphan*/ *) ; 
 int parse_sec (char const*,scalar_t__*) ; 
 int parse_show_status (char const*,scalar_t__*) ; 
 scalar_t__ path_is_absolute (char const*) ; 
 scalar_t__ proc_cmdline_key_streq (char const*,char*) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 
 char* runlevel_to_target (char const*) ; 
 int set_machine_id (char const*) ; 
 int /*<<< orphan*/  startswith (char const*,char*) ; 
 int status_unit_format_from_string (char const*) ; 
 scalar_t__ streq (char const*,char*) ; 
 char** strv_env_set (char**,char const*) ; 
 int /*<<< orphan*/  unit_name_is_valid (char const*,int) ; 

__attribute__((used)) static int parse_proc_cmdline_item(const char *key, const char *value, void *data) {

        int r;

        assert(key);

        if (STR_IN_SET(key, "systemd.unit", "rd.systemd.unit")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (!unit_name_is_valid(value, UNIT_NAME_PLAIN|UNIT_NAME_INSTANCE))
                        log_warning("Unit name specified on %s= is not valid, ignoring: %s", key, value);
                else if (in_initrd() == !!startswith(key, "rd.")) {
                        if (free_and_strdup(&arg_default_unit, value) < 0)
                                return log_oom();
                }

        } else if (proc_cmdline_key_streq(key, "systemd.dump_core")) {

                r = value ? parse_boolean(value) : true;
                if (r < 0)
                        log_warning_errno(r, "Failed to parse dump core switch %s, ignoring: %m", value);
                else
                        arg_dump_core = r;

        } else if (proc_cmdline_key_streq(key, "systemd.early_core_pattern")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (path_is_absolute(value))
                        (void) parse_path_argument_and_warn(value, false, &arg_early_core_pattern);
                else
                        log_warning("Specified core pattern '%s' is not an absolute path, ignoring.", value);

        } else if (proc_cmdline_key_streq(key, "systemd.crash_chvt")) {

                if (!value)
                        arg_crash_chvt = 0; /* turn on */
                else {
                        r = parse_crash_chvt(value, &arg_crash_chvt);
                        if (r < 0)
                                log_warning_errno(r, "Failed to parse crash chvt switch %s, ignoring: %m", value);
                }

        } else if (proc_cmdline_key_streq(key, "systemd.crash_shell")) {

                r = value ? parse_boolean(value) : true;
                if (r < 0)
                        log_warning_errno(r, "Failed to parse crash shell switch %s, ignoring: %m", value);
                else
                        arg_crash_shell = r;

        } else if (proc_cmdline_key_streq(key, "systemd.crash_reboot")) {

                r = value ? parse_boolean(value) : true;
                if (r < 0)
                        log_warning_errno(r, "Failed to parse crash reboot switch %s, ignoring: %m", value);
                else
                        arg_crash_reboot = r;

        } else if (proc_cmdline_key_streq(key, "systemd.confirm_spawn")) {
                char *s;

                r = parse_confirm_spawn(value, &s);
                if (r < 0)
                        log_warning_errno(r, "Failed to parse confirm_spawn switch %s, ignoring: %m", value);
                else
                        free_and_replace(arg_confirm_spawn, s);

        } else if (proc_cmdline_key_streq(key, "systemd.service_watchdogs")) {

                r = value ? parse_boolean(value) : true;
                if (r < 0)
                        log_warning_errno(r, "Failed to parse service watchdog switch %s, ignoring: %m", value);
                else
                        arg_service_watchdogs = r;

        } else if (proc_cmdline_key_streq(key, "systemd.show_status")) {

                if (value) {
                        r = parse_show_status(value, &arg_show_status);
                        if (r < 0)
                                log_warning_errno(r, "Failed to parse show status switch %s, ignoring: %m", value);
                } else
                        arg_show_status = SHOW_STATUS_YES;

        } else if (proc_cmdline_key_streq(key, "systemd.status_unit_format")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                r = status_unit_format_from_string(value);
                if (r < 0)
                        log_warning_errno(r, "Failed to parse %s=%s, ignoring: %m", key, value);
                else
                        arg_status_unit_format = r;

        } else if (proc_cmdline_key_streq(key, "systemd.default_standard_output")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                r = exec_output_from_string(value);
                if (r < 0)
                        log_warning_errno(r, "Failed to parse default standard output switch %s, ignoring: %m", value);
                else
                        arg_default_std_output = r;

        } else if (proc_cmdline_key_streq(key, "systemd.default_standard_error")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                r = exec_output_from_string(value);
                if (r < 0)
                        log_warning_errno(r, "Failed to parse default standard error switch %s, ignoring: %m", value);
                else
                        arg_default_std_error = r;

        } else if (streq(key, "systemd.setenv")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (env_assignment_is_valid(value)) {
                        char **env;

                        env = strv_env_set(arg_default_environment, value);
                        if (!env)
                                return log_oom();

                        arg_default_environment = env;
                } else
                        log_warning("Environment variable name '%s' is not valid. Ignoring.", value);

        } else if (proc_cmdline_key_streq(key, "systemd.machine_id")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                r = set_machine_id(value);
                if (r < 0)
                        log_warning_errno(r, "MachineID '%s' is not valid, ignoring: %m", value);

        } else if (proc_cmdline_key_streq(key, "systemd.default_timeout_start_sec")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                r = parse_sec(value, &arg_default_timeout_start_usec);
                if (r < 0)
                        log_warning_errno(r, "Failed to parse default start timeout '%s', ignoring: %m", value);

                if (arg_default_timeout_start_usec <= 0)
                        arg_default_timeout_start_usec = USEC_INFINITY;

        } else if (proc_cmdline_key_streq(key, "systemd.watchdog_device")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                (void) parse_path_argument_and_warn(value, false, &arg_watchdog_device);

        } else if (streq(key, "quiet") && !value) {

                if (arg_show_status == _SHOW_STATUS_INVALID)
                        arg_show_status = SHOW_STATUS_AUTO;

        } else if (streq(key, "debug") && !value) {

                /* Note that log_parse_environment() handles 'debug'
                 * too, and sets the log level to LOG_DEBUG. */

                if (detect_container() > 0)
                        log_set_target(LOG_TARGET_CONSOLE);

        } else if (!value) {
                const char *target;

                /* SysV compatibility */
                target = runlevel_to_target(key);
                if (target)
                        return free_and_strdup(&arg_default_unit, target);
        }

        return 0;
}