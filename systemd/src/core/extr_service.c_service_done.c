#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_9__ {void* exec_fd_event_source; void* timer_event_source; int /*<<< orphan*/  accept_socket; int /*<<< orphan*/  peer; void* usb_function_strings; void* usb_function_descriptors; void* bus_name_owner; void* bus_name; int /*<<< orphan*/  success_status; int /*<<< orphan*/  restart_force_status; int /*<<< orphan*/  restart_prevent_status; int /*<<< orphan*/  dynamic_creds; int /*<<< orphan*/ * main_command; int /*<<< orphan*/ * control_command; int /*<<< orphan*/  exec_command; int /*<<< orphan*/  exec_runtime; void* status_text; void* pid_file; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SERVICE_EXEC_COMMAND_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dynamic_creds_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_command_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_runtime_unref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit_status_set_free (int /*<<< orphan*/ *) ; 
 void* mfree (void*) ; 
 void* sd_event_source_unref (void*) ; 
 int /*<<< orphan*/  service_close_socket_fd (TYPE_1__*) ; 
 int /*<<< orphan*/  service_release_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_stop_watchdog (TYPE_1__*) ; 
 int /*<<< orphan*/  service_unwatch_control_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  service_unwatch_main_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  service_unwatch_pid_file (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_peer_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_ref_unset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_unwatch_bus_name (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void service_done(Unit *u) {
        Service *s = SERVICE(u);

        assert(s);

        s->pid_file = mfree(s->pid_file);
        s->status_text = mfree(s->status_text);

        s->exec_runtime = exec_runtime_unref(s->exec_runtime, false);
        exec_command_free_array(s->exec_command, _SERVICE_EXEC_COMMAND_MAX);
        s->control_command = NULL;
        s->main_command = NULL;

        dynamic_creds_unref(&s->dynamic_creds);

        exit_status_set_free(&s->restart_prevent_status);
        exit_status_set_free(&s->restart_force_status);
        exit_status_set_free(&s->success_status);

        /* This will leak a process, but at least no memory or any of
         * our resources */
        service_unwatch_main_pid(s);
        service_unwatch_control_pid(s);
        service_unwatch_pid_file(s);

        if (s->bus_name)  {
                unit_unwatch_bus_name(u, s->bus_name);
                s->bus_name = mfree(s->bus_name);
        }

        s->bus_name_owner = mfree(s->bus_name_owner);

        s->usb_function_descriptors = mfree(s->usb_function_descriptors);
        s->usb_function_strings = mfree(s->usb_function_strings);

        service_close_socket_fd(s);
        s->peer = socket_peer_unref(s->peer);

        unit_ref_unset(&s->accept_socket);

        service_stop_watchdog(s);

        s->timer_event_source = sd_event_source_unref(s->timer_event_source);
        s->exec_fd_event_source = sd_event_source_unref(s->exec_fd_event_source);

        service_release_resources(u);
}