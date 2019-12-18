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
typedef  scalar_t__ VolatileMode ;

/* Variables and functions */
 scalar_t__ STR_IN_SET (char const*,char*,char*) ; 
 scalar_t__ VOLATILE_YES ; 
 int arg_fstab_enabled ; 
 int /*<<< orphan*/  arg_root_fstype ; 
 int /*<<< orphan*/  arg_root_hash ; 
 int /*<<< orphan*/  arg_root_options ; 
 int arg_root_rw ; 
 int /*<<< orphan*/  arg_root_what ; 
 int /*<<< orphan*/  arg_usr_fstype ; 
 int /*<<< orphan*/  arg_usr_options ; 
 int /*<<< orphan*/  arg_usr_what ; 
 scalar_t__ arg_volatile_mode ; 
 scalar_t__ free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_warning (char*,char const*) ; 
 int parse_boolean (char const*) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 
 int /*<<< orphan*/  strextend_with_separator (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ volatile_mode_from_string (char const*) ; 

__attribute__((used)) static int parse_proc_cmdline_item(const char *key, const char *value, void *data) {
        int r;

        /* root=, usr=, usrfstype= and roofstype= may occur more than once, the last
         * instance should take precedence.  In the case of multiple rootflags=
         * or usrflags= the arguments should be concatenated */

        if (STR_IN_SET(key, "fstab", "rd.fstab")) {

                r = value ? parse_boolean(value) : 1;
                if (r < 0)
                        log_warning("Failed to parse fstab switch %s. Ignoring.", value);
                else
                        arg_fstab_enabled = r;

        } else if (streq(key, "root")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (free_and_strdup(&arg_root_what, value) < 0)
                        return log_oom();

        } else if (streq(key, "rootfstype")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (free_and_strdup(&arg_root_fstype, value) < 0)
                        return log_oom();

        } else if (streq(key, "rootflags")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (!strextend_with_separator(&arg_root_options, ",", value, NULL))
                        return log_oom();

        } else if (streq(key, "roothash")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (free_and_strdup(&arg_root_hash, value) < 0)
                        return log_oom();

        } else if (streq(key, "mount.usr")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (free_and_strdup(&arg_usr_what, value) < 0)
                        return log_oom();

        } else if (streq(key, "mount.usrfstype")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (free_and_strdup(&arg_usr_fstype, value) < 0)
                        return log_oom();

        } else if (streq(key, "mount.usrflags")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (!strextend_with_separator(&arg_usr_options, ",", value, NULL))
                        return log_oom();

        } else if (streq(key, "rw") && !value)
                arg_root_rw = true;
        else if (streq(key, "ro") && !value)
                arg_root_rw = false;
        else if (streq(key, "systemd.volatile")) {
                VolatileMode m;

                if (value) {
                        m = volatile_mode_from_string(value);
                        if (m < 0)
                                log_warning("Failed to parse systemd.volatile= argument: %s", value);
                        else
                                arg_volatile_mode = m;
                } else
                        arg_volatile_mode = VOLATILE_YES;
        }

        return 0;
}