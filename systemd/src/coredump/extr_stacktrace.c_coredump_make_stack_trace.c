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
 int EINVAL ; 
 int /*<<< orphan*/  dwfl_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwfl_errno () ; 
 int /*<<< orphan*/  log_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int make_stack_trace (int,char const*,char**) ; 

void coredump_make_stack_trace(int fd, const char *executable, char **ret) {
        int r;

        r = make_stack_trace(fd, executable, ret);
        if (r == -EINVAL)
                log_warning("Failed to generate stack trace: %s", dwfl_errmsg(dwfl_errno()));
        else if (r < 0)
                log_warning_errno(r, "Failed to generate stack trace: %m");
}