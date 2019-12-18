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
 int /*<<< orphan*/  DEBUGTTY ; 
 int /*<<< orphan*/  arg_debug_shell ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  skip_dev_prefix (int /*<<< orphan*/ ) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_drop_in_format (char const*,char*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void install_debug_shell_dropin(const char *dir) {
        int r;

        if (streq(arg_debug_shell, skip_dev_prefix(DEBUGTTY)))
                return;

        r = write_drop_in_format(dir, "debug-shell.service", 50, "tty",
                        "[Unit]\n"
                        "Description=Early root shell on /dev/%s FOR DEBUGGING ONLY\n"
                        "ConditionPathExists=\n"
                        "[Service]\n"
                        "TTYPath=/dev/%s",
                        arg_debug_shell, arg_debug_shell);
        if (r < 0)
                log_warning_errno(r, "Failed to write drop-in for debug-shell.service, ignoring: %m");
}