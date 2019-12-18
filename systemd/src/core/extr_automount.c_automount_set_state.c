#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ state; } ;
typedef  scalar_t__ AutomountState ;
typedef  TYPE_1__ Automount ;

/* Variables and functions */
 scalar_t__ AUTOMOUNT_RUNNING ; 
 int /*<<< orphan*/  AUTOMOUNT_WAITING ; 
 int /*<<< orphan*/  IN_SET (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  automount_state_to_string (scalar_t__) ; 
 int /*<<< orphan*/  automount_stop_expire (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * state_translation_table ; 
 int /*<<< orphan*/  unit_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmount_autofs (TYPE_1__*) ; 

__attribute__((used)) static void automount_set_state(Automount *a, AutomountState state) {
        AutomountState old_state;
        assert(a);

        if (a->state != state)
                bus_unit_send_pending_change_signal(UNIT(a), false);

        old_state = a->state;
        a->state = state;

        if (state != AUTOMOUNT_RUNNING)
                automount_stop_expire(a);

        if (!IN_SET(state, AUTOMOUNT_WAITING, AUTOMOUNT_RUNNING))
                unmount_autofs(a);

        if (state != old_state)
                log_unit_debug(UNIT(a), "Changed %s -> %s", automount_state_to_string(old_state), automount_state_to_string(state));

        unit_notify(UNIT(a), state_translation_table[old_state], state_translation_table[state], 0);
}