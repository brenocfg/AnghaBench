#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnitActiveState ;
struct TYPE_18__ {int /*<<< orphan*/  manager; scalar_t__ job; } ;
struct TYPE_17__ {size_t state; scalar_t__ type; scalar_t__ reload_result; scalar_t__ result; scalar_t__ will_auto_restart; void* exec_fd_event_source; int /*<<< orphan*/  control_command_id; int /*<<< orphan*/ * control_command; int /*<<< orphan*/ * main_command; void* timer_event_source; } ;
typedef  size_t ServiceState ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 scalar_t__ IN_SET (size_t,size_t,size_t,size_t,...) ; 
 int /*<<< orphan*/  MANAGER_IS_RELOADING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVICE_AUTO_RESTART ; 
 int /*<<< orphan*/  SERVICE_CLEANING ; 
 int /*<<< orphan*/  SERVICE_CONDITION ; 
 size_t SERVICE_DEAD ; 
 size_t SERVICE_EXITED ; 
 int /*<<< orphan*/  SERVICE_FAILED ; 
 int /*<<< orphan*/  SERVICE_FINAL_SIGKILL ; 
 int /*<<< orphan*/  SERVICE_FINAL_SIGTERM ; 
 scalar_t__ SERVICE_IDLE ; 
 int /*<<< orphan*/  SERVICE_RELOAD ; 
 int /*<<< orphan*/  SERVICE_RUNNING ; 
 scalar_t__ SERVICE_SKIP_CONDITION ; 
 size_t SERVICE_START ; 
 size_t SERVICE_START_POST ; 
 int /*<<< orphan*/  SERVICE_START_PRE ; 
 int /*<<< orphan*/  SERVICE_STOP ; 
 int /*<<< orphan*/  SERVICE_STOP_POST ; 
 int /*<<< orphan*/  SERVICE_STOP_SIGKILL ; 
 int /*<<< orphan*/  SERVICE_STOP_SIGTERM ; 
 int /*<<< orphan*/  SERVICE_STOP_WATCHDOG ; 
 scalar_t__ SERVICE_SUCCESS ; 
 TYPE_2__* UNIT (TYPE_1__*) ; 
 int UNIT_NOTIFY_RELOAD_FAILURE ; 
 int UNIT_NOTIFY_SKIP_CONDITION ; 
 int UNIT_NOTIFY_WILL_AUTO_RESTART ; 
 int /*<<< orphan*/  _SERVICE_EXEC_COMMAND_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (TYPE_2__*,int) ; 
 int /*<<< orphan*/  log_unit_debug (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 
 int /*<<< orphan*/  service_close_socket_fd (TYPE_1__*) ; 
 int /*<<< orphan*/  service_state_to_string (size_t) ; 
 int /*<<< orphan*/  service_stop_watchdog (TYPE_1__*) ; 
 int /*<<< orphan*/  service_unwatch_control_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  service_unwatch_main_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  service_unwatch_pid_file (TYPE_1__*) ; 
 int /*<<< orphan*/ * state_translation_table ; 
 int /*<<< orphan*/ * state_translation_table_idle ; 
 int /*<<< orphan*/  unit_dequeue_rewatch_pids (TYPE_2__*) ; 
 int /*<<< orphan*/  unit_notify (TYPE_2__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  unit_prune_cgroup (TYPE_2__*) ; 
 int /*<<< orphan*/  unit_unwatch_all_pids (TYPE_2__*) ; 

__attribute__((used)) static void service_set_state(Service *s, ServiceState state) {
        ServiceState old_state;
        const UnitActiveState *table;

        assert(s);

        if (s->state != state)
                bus_unit_send_pending_change_signal(UNIT(s), false);

        table = s->type == SERVICE_IDLE ? state_translation_table_idle : state_translation_table;

        old_state = s->state;
        s->state = state;

        service_unwatch_pid_file(s);

        if (!IN_SET(state,
                    SERVICE_CONDITION, SERVICE_START_PRE, SERVICE_START, SERVICE_START_POST,
                    SERVICE_RUNNING,
                    SERVICE_RELOAD,
                    SERVICE_STOP, SERVICE_STOP_WATCHDOG, SERVICE_STOP_SIGTERM, SERVICE_STOP_SIGKILL, SERVICE_STOP_POST,
                    SERVICE_FINAL_SIGTERM, SERVICE_FINAL_SIGKILL,
                    SERVICE_AUTO_RESTART,
                    SERVICE_CLEANING))
                s->timer_event_source = sd_event_source_unref(s->timer_event_source);

        if (!IN_SET(state,
                    SERVICE_START, SERVICE_START_POST,
                    SERVICE_RUNNING, SERVICE_RELOAD,
                    SERVICE_STOP, SERVICE_STOP_WATCHDOG, SERVICE_STOP_SIGTERM, SERVICE_STOP_SIGKILL, SERVICE_STOP_POST,
                    SERVICE_FINAL_SIGTERM, SERVICE_FINAL_SIGKILL)) {
                service_unwatch_main_pid(s);
                s->main_command = NULL;
        }

        if (!IN_SET(state,
                    SERVICE_CONDITION, SERVICE_START_PRE, SERVICE_START, SERVICE_START_POST,
                    SERVICE_RELOAD,
                    SERVICE_STOP, SERVICE_STOP_WATCHDOG, SERVICE_STOP_SIGTERM, SERVICE_STOP_SIGKILL, SERVICE_STOP_POST,
                    SERVICE_FINAL_SIGTERM, SERVICE_FINAL_SIGKILL,
                    SERVICE_CLEANING)) {
                service_unwatch_control_pid(s);
                s->control_command = NULL;
                s->control_command_id = _SERVICE_EXEC_COMMAND_INVALID;
        }

        if (IN_SET(state, SERVICE_DEAD, SERVICE_FAILED, SERVICE_AUTO_RESTART)) {
                unit_unwatch_all_pids(UNIT(s));
                unit_dequeue_rewatch_pids(UNIT(s));
        }

        if (!IN_SET(state,
                    SERVICE_CONDITION, SERVICE_START_PRE, SERVICE_START, SERVICE_START_POST,
                    SERVICE_RUNNING, SERVICE_RELOAD,
                    SERVICE_STOP, SERVICE_STOP_WATCHDOG, SERVICE_STOP_SIGTERM, SERVICE_STOP_SIGKILL, SERVICE_STOP_POST,
                    SERVICE_FINAL_SIGTERM, SERVICE_FINAL_SIGKILL) &&
            !(state == SERVICE_DEAD && UNIT(s)->job))
                service_close_socket_fd(s);

        if (state != SERVICE_START)
                s->exec_fd_event_source = sd_event_source_unref(s->exec_fd_event_source);

        if (!IN_SET(state, SERVICE_START_POST, SERVICE_RUNNING, SERVICE_RELOAD))
                service_stop_watchdog(s);

        /* For the inactive states unit_notify() will trim the cgroup,
         * but for exit we have to do that ourselves... */
        if (state == SERVICE_EXITED && !MANAGER_IS_RELOADING(UNIT(s)->manager))
                unit_prune_cgroup(UNIT(s));

        if (old_state != state)
                log_unit_debug(UNIT(s), "Changed %s -> %s", service_state_to_string(old_state), service_state_to_string(state));

        unit_notify(UNIT(s), table[old_state], table[state],
                    (s->reload_result == SERVICE_SUCCESS ? 0 : UNIT_NOTIFY_RELOAD_FAILURE) |
                    (s->will_auto_restart ? UNIT_NOTIFY_WILL_AUTO_RESTART : 0) |
                    (s->result == SERVICE_SKIP_CONDITION ? UNIT_NOTIFY_SKIP_CONDITION : 0));
}