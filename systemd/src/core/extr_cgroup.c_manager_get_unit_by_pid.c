#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/ **** Unit ;
struct TYPE_5__ {int /*<<< orphan*/  watch_pids; int /*<<< orphan*/  units; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  PID_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPECIAL_INIT_SCOPE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  getpid_cached () ; 
 int /*<<< orphan*/ ***** hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ***** manager_get_unit_by_pid_cgroup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_is_valid (int /*<<< orphan*/ ) ; 

Unit *manager_get_unit_by_pid(Manager *m, pid_t pid) {
        Unit *u, **array;

        assert(m);

        /* Note that a process might be owned by multiple units, we return only one here, which is good enough for most
         * cases, though not strictly correct. We prefer the one reported by cgroup membership, as that's the most
         * relevant one as children of the process will be assigned to that one, too, before all else. */

        if (!pid_is_valid(pid))
                return NULL;

        if (pid == getpid_cached())
                return hashmap_get(m->units, SPECIAL_INIT_SCOPE);

        u = manager_get_unit_by_pid_cgroup(m, pid);
        if (u)
                return u;

        u = hashmap_get(m->watch_pids, PID_TO_PTR(pid));
        if (u)
                return u;

        array = hashmap_get(m->watch_pids, PID_TO_PTR(-pid));
        if (array)
                return array[0];

        return NULL;
}