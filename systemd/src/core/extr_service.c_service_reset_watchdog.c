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
struct TYPE_5__ {int /*<<< orphan*/  watchdog_timestamp; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dual_timestamp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_start_watchdog (TYPE_1__*) ; 

__attribute__((used)) static void service_reset_watchdog(Service *s) {
        assert(s);

        dual_timestamp_get(&s->watchdog_timestamp);
        service_start_watchdog(s);
}