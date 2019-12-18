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
struct TYPE_5__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_EXIT_USEC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_event_loop_with_idle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  check_idle ; 

__attribute__((used)) static int manager_run(Manager *m) {
        assert(m);

        return bus_event_loop_with_idle(
                        m->event,
                        m->bus,
                        "org.freedesktop.machine1",
                        DEFAULT_EXIT_USEC,
                        check_idle, m);
}