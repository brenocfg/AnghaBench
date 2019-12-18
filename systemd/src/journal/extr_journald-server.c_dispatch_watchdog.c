#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_3__ {int send_watchdog; int watchdog_usec; int /*<<< orphan*/  watchdog_event_source; int /*<<< orphan*/  notify_event_source; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_ON ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int sd_event_source_set_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dispatch_watchdog(sd_event_source *es, uint64_t usec, void *userdata) {
        Server *s = userdata;
        int r;

        assert(s);

        s->send_watchdog = true;

        r = sd_event_source_set_enabled(s->notify_event_source, SD_EVENT_ON);
        if (r < 0)
                log_warning_errno(r, "Failed to turn on notify event source: %m");

        r = sd_event_source_set_time(s->watchdog_event_source, usec + s->watchdog_usec / 2);
        if (r < 0)
                return log_error_errno(r, "Failed to restart watchdog event source: %m");

        r = sd_event_source_set_enabled(s->watchdog_event_source, SD_EVENT_ON);
        if (r < 0)
                return log_error_errno(r, "Failed to enable watchdog event source: %m");

        return 0;
}