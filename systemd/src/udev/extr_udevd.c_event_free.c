#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct event {TYPE_2__* manager; TYPE_1__* worker; int /*<<< orphan*/  timeout_event; int /*<<< orphan*/  timeout_warning_event; int /*<<< orphan*/  dev_kernel; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ pid; int /*<<< orphan*/  events; } ;
struct TYPE_3__ {int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 scalar_t__ LIST_IS_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct event*,int /*<<< orphan*/ ,struct event*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct event*) ; 
 scalar_t__ getpid_cached () ; 
 int /*<<< orphan*/  log_warning_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sd_device_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void event_free(struct event *event) {
        if (!event)
                return;

        assert(event->manager);

        LIST_REMOVE(event, event->manager->events, event);
        sd_device_unref(event->dev);
        sd_device_unref(event->dev_kernel);

        sd_event_source_unref(event->timeout_warning_event);
        sd_event_source_unref(event->timeout_event);

        if (event->worker)
                event->worker->event = NULL;

        /* only clean up the queue from the process that created it */
        if (LIST_IS_EMPTY(event->manager->events) &&
            event->manager->pid == getpid_cached())
                if (unlink("/run/udev/queue") < 0)
                        log_warning_errno(errno, "Failed to unlink /run/udev/queue: %m");

        free(event);
}