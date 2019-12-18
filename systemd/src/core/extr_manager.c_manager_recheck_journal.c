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
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 scalar_t__ MANAGER_IS_RELOADING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int getpid_cached () ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_set_prohibit_ipc (int) ; 
 int /*<<< orphan*/  manager_journal_is_running (int /*<<< orphan*/ *) ; 

void manager_recheck_journal(Manager *m) {

        assert(m);

        /* Don't bother with this unless we are in the special situation of being PID 1 */
        if (getpid_cached() != 1)
                return;

        /* Don't check this while we are reloading, things might still change */
        if (MANAGER_IS_RELOADING(m))
                return;

        /* The journal is fully and entirely up? If so, let's permit logging to it, if that's configured. If the
         * journal is down, don't ever log to it, otherwise we might end up deadlocking ourselves as we might trigger
         * an activation ourselves we can't fulfill. */
        log_set_prohibit_ipc(!manager_journal_is_running(m));
        log_open();
}