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
struct TYPE_9__ {scalar_t__ result; size_t control_command_id; int /*<<< orphan*/  control_pid; scalar_t__ control_command; scalar_t__* exec_command; } ;
typedef  scalar_t__ SocketResult ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 size_t SOCKET_EXEC_STOP_POST ; 
 scalar_t__ SOCKET_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGTERM ; 
 int /*<<< orphan*/  SOCKET_STOP_POST ; 
 scalar_t__ SOCKET_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  socket_enter_signal (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  socket_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int socket_spawn (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_unwatch_control_pid (TYPE_1__*) ; 

__attribute__((used)) static void socket_enter_stop_post(Socket *s, SocketResult f) {
        int r;
        assert(s);

        if (s->result == SOCKET_SUCCESS)
                s->result = f;

        socket_unwatch_control_pid(s);
        s->control_command_id = SOCKET_EXEC_STOP_POST;
        s->control_command = s->exec_command[SOCKET_EXEC_STOP_POST];

        if (s->control_command) {
                r = socket_spawn(s, s->control_command, &s->control_pid);
                if (r < 0)
                        goto fail;

                socket_set_state(s, SOCKET_STOP_POST);
        } else
                socket_enter_signal(s, SOCKET_FINAL_SIGTERM, SOCKET_SUCCESS);

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to run 'stop-post' task: %m");
        socket_enter_signal(s, SOCKET_FINAL_SIGTERM, SOCKET_FAILURE_RESOURCES);
}