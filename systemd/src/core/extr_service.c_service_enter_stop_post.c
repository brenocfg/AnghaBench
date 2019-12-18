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
struct TYPE_9__ {scalar_t__ result; size_t control_command_id; int /*<<< orphan*/  control_pid; int /*<<< orphan*/  timeout_stop_usec; scalar_t__ control_command; scalar_t__* exec_command; } ;
typedef  scalar_t__ ServiceResult ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int EXEC_APPLY_CHROOT ; 
 int EXEC_APPLY_SANDBOXING ; 
 int EXEC_APPLY_TTY_STDIN ; 
 int EXEC_CONTROL_CGROUP ; 
 int EXEC_IS_CONTROL ; 
 int EXEC_SETENV_RESULT ; 
 size_t SERVICE_EXEC_STOP_POST ; 
 scalar_t__ SERVICE_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SERVICE_FINAL_SIGTERM ; 
 int /*<<< orphan*/  SERVICE_STOP_POST ; 
 scalar_t__ SERVICE_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  service_enter_signal (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  service_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int service_spawn (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_unwatch_control_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_enqueue_rewatch_pids (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_enter_stop_post(Service *s, ServiceResult f) {
        int r;
        assert(s);

        if (s->result == SERVICE_SUCCESS)
                s->result = f;

        service_unwatch_control_pid(s);
        (void) unit_enqueue_rewatch_pids(UNIT(s));

        s->control_command = s->exec_command[SERVICE_EXEC_STOP_POST];
        if (s->control_command) {
                s->control_command_id = SERVICE_EXEC_STOP_POST;

                r = service_spawn(s,
                                  s->control_command,
                                  s->timeout_stop_usec,
                                  EXEC_APPLY_SANDBOXING|EXEC_APPLY_CHROOT|EXEC_APPLY_TTY_STDIN|EXEC_IS_CONTROL|EXEC_SETENV_RESULT|EXEC_CONTROL_CGROUP,
                                  &s->control_pid);
                if (r < 0)
                        goto fail;

                service_set_state(s, SERVICE_STOP_POST);
        } else
                service_enter_signal(s, SERVICE_FINAL_SIGTERM, SERVICE_SUCCESS);

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to run 'stop-post' task: %m");
        service_enter_signal(s, SERVICE_FINAL_SIGTERM, SERVICE_FAILURE_RESOURCES);
}