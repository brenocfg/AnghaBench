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
typedef  scalar_t__ usec_t ;
struct TYPE_6__ {scalar_t__ scheduled_shutdown_timeout; scalar_t__ wall_message_timeout_source; int /*<<< orphan*/  event; int /*<<< orphan*/  scheduled_shutdown_type; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int USEC_PER_MINUTE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ isempty (int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int sd_event_add_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wall_message_timeout_handler ; 
 int warn_wall (TYPE_1__*,scalar_t__) ; 
 scalar_t__ when_wall (scalar_t__,scalar_t__) ; 

int manager_setup_wall_message_timer(Manager *m) {

        usec_t n, elapse;
        int r;

        assert(m);

        n = now(CLOCK_REALTIME);
        elapse = m->scheduled_shutdown_timeout;

        /* wall message handling */

        if (isempty(m->scheduled_shutdown_type)) {
                warn_wall(m, n);
                return 0;
        }

        if (elapse < n)
                return 0;

        /* Warn immediately if less than 15 minutes are left */
        if (elapse - n < 15 * USEC_PER_MINUTE) {
                r = warn_wall(m, n);
                if (r == 0)
                        return 0;
        }

        elapse = when_wall(n, elapse);
        if (elapse == 0)
                return 0;

        if (m->wall_message_timeout_source) {
                r = sd_event_source_set_time(m->wall_message_timeout_source, n + elapse);
                if (r < 0)
                        return log_error_errno(r, "sd_event_source_set_time() failed. %m");

                r = sd_event_source_set_enabled(m->wall_message_timeout_source, SD_EVENT_ONESHOT);
                if (r < 0)
                        return log_error_errno(r, "sd_event_source_set_enabled() failed. %m");
        } else {
                r = sd_event_add_time(m->event, &m->wall_message_timeout_source,
                                      CLOCK_REALTIME, n + elapse, 0, wall_message_timeout_handler, m);
                if (r < 0)
                        return log_error_errno(r, "sd_event_add_time() failed. %m");
        }

        return 0;
}