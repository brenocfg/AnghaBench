#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t control_command_id; int /*<<< orphan*/  control_pid; int /*<<< orphan*/  timeout_start_usec; scalar_t__ control_command; scalar_t__* exec_command; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int EXEC_APPLY_CHROOT ; 
 int EXEC_APPLY_SANDBOXING ; 
 int EXEC_APPLY_TTY_STDIN ; 
 int EXEC_IS_CONTROL ; 
 int /*<<< orphan*/  SERVICE_CONDITION ; 
 size_t SERVICE_EXEC_CONDITION ; 
 int /*<<< orphan*/  SERVICE_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int service_adverse_to_leftover_processes (TYPE_1__*) ; 
 int /*<<< orphan*/  service_enter_dead (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  service_enter_start_pre (TYPE_1__*) ; 
 int /*<<< orphan*/  service_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int service_spawn (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_unwatch_control_pid (TYPE_1__*) ; 

__attribute__((used)) static void service_enter_condition(Service *s) {
        int r;

        assert(s);

        service_unwatch_control_pid(s);

        s->control_command = s->exec_command[SERVICE_EXEC_CONDITION];
        if (s->control_command) {

                r = service_adverse_to_leftover_processes(s);
                if (r < 0)
                        goto fail;

                s->control_command_id = SERVICE_EXEC_CONDITION;

                r = service_spawn(s,
                                  s->control_command,
                                  s->timeout_start_usec,
                                  EXEC_APPLY_SANDBOXING|EXEC_APPLY_CHROOT|EXEC_IS_CONTROL|EXEC_APPLY_TTY_STDIN,
                                  &s->control_pid);

                if (r < 0)
                        goto fail;

                service_set_state(s, SERVICE_CONDITION);
        } else
                service_enter_start_pre(s);

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to run 'exec-condition' task: %m");
        service_enter_dead(s, SERVICE_FAILURE_RESOURCES, true);
}