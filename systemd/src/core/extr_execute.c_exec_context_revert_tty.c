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
typedef  int /*<<< orphan*/  ExecContext ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TTY_GID ; 
 int /*<<< orphan*/  TTY_MODE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int chmod_and_chown (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_context_may_touch_tty (int /*<<< orphan*/ *) ; 
 char* exec_context_tty_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_context_tty_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,char const*) ; 

void exec_context_revert_tty(ExecContext *c) {
        int r;

        assert(c);

        /* First, reset the TTY (possibly kicking everybody else from the TTY) */
        exec_context_tty_reset(c, NULL);

        /* And then undo what chown_terminal() did earlier. Note that we only do this if we have a path
         * configured. If the TTY was passed to us as file descriptor we assume the TTY is opened and managed
         * by whoever passed it to us and thus knows better when and how to chmod()/chown() it back. */

        if (exec_context_may_touch_tty(c)) {
                const char *path;

                path = exec_context_tty_path(c);
                if (path) {
                        r = chmod_and_chown(path, TTY_MODE, 0, TTY_GID);
                        if (r < 0 && r != -ENOENT)
                                log_warning_errno(r, "Failed to reset TTY ownership/access mode of %s, ignoring: %m", path);
                }
        }
}