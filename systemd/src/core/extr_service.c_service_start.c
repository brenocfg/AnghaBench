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
struct TYPE_12__ {int reset_accounting; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_13__ {scalar_t__ state; int main_pid_known; int main_pid_alien; int forbid_restart; int watchdog_override_enable; int flush_n_restarts; scalar_t__ n_restarts; int /*<<< orphan*/  main_exec_status; int /*<<< orphan*/  exec_command; int /*<<< orphan*/  watchdog_override_usec; int /*<<< orphan*/  watchdog_usec; int /*<<< orphan*/  watchdog_original_usec; int /*<<< orphan*/  notify_state; scalar_t__ status_errno; int /*<<< orphan*/  status_text; void* reload_result; void* result; } ;
typedef  TYPE_2__ Service ;

/* Variables and functions */
 int EAGAIN ; 
 TYPE_2__* IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  NOTIFY_UNKNOWN ; 
 TYPE_2__* SERVICE (TYPE_1__*) ; 
 scalar_t__ SERVICE_AUTO_RESTART ; 
 int /*<<< orphan*/  SERVICE_CLEANING ; 
 int /*<<< orphan*/  SERVICE_CONDITION ; 
 int /*<<< orphan*/  SERVICE_DEAD ; 
 int /*<<< orphan*/  SERVICE_FAILED ; 
 int /*<<< orphan*/  SERVICE_FAILURE_START_LIMIT_HIT ; 
 int /*<<< orphan*/  SERVICE_FINAL_SIGKILL ; 
 int /*<<< orphan*/  SERVICE_FINAL_SIGTERM ; 
 int /*<<< orphan*/  SERVICE_START ; 
 int /*<<< orphan*/  SERVICE_START_POST ; 
 int /*<<< orphan*/  SERVICE_START_PRE ; 
 int /*<<< orphan*/  SERVICE_STOP ; 
 int /*<<< orphan*/  SERVICE_STOP_POST ; 
 int /*<<< orphan*/  SERVICE_STOP_SIGKILL ; 
 int /*<<< orphan*/  SERVICE_STOP_SIGTERM ; 
 int /*<<< orphan*/  SERVICE_STOP_WATCHDOG ; 
 void* SERVICE_SUCCESS ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  _SERVICE_EXEC_COMMAND_MAX ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  exec_command_reset_status_list_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_status_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_enter_condition (TYPE_2__*) ; 
 int /*<<< orphan*/  service_enter_dead (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int unit_acquire_invocation_id (TYPE_1__*) ; 
 int unit_test_start_limit (TYPE_1__*) ; 

__attribute__((used)) static int service_start(Unit *u) {
        Service *s = SERVICE(u);
        int r;

        assert(s);

        /* We cannot fulfill this request right now, try again later
         * please! */
        if (IN_SET(s->state,
                   SERVICE_STOP, SERVICE_STOP_WATCHDOG, SERVICE_STOP_SIGTERM, SERVICE_STOP_SIGKILL, SERVICE_STOP_POST,
                   SERVICE_FINAL_SIGTERM, SERVICE_FINAL_SIGKILL, SERVICE_CLEANING))
                return -EAGAIN;

        /* Already on it! */
        if (IN_SET(s->state, SERVICE_CONDITION, SERVICE_START_PRE, SERVICE_START, SERVICE_START_POST))
                return 0;

        /* A service that will be restarted must be stopped first to
         * trigger BindsTo and/or OnFailure dependencies. If a user
         * does not want to wait for the holdoff time to elapse, the
         * service should be manually restarted, not started. We
         * simply return EAGAIN here, so that any start jobs stay
         * queued, and assume that the auto restart timer will
         * eventually trigger the restart. */
        if (s->state == SERVICE_AUTO_RESTART)
                return -EAGAIN;

        assert(IN_SET(s->state, SERVICE_DEAD, SERVICE_FAILED));

        /* Make sure we don't enter a busy loop of some kind. */
        r = unit_test_start_limit(u);
        if (r < 0) {
                service_enter_dead(s, SERVICE_FAILURE_START_LIMIT_HIT, false);
                return r;
        }

        r = unit_acquire_invocation_id(u);
        if (r < 0)
                return r;

        s->result = SERVICE_SUCCESS;
        s->reload_result = SERVICE_SUCCESS;
        s->main_pid_known = false;
        s->main_pid_alien = false;
        s->forbid_restart = false;

        s->status_text = mfree(s->status_text);
        s->status_errno = 0;

        s->notify_state = NOTIFY_UNKNOWN;

        s->watchdog_original_usec = s->watchdog_usec;
        s->watchdog_override_enable = false;
        s->watchdog_override_usec = USEC_INFINITY;

        exec_command_reset_status_list_array(s->exec_command, _SERVICE_EXEC_COMMAND_MAX);
        exec_status_reset(&s->main_exec_status);

        /* This is not an automatic restart? Flush the restart counter then */
        if (s->flush_n_restarts) {
                s->n_restarts = 0;
                s->flush_n_restarts = false;
        }

        u->reset_accounting = true;

        service_enter_condition(s);
        return 1;
}