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
struct TYPE_10__ {scalar_t__ result; int /*<<< orphan*/  timeout_usec; int /*<<< orphan*/  control_pid; int /*<<< orphan*/  kill_context; } ;
typedef  int /*<<< orphan*/  SocketState ;
typedef  scalar_t__ SocketResult ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCKET_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGKILL ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGTERM ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE_SIGKILL ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE_SIGTERM ; 
 scalar_t__ SOCKET_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int socket_arm_timer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_enter_dead (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  socket_enter_stop_post (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  socket_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_to_kill_operation (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int unit_kill_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socket_enter_signal(Socket *s, SocketState state, SocketResult f) {
        int r;

        assert(s);

        if (s->result == SOCKET_SUCCESS)
                s->result = f;

        r = unit_kill_context(
                        UNIT(s),
                        &s->kill_context,
                        state_to_kill_operation(s, state),
                        -1,
                        s->control_pid,
                        false);
        if (r < 0)
                goto fail;

        if (r > 0) {
                r = socket_arm_timer(s, usec_add(now(CLOCK_MONOTONIC), s->timeout_usec));
                if (r < 0)
                        goto fail;

                socket_set_state(s, state);
        } else if (state == SOCKET_STOP_PRE_SIGTERM)
                socket_enter_signal(s, SOCKET_STOP_PRE_SIGKILL, SOCKET_SUCCESS);
        else if (state == SOCKET_STOP_PRE_SIGKILL)
                socket_enter_stop_post(s, SOCKET_SUCCESS);
        else if (state == SOCKET_FINAL_SIGTERM)
                socket_enter_signal(s, SOCKET_FINAL_SIGKILL, SOCKET_SUCCESS);
        else
                socket_enter_dead(s, SOCKET_SUCCESS);

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to kill processes: %m");

        if (IN_SET(state, SOCKET_STOP_PRE_SIGTERM, SOCKET_STOP_PRE_SIGKILL))
                socket_enter_stop_post(s, SOCKET_FAILURE_RESOURCES);
        else
                socket_enter_dead(s, SOCKET_FAILURE_RESOURCES);
}