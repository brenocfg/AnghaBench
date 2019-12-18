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
 int /*<<< orphan*/  ACTION_REEXEC ; 
 scalar_t__ ACTION_RELOAD ; 
 int /*<<< orphan*/  IN_SET (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ arg_action ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ daemon_reload (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ kill (int,int /*<<< orphan*/ ) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int reload_with_fallback(void) {
        /* First, try systemd via D-Bus. */
        if (daemon_reload(0, NULL, NULL) >= 0)
                return 0;

        /* Nothing else worked, so let's try signals */
        assert(IN_SET(arg_action, ACTION_RELOAD, ACTION_REEXEC));

        if (kill(1, arg_action == ACTION_RELOAD ? SIGHUP : SIGTERM) < 0)
                return log_error_errno(errno, "kill() failed: %m");

        return 0;
}