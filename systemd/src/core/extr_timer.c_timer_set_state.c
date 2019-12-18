#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TimerState ;
struct TYPE_5__ {scalar_t__ state; void* next_elapse_realtime; void* next_elapse_monotonic_or_boottime; void* realtime_event_source; void* monotonic_event_source; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 scalar_t__ TIMER_WAITING ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 void* USEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 
 int /*<<< orphan*/ * state_translation_table ; 
 int /*<<< orphan*/  timer_state_to_string (scalar_t__) ; 
 int /*<<< orphan*/  unit_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_set_state(Timer *t, TimerState state) {
        TimerState old_state;
        assert(t);

        if (t->state != state)
                bus_unit_send_pending_change_signal(UNIT(t), false);

        old_state = t->state;
        t->state = state;

        if (state != TIMER_WAITING) {
                t->monotonic_event_source = sd_event_source_unref(t->monotonic_event_source);
                t->realtime_event_source = sd_event_source_unref(t->realtime_event_source);
                t->next_elapse_monotonic_or_boottime = USEC_INFINITY;
                t->next_elapse_realtime = USEC_INFINITY;
        }

        if (state != old_state)
                log_unit_debug(UNIT(t), "Changed %s -> %s", timer_state_to_string(old_state), timer_state_to_string(state));

        unit_notify(UNIT(t), state_translation_table[old_state], state_translation_table[state], 0);
}