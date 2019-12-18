#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {scalar_t__ state; } ;
typedef  scalar_t__ SliceState ;
typedef  TYPE_1__ Slice ;

/* Variables and functions */
 TYPE_2__* UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (TYPE_2__*,int) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slice_state_to_string (scalar_t__) ; 
 int /*<<< orphan*/ * state_translation_table ; 
 int /*<<< orphan*/  unit_notify (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slice_set_state(Slice *t, SliceState state) {
        SliceState old_state;
        assert(t);

        if (t->state != state)
                bus_unit_send_pending_change_signal(UNIT(t), false);

        old_state = t->state;
        t->state = state;

        if (state != old_state)
                log_debug("%s changed %s -> %s",
                          UNIT(t)->id,
                          slice_state_to_string(old_state),
                          slice_state_to_string(state));

        unit_notify(UNIT(t), state_translation_table[old_state], state_translation_table[state], 0);
}