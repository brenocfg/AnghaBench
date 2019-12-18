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
struct TYPE_9__ {size_t control_command_id; int /*<<< orphan*/  reload_result; int /*<<< orphan*/  control_pid; int /*<<< orphan*/  timeout_start_usec; scalar_t__ control_command; scalar_t__* exec_command; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int EXEC_APPLY_CHROOT ; 
 int EXEC_APPLY_SANDBOXING ; 
 int EXEC_CONTROL_CGROUP ; 
 int EXEC_IS_CONTROL ; 
 size_t SERVICE_EXEC_RELOAD ; 
 int /*<<< orphan*/  SERVICE_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SERVICE_RELOAD ; 
 int /*<<< orphan*/  SERVICE_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  service_enter_running (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int service_spawn (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_unwatch_control_pid (TYPE_1__*) ; 

__attribute__((used)) static void service_enter_reload(Service *s) {
        int r;

        assert(s);

        service_unwatch_control_pid(s);
        s->reload_result = SERVICE_SUCCESS;

        s->control_command = s->exec_command[SERVICE_EXEC_RELOAD];
        if (s->control_command) {
                s->control_command_id = SERVICE_EXEC_RELOAD;

                r = service_spawn(s,
                                  s->control_command,
                                  s->timeout_start_usec,
                                  EXEC_APPLY_SANDBOXING|EXEC_APPLY_CHROOT|EXEC_IS_CONTROL|EXEC_CONTROL_CGROUP,
                                  &s->control_pid);
                if (r < 0)
                        goto fail;

                service_set_state(s, SERVICE_RELOAD);
        } else
                service_enter_running(s, SERVICE_SUCCESS);

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to run 'reload' task: %m");
        s->reload_result = SERVICE_FAILURE_RESOURCES;
        service_enter_running(s, SERVICE_SUCCESS);
}