#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int exit; int /*<<< orphan*/  fd_inotify; int /*<<< orphan*/  inotify_event; int /*<<< orphan*/  ctrl; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_QUEUED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  event_queue_cleanup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_kill_workers (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_notify (int,char*) ; 
 int /*<<< orphan*/  udev_ctrl_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void manager_exit(Manager *manager) {
        assert(manager);

        manager->exit = true;

        sd_notify(false,
                  "STOPPING=1\n"
                  "STATUS=Starting shutdown...");

        /* close sources of new events and discard buffered events */
        manager->ctrl = udev_ctrl_unref(manager->ctrl);

        manager->inotify_event = sd_event_source_unref(manager->inotify_event);
        manager->fd_inotify = safe_close(manager->fd_inotify);

        /* discard queued events and kill workers */
        event_queue_cleanup(manager, EVENT_QUEUED);
        manager_kill_workers(manager);
}