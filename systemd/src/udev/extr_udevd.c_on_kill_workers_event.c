#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  manager_kill_workers (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_kill_workers_event(sd_event_source *s, uint64_t usec, void *userdata) {
        Manager *manager = userdata;

        assert(manager);

        log_debug("Cleanup idle workers");
        manager_kill_workers(manager);

        return 1;
}