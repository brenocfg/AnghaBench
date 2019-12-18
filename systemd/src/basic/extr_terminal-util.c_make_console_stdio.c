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
 int ACQUIRE_TERMINAL_FORCE ; 
 int ACQUIRE_TERMINAL_PERMISSIVE ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int acquire_terminal (char*,int,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int make_null_stdio () ; 
 int rearrange_stdio (int,int,int) ; 
 int reset_terminal_fd (int,int) ; 
 int /*<<< orphan*/  reset_terminal_feature_caches () ; 

int make_console_stdio(void) {
        int fd, r;

        /* Make /dev/console the controlling terminal and stdin/stdout/stderr, if we can. If we can't use
         * /dev/null instead. This is particularly useful if /dev/console is turned off, e.g. if console=null
         * is specified on the kernel command line. */

        fd = acquire_terminal("/dev/console", ACQUIRE_TERMINAL_FORCE|ACQUIRE_TERMINAL_PERMISSIVE, USEC_INFINITY);
        if (fd < 0) {
                log_warning_errno(fd, "Failed to acquire terminal, using /dev/null stdin/stdout/stderr instead: %m");

                r = make_null_stdio();
                if (r < 0)
                        return log_error_errno(r, "Failed to make /dev/null stdin/stdout/stderr: %m");

        } else {
                r = reset_terminal_fd(fd, true);
                if (r < 0)
                        log_warning_errno(r, "Failed to reset terminal, ignoring: %m");

                r = rearrange_stdio(fd, fd, fd); /* This invalidates 'fd' both on success and on failure. */
                if (r < 0)
                        return log_error_errno(r, "Failed to make terminal stdin/stdout/stderr: %m");
        }

        reset_terminal_feature_caches();
        return 0;
}