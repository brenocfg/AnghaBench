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
struct TYPE_5__ {scalar_t__ pid; int /*<<< orphan*/  worker_watch; int /*<<< orphan*/  fd_inotify; int /*<<< orphan*/  rules; int /*<<< orphan*/  properties; int /*<<< orphan*/  rtnl; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ getpid_cached () ; 
 int /*<<< orphan*/  hashmap_free_free_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_clear_for_worker (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close_pair (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_monitor_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_builtin_exit () ; 
 int /*<<< orphan*/  udev_ctrl_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_rules_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void manager_free(Manager *manager) {
        if (!manager)
                return;

        manager->monitor = sd_device_monitor_unref(manager->monitor);

        udev_builtin_exit();

        if (manager->pid == getpid_cached())
                udev_ctrl_cleanup(manager->ctrl);

        manager_clear_for_worker(manager);

        sd_netlink_unref(manager->rtnl);

        hashmap_free_free_free(manager->properties);
        udev_rules_free(manager->rules);

        safe_close(manager->fd_inotify);
        safe_close_pair(manager->worker_watch);

        free(manager);
}