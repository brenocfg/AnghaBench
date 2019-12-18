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
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ dup2 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pager_pid ; 
 scalar_t__ safe_close (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int stderr_redirected ; 
 int /*<<< orphan*/  stdout ; 
 int stdout_redirected ; 
 scalar_t__ stored_stderr ; 
 scalar_t__ stored_stdout ; 
 int /*<<< orphan*/  wait_for_terminate (scalar_t__,int /*<<< orphan*/ *) ; 

void pager_close(void) {

        if (pager_pid <= 0)
                return;

        /* Inform pager that we are done */
        (void) fflush(stdout);
        if (stdout_redirected)
                if (stored_stdout < 0 || dup2(stored_stdout, STDOUT_FILENO) < 0)
                        (void) close(STDOUT_FILENO);
        stored_stdout = safe_close(stored_stdout);
        (void) fflush(stderr);
        if (stderr_redirected)
                if (stored_stderr < 0 || dup2(stored_stderr, STDERR_FILENO) < 0)
                        (void) close(STDERR_FILENO);
        stored_stderr = safe_close(stored_stderr);
        stdout_redirected = stderr_redirected = false;

        (void) kill(pager_pid, SIGCONT);
        (void) wait_for_terminate(pager_pid, NULL);
        pager_pid = 0;
}