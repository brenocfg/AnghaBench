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
struct TYPE_6__ {scalar_t__ state; } ;
typedef  scalar_t__ DeviceState ;
typedef  TYPE_1__ Device ;

/* Variables and functions */
 scalar_t__ DEVICE_DEAD ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_state_to_string (scalar_t__) ; 
 int /*<<< orphan*/  device_unset_sysfs (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * state_translation_table ; 
 int /*<<< orphan*/  unit_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_set_state(Device *d, DeviceState state) {
        DeviceState old_state;
        assert(d);

        if (d->state != state)
                bus_unit_send_pending_change_signal(UNIT(d), false);

        old_state = d->state;
        d->state = state;

        if (state == DEVICE_DEAD)
                device_unset_sysfs(d);

        if (state != old_state)
                log_unit_debug(UNIT(d), "Changed %s -> %s", device_state_to_string(old_state), device_state_to_string(state));

        unit_notify(UNIT(d), state_translation_table[old_state], state_translation_table[state], 0);
}