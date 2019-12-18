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
 int FORK_NULL_STDIO ; 
 int FORK_RESET_SIGNALS ; 
 int FORK_RLIMIT_NOFILE_SAFE ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execvp (char const*,char**) ; 
 int /*<<< orphan*/  log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 char* strndupa (char const*,int) ; 
 char* strrchr (char const*,char) ; 
 int wait_for_terminate_and_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int show_man_page(const char *desc, bool null_stdio) {
        const char *args[4] = { "man", NULL, NULL, NULL };
        char *e = NULL;
        pid_t pid;
        size_t k;
        int r;

        k = strlen(desc);

        if (desc[k-1] == ')')
                e = strrchr(desc, '(');

        if (e) {
                char *page = NULL, *section = NULL;

                page = strndupa(desc, e - desc);
                section = strndupa(e + 1, desc + k - e - 2);

                args[1] = section;
                args[2] = page;
        } else
                args[1] = desc;

        r = safe_fork("(man)", FORK_RESET_SIGNALS|FORK_DEATHSIG|(null_stdio ? FORK_NULL_STDIO : 0)|FORK_RLIMIT_NOFILE_SAFE|FORK_LOG, &pid);
        if (r < 0)
                return r;
        if (r == 0) {
                /* Child */
                execvp(args[0], (char**) args);
                log_error_errno(errno, "Failed to execute man: %m");
                _exit(EXIT_FAILURE);
        }

        return wait_for_terminate_and_check(NULL, pid, 0);
}