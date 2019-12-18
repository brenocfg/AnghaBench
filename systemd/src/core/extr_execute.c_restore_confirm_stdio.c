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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  assert (int*) ; 
 scalar_t__ dup2 (int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  release_terminal () ; 
 int safe_close (int) ; 

__attribute__((used)) static int restore_confirm_stdio(int *saved_stdin, int *saved_stdout) {
        int r = 0;

        assert(saved_stdin);
        assert(saved_stdout);

        release_terminal();

        if (*saved_stdin >= 0)
                if (dup2(*saved_stdin, STDIN_FILENO) < 0)
                        r = -errno;

        if (*saved_stdout >= 0)
                if (dup2(*saved_stdout, STDOUT_FILENO) < 0)
                        r = -errno;

        *saved_stdin = safe_close(*saved_stdin);
        *saved_stdout = safe_close(*saved_stdout);

        return r;
}