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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int FORK_DEATHSIG ; 
 int FORK_LOG ; 
 int FORK_RESET_SIGNALS ; 
 int FORK_RLIMIT_NOFILE_SAFE ; 
 int FORK_WAIT ; 
 int /*<<< orphan*/  F_OK ; 
#define  QUOTACHECK 128 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_force ; 
 scalar_t__ arg_skip ; 
 int /*<<< orphan*/  execv (char const* const,char**) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_setup_service () ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  parse_proc_cmdline_item ; 
 int proc_cmdline_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_files () ; 
 int /*<<< orphan*/  umask (int) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        log_setup_service();

        if (argc > 1)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "This program takes no arguments.");

        umask(0022);

        r = proc_cmdline_parse(parse_proc_cmdline_item, NULL, 0);
        if (r < 0)
                log_warning_errno(r, "Failed to parse kernel command line, ignoring: %m");

        test_files();

        if (!arg_force) {
                if (arg_skip)
                        return 0;

                if (access("/run/systemd/quotacheck", F_OK) < 0)
                        return 0;
        }

        r = safe_fork("(quotacheck)", FORK_RESET_SIGNALS|FORK_DEATHSIG|FORK_RLIMIT_NOFILE_SAFE|FORK_WAIT|FORK_LOG, NULL);
        if (r < 0)
                return r;
        if (r == 0) {
                static const char * const cmdline[] = {
                        QUOTACHECK,
                        "-anug",
                        NULL
                };

                /* Child */

                execv(cmdline[0], (char**) cmdline);
                _exit(EXIT_FAILURE); /* Operational error */
        }

        return 0;
}