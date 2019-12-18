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
typedef  int /*<<< orphan*/  uint64_t ;
struct dual_timestamp {scalar_t__ monotonic; } ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_6__ {scalar_t__ idle_action; scalar_t__ idle_action_usec; scalar_t__ idle_action_not_before_usec; int /*<<< orphan*/  idle_action_event_source; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ HANDLE_IGNORE ; 
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 scalar_t__ SD_EVENT_PRIORITY_IDLE ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_action_to_string (scalar_t__) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int manager_get_idle_hint (TYPE_1__*,struct dual_timestamp*) ; 
 int /*<<< orphan*/  manager_handle_action (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int sd_event_add_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*),TYPE_1__*) ; 
 int sd_event_source_set_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_priority (int /*<<< orphan*/ ,scalar_t__) ; 
 int sd_event_source_set_time (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int manager_dispatch_idle_action(sd_event_source *s, uint64_t t, void *userdata) {
        Manager *m = userdata;
        struct dual_timestamp since;
        usec_t n, elapse;
        int r;

        assert(m);

        if (m->idle_action == HANDLE_IGNORE ||
            m->idle_action_usec <= 0)
                return 0;

        n = now(CLOCK_MONOTONIC);

        r = manager_get_idle_hint(m, &since);
        if (r <= 0)
                /* Not idle. Let's check if after a timeout it might be idle then. */
                elapse = n + m->idle_action_usec;
        else {
                /* Idle! Let's see if it's time to do something, or if
                 * we shall sleep for longer. */

                if (n >= since.monotonic + m->idle_action_usec &&
                    (m->idle_action_not_before_usec <= 0 || n >= m->idle_action_not_before_usec + m->idle_action_usec)) {
                        log_info("System idle. Doing %s operation.", handle_action_to_string(m->idle_action));

                        manager_handle_action(m, 0, m->idle_action, false, false);
                        m->idle_action_not_before_usec = n;
                }

                elapse = MAX(since.monotonic, m->idle_action_not_before_usec) + m->idle_action_usec;
        }

        if (!m->idle_action_event_source) {

                r = sd_event_add_time(
                                m->event,
                                &m->idle_action_event_source,
                                CLOCK_MONOTONIC,
                                elapse, USEC_PER_SEC*30,
                                manager_dispatch_idle_action, m);
                if (r < 0)
                        return log_error_errno(r, "Failed to add idle event source: %m");

                r = sd_event_source_set_priority(m->idle_action_event_source, SD_EVENT_PRIORITY_IDLE+10);
                if (r < 0)
                        return log_error_errno(r, "Failed to set idle event source priority: %m");
        } else {
                r = sd_event_source_set_time(m->idle_action_event_source, elapse);
                if (r < 0)
                        return log_error_errno(r, "Failed to set idle event timer: %m");

                r = sd_event_source_set_enabled(m->idle_action_event_source, SD_EVENT_ONESHOT);
                if (r < 0)
                        return log_error_errno(r, "Failed to enable idle event timer: %m");
        }

        return 0;
}