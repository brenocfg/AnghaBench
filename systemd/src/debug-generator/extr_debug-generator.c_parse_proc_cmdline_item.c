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
 char const* DEBUGTTY ; 
 int /*<<< orphan*/  UNIT_NAME_MANGLE_WARN ; 
 int /*<<< orphan*/  arg_debug_shell ; 
 int /*<<< orphan*/  arg_default_unit ; 
 int /*<<< orphan*/  arg_mask ; 
 int /*<<< orphan*/  arg_wants ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int log_error_errno (int,char*,...) ; 
 int log_oom () ; 
 int parse_boolean (char const*) ; 
 scalar_t__ proc_cmdline_key_streq (char const*,char*) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 
 char* runlevel_to_target (char const*) ; 
 char* skip_dev_prefix (char const*) ; 
 scalar_t__ streq (char const*,char*) ; 
 int strv_consume (int /*<<< orphan*/ *,char*) ; 
 int unit_name_mangle (char const*,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int parse_proc_cmdline_item(const char *key, const char *value, void *data) {
        int r;

        assert(key);

        if (streq(key, "systemd.mask")) {
                char *n;

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                r = unit_name_mangle(value, UNIT_NAME_MANGLE_WARN, &n);
                if (r < 0)
                        return log_error_errno(r, "Failed to glob unit name: %m");

                r = strv_consume(&arg_mask, n);
                if (r < 0)
                        return log_oom();

        } else if (streq(key, "systemd.wants")) {
                char *n;

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                r = unit_name_mangle(value, UNIT_NAME_MANGLE_WARN, &n);
                if (r < 0)
                        return log_error_errno(r, "Failed to glob unit name: %m");

                r = strv_consume(&arg_wants, n);
                if (r < 0)
                        return log_oom();

        } else if (proc_cmdline_key_streq(key, "systemd.debug_shell")) {
                const char *t = NULL;

                r = value ? parse_boolean(value) : 1;
                if (r < 0)
                        t = skip_dev_prefix(value);
                else if (r > 0)
                        t = skip_dev_prefix(DEBUGTTY);

                if (free_and_strdup(&arg_debug_shell, t) < 0)
                        return log_oom();

        } else if (streq(key, "systemd.unit")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                r = free_and_strdup(&arg_default_unit, value);
                if (r < 0)
                        return log_error_errno(r, "Failed to set default unit %s: %m", value);

        } else if (!value) {
                const char *target;

                target = runlevel_to_target(key);
                if (target) {
                        r = free_and_strdup(&arg_default_unit, target);
                        if (r < 0)
                                return log_error_errno(r, "Failed to set default unit %s: %m", target);
                }
        }

        return 0;
}