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
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_6__ {int sync_scheduled; scalar_t__ sync_interval_usec; int /*<<< orphan*/  sync_event_source; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int LOG_CRIT ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  SD_EVENT_PRIORITY_IMPORTANT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_event_add_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_now (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_event_source_set_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_dispatch_sync ; 
 int /*<<< orphan*/  server_sync (TYPE_1__*) ; 

int server_schedule_sync(Server *s, int priority) {
        int r;

        assert(s);

        if (priority <= LOG_CRIT) {
                /* Immediately sync to disk when this is of priority CRIT, ALERT, EMERG */
                server_sync(s);
                return 0;
        }

        if (s->sync_scheduled)
                return 0;

        if (s->sync_interval_usec > 0) {
                usec_t when;

                r = sd_event_now(s->event, CLOCK_MONOTONIC, &when);
                if (r < 0)
                        return r;

                when += s->sync_interval_usec;

                if (!s->sync_event_source) {
                        r = sd_event_add_time(
                                        s->event,
                                        &s->sync_event_source,
                                        CLOCK_MONOTONIC,
                                        when, 0,
                                        server_dispatch_sync, s);
                        if (r < 0)
                                return r;

                        r = sd_event_source_set_priority(s->sync_event_source, SD_EVENT_PRIORITY_IMPORTANT);
                } else {
                        r = sd_event_source_set_time(s->sync_event_source, when);
                        if (r < 0)
                                return r;

                        r = sd_event_source_set_enabled(s->sync_event_source, SD_EVENT_ONESHOT);
                }
                if (r < 0)
                        return r;

                s->sync_scheduled = true;
        }

        return 0;
}