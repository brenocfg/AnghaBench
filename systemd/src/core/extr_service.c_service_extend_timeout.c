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
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_5__ {int /*<<< orphan*/  watchdog_event_source; int /*<<< orphan*/  timer_event_source; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_extend_event_source_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_extend_timeout(Service *s, usec_t extend_timeout_usec) {
        usec_t extended;

        assert(s);

        if (IN_SET(extend_timeout_usec, 0, USEC_INFINITY))
                return;

        extended = usec_add(now(CLOCK_MONOTONIC), extend_timeout_usec);

        service_extend_event_source_timeout(s, s->timer_event_source, extended);
        service_extend_event_source_timeout(s, s->watchdog_event_source, extended);
}