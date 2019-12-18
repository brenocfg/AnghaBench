#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ state; int /*<<< orphan*/  control_command_id; int /*<<< orphan*/ * control_command; int /*<<< orphan*/  timer_event_source; } ;
typedef  scalar_t__ SocketState ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 int /*<<< orphan*/  IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  SOCKET_CLEANING ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGKILL ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGTERM ; 
 scalar_t__ SOCKET_LISTENING ; 
 int /*<<< orphan*/  SOCKET_RUNNING ; 
 int /*<<< orphan*/  SOCKET_START_CHOWN ; 
 int /*<<< orphan*/  SOCKET_START_POST ; 
 int /*<<< orphan*/  SOCKET_START_PRE ; 
 int /*<<< orphan*/  SOCKET_STOP_POST ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE_SIGKILL ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE_SIGTERM ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  _SOCKET_EXEC_COMMAND_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_close_fds (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_state_to_string (scalar_t__) ; 
 int /*<<< orphan*/  socket_unwatch_control_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_unwatch_fds (TYPE_1__*) ; 
 int /*<<< orphan*/ * state_translation_table ; 
 int /*<<< orphan*/  unit_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socket_set_state(Socket *s, SocketState state) {
        SocketState old_state;
        assert(s);

        if (s->state != state)
                bus_unit_send_pending_change_signal(UNIT(s), false);

        old_state = s->state;
        s->state = state;

        if (!IN_SET(state,
                    SOCKET_START_PRE,
                    SOCKET_START_CHOWN,
                    SOCKET_START_POST,
                    SOCKET_STOP_PRE,
                    SOCKET_STOP_PRE_SIGTERM,
                    SOCKET_STOP_PRE_SIGKILL,
                    SOCKET_STOP_POST,
                    SOCKET_FINAL_SIGTERM,
                    SOCKET_FINAL_SIGKILL,
                    SOCKET_CLEANING)) {

                s->timer_event_source = sd_event_source_unref(s->timer_event_source);
                socket_unwatch_control_pid(s);
                s->control_command = NULL;
                s->control_command_id = _SOCKET_EXEC_COMMAND_INVALID;
        }

        if (state != SOCKET_LISTENING)
                socket_unwatch_fds(s);

        if (!IN_SET(state,
                    SOCKET_START_CHOWN,
                    SOCKET_START_POST,
                    SOCKET_LISTENING,
                    SOCKET_RUNNING,
                    SOCKET_STOP_PRE,
                    SOCKET_STOP_PRE_SIGTERM,
                    SOCKET_STOP_PRE_SIGKILL,
                    SOCKET_CLEANING))
                socket_close_fds(s);

        if (state != old_state)
                log_unit_debug(UNIT(s), "Changed %s -> %s", socket_state_to_string(old_state), socket_state_to_string(state));

        unit_notify(UNIT(s), state_translation_table[old_state], state_translation_table[state], 0);
}