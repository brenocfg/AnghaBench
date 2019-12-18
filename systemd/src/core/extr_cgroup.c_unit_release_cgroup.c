#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cgroup_control_inotify_wd; int cgroup_memory_inotify_wd; TYPE_1__* manager; int /*<<< orphan*/  id; scalar_t__ cgroup_path; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_6__ {int /*<<< orphan*/  cgroup_memory_inotify_wd_unit; int /*<<< orphan*/  cgroup_inotify_fd; int /*<<< orphan*/  cgroup_control_inotify_wd_unit; int /*<<< orphan*/  cgroup_unit; } ;

/* Variables and functions */
 scalar_t__ INT_TO_PTR (int) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ inotify_rm_watch (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_unit_debug_errno (TYPE_2__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mfree (scalar_t__) ; 

void unit_release_cgroup(Unit *u) {
        assert(u);

        /* Forgets all cgroup details for this cgroup — but does *not* destroy the cgroup. This is hence OK to call
         * when we close down everything for reexecution, where we really want to leave the cgroup in place. */

        if (u->cgroup_path) {
                (void) hashmap_remove(u->manager->cgroup_unit, u->cgroup_path);
                u->cgroup_path = mfree(u->cgroup_path);
        }

        if (u->cgroup_control_inotify_wd >= 0) {
                if (inotify_rm_watch(u->manager->cgroup_inotify_fd, u->cgroup_control_inotify_wd) < 0)
                        log_unit_debug_errno(u, errno, "Failed to remove cgroup control inotify watch %i for %s, ignoring: %m", u->cgroup_control_inotify_wd, u->id);

                (void) hashmap_remove(u->manager->cgroup_control_inotify_wd_unit, INT_TO_PTR(u->cgroup_control_inotify_wd));
                u->cgroup_control_inotify_wd = -1;
        }

        if (u->cgroup_memory_inotify_wd >= 0) {
                if (inotify_rm_watch(u->manager->cgroup_inotify_fd, u->cgroup_memory_inotify_wd) < 0)
                        log_unit_debug_errno(u, errno, "Failed to remove cgroup memory inotify watch %i for %s, ignoring: %m", u->cgroup_memory_inotify_wd, u->id);

                (void) hashmap_remove(u->manager->cgroup_memory_inotify_wd_unit, INT_TO_PTR(u->cgroup_memory_inotify_wd));
                u->cgroup_memory_inotify_wd = -1;
        }
}