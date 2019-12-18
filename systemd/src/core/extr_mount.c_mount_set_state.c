#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; scalar_t__ reload_result; int /*<<< orphan*/  control_command_id; int /*<<< orphan*/ * control_command; int /*<<< orphan*/  timer_event_source; } ;
typedef  scalar_t__ MountState ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNT_STATE_WITH_PROCESS (scalar_t__) ; 
 scalar_t__ MOUNT_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  UNIT_NOTIFY_RELOAD_FAILURE ; 
 int /*<<< orphan*/  _MOUNT_EXEC_COMMAND_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_state_to_string (scalar_t__) ; 
 int /*<<< orphan*/  mount_unwatch_control_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * state_translation_table ; 
 int /*<<< orphan*/  unit_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mount_set_state(Mount *m, MountState state) {
        MountState old_state;
        assert(m);

        if (m->state != state)
                bus_unit_send_pending_change_signal(UNIT(m), false);

        old_state = m->state;
        m->state = state;

        if (!MOUNT_STATE_WITH_PROCESS(state)) {
                m->timer_event_source = sd_event_source_unref(m->timer_event_source);
                mount_unwatch_control_pid(m);
                m->control_command = NULL;
                m->control_command_id = _MOUNT_EXEC_COMMAND_INVALID;
        }

        if (state != old_state)
                log_unit_debug(UNIT(m), "Changed %s -> %s", mount_state_to_string(old_state), mount_state_to_string(state));

        unit_notify(UNIT(m), state_translation_table[old_state], state_translation_table[state],
                    m->reload_result == MOUNT_SUCCESS ? 0 : UNIT_NOTIFY_RELOAD_FAILURE);
}