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
struct TYPE_5__ {int /*<<< orphan*/ * worker_watch; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  monitor; int /*<<< orphan*/  workers; int /*<<< orphan*/  event; void* kill_workers_event; void* inotify_event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_UNDEF ; 
 size_t READ_END ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  event_queue_cleanup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_monitor_unref (int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_ctrl_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void manager_clear_for_worker(Manager *manager) {
        assert(manager);

        manager->inotify_event = sd_event_source_unref(manager->inotify_event);
        manager->kill_workers_event = sd_event_source_unref(manager->kill_workers_event);

        manager->event = sd_event_unref(manager->event);

        manager->workers = hashmap_free(manager->workers);
        event_queue_cleanup(manager, EVENT_UNDEF);

        manager->monitor = sd_device_monitor_unref(manager->monitor);
        manager->ctrl = udev_ctrl_unref(manager->ctrl);

        manager->worker_watch[READ_END] = safe_close(manager->worker_watch[READ_END]);
}