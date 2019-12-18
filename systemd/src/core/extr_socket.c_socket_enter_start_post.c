#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t control_command_id; int /*<<< orphan*/  control_pid; scalar_t__ control_command; scalar_t__* exec_command; } ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 size_t SOCKET_EXEC_START_POST ; 
 int /*<<< orphan*/  SOCKET_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SOCKET_START_POST ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  socket_enter_listening (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_enter_stop_pre (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int socket_spawn (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_unwatch_control_pid (TYPE_1__*) ; 

__attribute__((used)) static void socket_enter_start_post(Socket *s) {
        int r;
        assert(s);

        socket_unwatch_control_pid(s);
        s->control_command_id = SOCKET_EXEC_START_POST;
        s->control_command = s->exec_command[SOCKET_EXEC_START_POST];

        if (s->control_command) {
                r = socket_spawn(s, s->control_command, &s->control_pid);
                if (r < 0) {
                        log_unit_warning_errno(UNIT(s), r, "Failed to run 'start-post' task: %m");
                        goto fail;
                }

                socket_set_state(s, SOCKET_START_POST);
        } else
                socket_enter_listening(s);

        return;

fail:
        socket_enter_stop_pre(s, SOCKET_FAILURE_RESOURCES);
}