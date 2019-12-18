#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  cgroup_path; TYPE_6__* manager; int /*<<< orphan*/  prefix; int /*<<< orphan*/  cgroup_supported; int /*<<< orphan*/  confirm_spawn; int /*<<< orphan*/  environment; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_11__ {int /*<<< orphan*/  prefix; int /*<<< orphan*/  cgroup_supported; } ;
typedef  TYPE_1__ ExecParameters ;

/* Variables and functions */
 int EXEC_CGROUP_DELEGATE ; 
 int EXEC_CHOWN_DIRECTORIES ; 
 int EXEC_PASS_LOG_UNIT ; 
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (TYPE_6__*) ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_get_confirm_spawn (TYPE_6__*) ; 
 int manager_get_effective_environment (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_cgroup_delegate (TYPE_1__*) ; 

int unit_set_exec_params(Unit *u, ExecParameters *p) {
        int r;

        assert(u);
        assert(p);

        /* Copy parameters from manager */
        r = manager_get_effective_environment(u->manager, &p->environment);
        if (r < 0)
                return r;

        p->confirm_spawn = manager_get_confirm_spawn(u->manager);
        p->cgroup_supported = u->manager->cgroup_supported;
        p->prefix = u->manager->prefix;
        SET_FLAG(p->flags, EXEC_PASS_LOG_UNIT|EXEC_CHOWN_DIRECTORIES, MANAGER_IS_SYSTEM(u->manager));

        /* Copy parameters from unit */
        p->cgroup_path = u->cgroup_path;
        SET_FLAG(p->flags, EXEC_CGROUP_DELEGATE, unit_cgroup_delegate(u));

        return 0;
}