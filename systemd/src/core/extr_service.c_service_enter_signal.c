#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ send_sigkill; } ;
struct TYPE_12__ {scalar_t__ result; TYPE_2__ kill_context; int /*<<< orphan*/  timeout_stop_usec; int /*<<< orphan*/  main_pid_alien; int /*<<< orphan*/  control_pid; int /*<<< orphan*/  main_pid; } ;
typedef  int /*<<< orphan*/  ServiceState ;
typedef  scalar_t__ ServiceResult ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ SERVICE_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SERVICE_FINAL_SIGKILL ; 
 int /*<<< orphan*/  SERVICE_FINAL_SIGTERM ; 
 int /*<<< orphan*/  SERVICE_STOP_SIGKILL ; 
 int /*<<< orphan*/  SERVICE_STOP_SIGTERM ; 
 int /*<<< orphan*/  SERVICE_STOP_WATCHDOG ; 
 scalar_t__ SERVICE_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int service_arm_timer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_enter_dead (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  service_enter_stop_post (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  service_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_timeout_abort_usec (TYPE_1__*) ; 
 int /*<<< orphan*/  state_to_kill_operation (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_enqueue_rewatch_pids (int /*<<< orphan*/ ) ; 
 int unit_kill_context (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_watch_all_pids (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_enter_signal(Service *s, ServiceState state, ServiceResult f) {
        int r;

        assert(s);

        if (s->result == SERVICE_SUCCESS)
                s->result = f;

        /* Before sending any signal, make sure we track all members of this cgroup */
        (void) unit_watch_all_pids(UNIT(s));

        /* Also, enqueue a job that we recheck all our PIDs a bit later, given that it's likely some processes have
         * died now */
        (void) unit_enqueue_rewatch_pids(UNIT(s));

        r = unit_kill_context(
                        UNIT(s),
                        &s->kill_context,
                        state_to_kill_operation(s, state),
                        s->main_pid,
                        s->control_pid,
                        s->main_pid_alien);
        if (r < 0)
                goto fail;

        if (r > 0) {
                r = service_arm_timer(s, usec_add(now(CLOCK_MONOTONIC),
                                      state == SERVICE_STOP_WATCHDOG ? service_timeout_abort_usec(s) : s->timeout_stop_usec));
                if (r < 0)
                        goto fail;

                service_set_state(s, state);
        } else if (IN_SET(state, SERVICE_STOP_WATCHDOG, SERVICE_STOP_SIGTERM) && s->kill_context.send_sigkill)
                service_enter_signal(s, SERVICE_STOP_SIGKILL, SERVICE_SUCCESS);
        else if (IN_SET(state, SERVICE_STOP_WATCHDOG, SERVICE_STOP_SIGTERM, SERVICE_STOP_SIGKILL))
                service_enter_stop_post(s, SERVICE_SUCCESS);
        else if (state == SERVICE_FINAL_SIGTERM && s->kill_context.send_sigkill)
                service_enter_signal(s, SERVICE_FINAL_SIGKILL, SERVICE_SUCCESS);
        else
                service_enter_dead(s, SERVICE_SUCCESS, true);

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to kill processes: %m");

        if (IN_SET(state, SERVICE_STOP_WATCHDOG, SERVICE_STOP_SIGTERM, SERVICE_STOP_SIGKILL))
                service_enter_stop_post(s, SERVICE_FAILURE_RESOURCES);
        else
                service_enter_dead(s, SERVICE_FAILURE_RESOURCES, true);
}