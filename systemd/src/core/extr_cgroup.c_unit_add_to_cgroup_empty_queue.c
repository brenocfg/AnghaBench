#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int in_cgroup_empty_queue; TYPE_1__* manager; int /*<<< orphan*/  cgroup_path; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_7__ {int /*<<< orphan*/  cgroup_empty_event_source; int /*<<< orphan*/  cgroup_empty_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int cg_is_empty_recursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_empty_queue ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int /*<<< orphan*/  log_unit_debug_errno (TYPE_2__*,int,char*,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void unit_add_to_cgroup_empty_queue(Unit *u) {
        int r;

        assert(u);

        /* Note that there are four different ways how cgroup empty events reach us:
         *
         * 1. On the unified hierarchy we get an inotify event on the cgroup
         *
         * 2. On the legacy hierarchy, when running in system mode, we get a datagram on the cgroup agent socket
         *
         * 3. On the legacy hierarchy, when running in user mode, we get a D-Bus signal on the system bus
         *
         * 4. On the legacy hierarchy, in service units we start watching all processes of the cgroup for SIGCHLD as
         *    soon as we get one SIGCHLD, to deal with unreliable cgroup notifications.
         *
         * Regardless which way we got the notification, we'll verify it here, and then add it to a separate
         * queue. This queue will be dispatched at a lower priority than the SIGCHLD handler, so that we always use
         * SIGCHLD if we can get it first, and only use the cgroup empty notifications if there's no SIGCHLD pending
         * (which might happen if the cgroup doesn't contain processes that are our own child, which is typically the
         * case for scope units). */

        if (u->in_cgroup_empty_queue)
                return;

        /* Let's verify that the cgroup is really empty */
        if (!u->cgroup_path)
                return;
        r = cg_is_empty_recursive(SYSTEMD_CGROUP_CONTROLLER, u->cgroup_path);
        if (r < 0) {
                log_unit_debug_errno(u, r, "Failed to determine whether cgroup %s is empty: %m", u->cgroup_path);
                return;
        }
        if (r == 0)
                return;

        LIST_PREPEND(cgroup_empty_queue, u->manager->cgroup_empty_queue, u);
        u->in_cgroup_empty_queue = true;

        /* Trigger the defer event */
        r = sd_event_source_set_enabled(u->manager->cgroup_empty_event_source, SD_EVENT_ONESHOT);
        if (r < 0)
                log_debug_errno(r, "Failed to enable cgroup empty event source: %m");
}