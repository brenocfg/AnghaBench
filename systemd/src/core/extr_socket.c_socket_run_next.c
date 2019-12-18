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
struct TYPE_11__ {scalar_t__ state; int /*<<< orphan*/  control_pid; struct TYPE_11__* control_command; struct TYPE_11__* command_next; } ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGTERM ; 
 scalar_t__ SOCKET_START_POST ; 
 scalar_t__ SOCKET_STOP_POST ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  socket_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_enter_signal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_enter_stop_pre (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int socket_spawn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_unwatch_control_pid (TYPE_1__*) ; 

__attribute__((used)) static void socket_run_next(Socket *s) {
        int r;

        assert(s);
        assert(s->control_command);
        assert(s->control_command->command_next);

        socket_unwatch_control_pid(s);

        s->control_command = s->control_command->command_next;

        r = socket_spawn(s, s->control_command, &s->control_pid);
        if (r < 0)
                goto fail;

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to run next task: %m");

        if (s->state == SOCKET_START_POST)
                socket_enter_stop_pre(s, SOCKET_FAILURE_RESOURCES);
        else if (s->state == SOCKET_STOP_POST)
                socket_enter_dead(s, SOCKET_FAILURE_RESOURCES);
        else
                socket_enter_signal(s, SOCKET_FINAL_SIGTERM, SOCKET_FAILURE_RESOURCES);
}