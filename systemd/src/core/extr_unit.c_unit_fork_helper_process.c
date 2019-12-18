#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ cgroup_path; TYPE_1__* manager; } ;
typedef  TYPE_2__ pid_t ;
typedef  TYPE_2__ Unit ;
struct TYPE_10__ {int /*<<< orphan*/  cgroup_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_CGROUP ; 
 int /*<<< orphan*/  FORK_REOPEN_LOG ; 
 int /*<<< orphan*/  PR_SET_PDEATHSIG ; 
 int /*<<< orphan*/  SIGNALS_CRASH_HANDLER ; 
 int /*<<< orphan*/  SIGNALS_IGNORE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int cg_attach_everywhere (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_signals (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ignore_signals (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_unit_error_errno (TYPE_2__*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int safe_fork (char const*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  unit_realize_cgroup (TYPE_2__*) ; 

int unit_fork_helper_process(Unit *u, const char *name, pid_t *ret) {
        int r;

        assert(u);
        assert(ret);

        /* Forks off a helper process and makes sure it is a member of the unit's cgroup. Returns == 0 in the child,
         * and > 0 in the parent. The pid parameter is always filled in with the child's PID. */

        (void) unit_realize_cgroup(u);

        r = safe_fork(name, FORK_REOPEN_LOG, ret);
        if (r != 0)
                return r;

        (void) default_signals(SIGNALS_CRASH_HANDLER, SIGNALS_IGNORE, -1);
        (void) ignore_signals(SIGPIPE, -1);

        (void) prctl(PR_SET_PDEATHSIG, SIGTERM);

        if (u->cgroup_path) {
                r = cg_attach_everywhere(u->manager->cgroup_supported, u->cgroup_path, 0, NULL, NULL);
                if (r < 0) {
                        log_unit_error_errno(u, r, "Failed to join unit cgroup %s: %m", u->cgroup_path);
                        _exit(EXIT_CGROUP);
                }
        }

        return 0;
}