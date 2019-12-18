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
 int arg_force ; 
 char* arg_repair ; 
 int arg_skip ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_warning (char*,...) ; 
 int parse_boolean (char const*) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int parse_proc_cmdline_item(const char *key, const char *value, void *data) {
        int r;

        assert(key);

        if (streq(key, "fsck.mode")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (streq(value, "auto"))
                        arg_force = arg_skip = false;
                else if (streq(value, "force"))
                        arg_force = true;
                else if (streq(value, "skip"))
                        arg_skip = true;
                else
                        log_warning("Invalid fsck.mode= parameter '%s'. Ignoring.", value);

        } else if (streq(key, "fsck.repair")) {

                if (proc_cmdline_value_missing(key, value))
                        return 0;

                if (streq(value, "preen"))
                        arg_repair = "-a";
                else {
                        r = parse_boolean(value);
                        if (r > 0)
                                arg_repair = "-y";
                        else if (r == 0)
                                arg_repair = "-n";
                        else
                                log_warning("Invalid fsck.repair= parameter '%s'. Ignoring.", value);
                }
        }

#if HAVE_SYSV_COMPAT
        else if (streq(key, "fastboot") && !value) {
                log_warning("Please pass 'fsck.mode=skip' rather than 'fastboot' on the kernel command line.");
                arg_skip = true;

        } else if (streq(key, "forcefsck") && !value) {
                log_warning("Please pass 'fsck.mode=force' rather than 'forcefsck' on the kernel command line.");
                arg_force = true;
        }
#endif

        return 0;
}