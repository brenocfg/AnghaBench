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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int FORK_DEATHSIG ; 
 int FORK_LOG ; 
 int FORK_RESET_SIGNALS ; 
 int FORK_RLIMIT_NOFILE_SAFE ; 
 int /*<<< orphan*/  WAIT_LOG ; 
 int /*<<< orphan*/  X_OK ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execv (char const*,char**) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,char const*) ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ streq (char const*,char*) ; 
 char* strjoina (char*,char const*) ; 
 int wait_for_terminate_and_check (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int makefs(const char *type, const char *device) {
        const char *mkfs;
        pid_t pid;
        int r;

        if (streq(type, "swap"))
                mkfs = "/sbin/mkswap";
        else
                mkfs = strjoina("/sbin/mkfs.", type);
        if (access(mkfs, X_OK) != 0)
                return log_error_errno(errno, "%s is not executable: %m", mkfs);

        r = safe_fork("(mkfs)", FORK_RESET_SIGNALS|FORK_DEATHSIG|FORK_RLIMIT_NOFILE_SAFE|FORK_LOG, &pid);
        if (r < 0)
                return r;
        if (r == 0) {
                const char *cmdline[3] = { mkfs, device, NULL };

                /* Child */

                execv(cmdline[0], (char**) cmdline);
                _exit(EXIT_FAILURE);
        }

        return wait_for_terminate_and_check(mkfs, pid, WAIT_LOG);
}