#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  unit; int /*<<< orphan*/  manager; int /*<<< orphan*/  leader; int /*<<< orphan*/  class; } ;
typedef  TYPE_1__ Machine ;
typedef  scalar_t__ KillWho ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ESRCH ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KILL_LEADER ; 
 int /*<<< orphan*/  MACHINE_CONTAINER ; 
 int /*<<< orphan*/  MACHINE_VM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int errno ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int) ; 
 int manager_kill_unit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int machine_kill(Machine *m, KillWho who, int signo) {
        assert(m);

        if (!IN_SET(m->class, MACHINE_VM, MACHINE_CONTAINER))
                return -EOPNOTSUPP;

        if (!m->unit)
                return -ESRCH;

        if (who == KILL_LEADER) {
                /* If we shall simply kill the leader, do so directly */

                if (kill(m->leader, signo) < 0)
                        return -errno;

                return 0;
        }

        /* Otherwise, make PID 1 do it for us, for the entire cgroup */
        return manager_kill_unit(m->manager, m->unit, signo, NULL);
}