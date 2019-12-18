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
 int /*<<< orphan*/  O_RDWR ; 
 int log_dup_console () ; 
 int log_error_errno (int,char*) ; 
 int open_terminal (char*,int /*<<< orphan*/ ) ; 
 int rearrange_stdio (int,int,int) ; 

__attribute__((used)) static int setup_stdio_as_dev_console(void) {
        int terminal;
        int r;

        terminal = open_terminal("/dev/console", O_RDWR);
        if (terminal < 0)
                return log_error_errno(terminal, "Failed to open console: %m");

        /* Make sure we can continue logging to the original stderr, even if
         * stderr points elsewhere now */
        r = log_dup_console();
        if (r < 0)
                return log_error_errno(r, "Failed to duplicate stderr: %m");

        /* invalidates 'terminal' on success and failure */
        r = rearrange_stdio(terminal, terminal, terminal);
        if (r < 0)
                return log_error_errno(r, "Failed to move console to stdin/stdout/stderr: %m");

        return 0;
}