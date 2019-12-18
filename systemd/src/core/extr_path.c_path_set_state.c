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
struct TYPE_6__ {scalar_t__ state; scalar_t__ inotify_triggered; } ;
typedef  scalar_t__ PathState ;
typedef  TYPE_1__ Path ;

/* Variables and functions */
 scalar_t__ PATH_RUNNING ; 
 scalar_t__ PATH_WAITING ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_pending_change_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_state_to_string (scalar_t__) ; 
 int /*<<< orphan*/  path_unwatch (TYPE_1__*) ; 
 int /*<<< orphan*/ * state_translation_table ; 
 int /*<<< orphan*/  unit_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void path_set_state(Path *p, PathState state) {
        PathState old_state;
        assert(p);

        if (p->state != state)
                bus_unit_send_pending_change_signal(UNIT(p), false);

        old_state = p->state;
        p->state = state;

        if (state != PATH_WAITING &&
            (state != PATH_RUNNING || p->inotify_triggered))
                path_unwatch(p);

        if (state != old_state)
                log_unit_debug(UNIT(p), "Changed %s -> %s", path_state_to_string(old_state), path_state_to_string(state));

        unit_notify(UNIT(p), state_translation_table[old_state], state_translation_table[state], 0);
}