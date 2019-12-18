#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_15__ {TYPE_1__* manager; } ;
struct TYPE_13__ {int /*<<< orphan*/  monotonic; } ;
struct TYPE_14__ {scalar_t__ watchdog_event_source; TYPE_2__ watchdog_timestamp; } ;
struct TYPE_12__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_3__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  SD_EVENT_PRIORITY_IDLE ; 
 TYPE_8__* UNIT (TYPE_3__*) ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (TYPE_8__*,int,char*) ; 
 int sd_event_add_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (scalar_t__,char*) ; 
 int sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_priority (scalar_t__,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_dispatch_watchdog ; 
 int /*<<< orphan*/  service_get_watchdog_usec (TYPE_3__*) ; 
 int /*<<< orphan*/  service_stop_watchdog (TYPE_3__*) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_start_watchdog(Service *s) {
        usec_t watchdog_usec;
        int r;

        assert(s);

        watchdog_usec = service_get_watchdog_usec(s);
        if (IN_SET(watchdog_usec, 0, USEC_INFINITY)) {
                service_stop_watchdog(s);
                return;
        }

        if (s->watchdog_event_source) {
                r = sd_event_source_set_time(s->watchdog_event_source, usec_add(s->watchdog_timestamp.monotonic, watchdog_usec));
                if (r < 0) {
                        log_unit_warning_errno(UNIT(s), r, "Failed to reset watchdog timer: %m");
                        return;
                }

                r = sd_event_source_set_enabled(s->watchdog_event_source, SD_EVENT_ONESHOT);
        } else {
                r = sd_event_add_time(
                                UNIT(s)->manager->event,
                                &s->watchdog_event_source,
                                CLOCK_MONOTONIC,
                                usec_add(s->watchdog_timestamp.monotonic, watchdog_usec), 0,
                                service_dispatch_watchdog, s);
                if (r < 0) {
                        log_unit_warning_errno(UNIT(s), r, "Failed to add watchdog timer: %m");
                        return;
                }

                (void) sd_event_source_set_description(s->watchdog_event_source, "service-watchdog");

                /* Let's process everything else which might be a sign
                 * of living before we consider a service died. */
                r = sd_event_source_set_priority(s->watchdog_event_source, SD_EVENT_PRIORITY_IDLE);
        }
        if (r < 0)
                log_unit_warning_errno(UNIT(s), r, "Failed to install watchdog timer: %m");
}