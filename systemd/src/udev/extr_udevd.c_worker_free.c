#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct worker {int /*<<< orphan*/  event; int /*<<< orphan*/  monitor; int /*<<< orphan*/  pid; TYPE_1__* manager; } ;
struct TYPE_2__ {int /*<<< orphan*/  workers; } ;

/* Variables and functions */
 int /*<<< orphan*/  PID_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  event_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct worker*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_monitor_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void worker_free(struct worker *worker) {
        if (!worker)
                return;

        assert(worker->manager);

        hashmap_remove(worker->manager->workers, PID_TO_PTR(worker->pid));
        sd_device_monitor_unref(worker->monitor);
        event_free(worker->event);

        free(worker);
}