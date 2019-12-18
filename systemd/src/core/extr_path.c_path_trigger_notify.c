#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ load_state; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_12__ {scalar_t__ state; int /*<<< orphan*/  inotify_triggered; } ;
typedef  TYPE_2__ Path ;

/* Variables and functions */
 TYPE_2__* PATH (TYPE_1__*) ; 
 scalar_t__ PATH_RUNNING ; 
 int /*<<< orphan*/  UNIT (TYPE_2__*) ; 
 scalar_t__ UNIT_IS_INACTIVE_OR_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_LOADED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  path_enter_waiting (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_active_state (TYPE_1__*) ; 

__attribute__((used)) static void path_trigger_notify(Unit *u, Unit *other) {
        Path *p = PATH(u);

        assert(u);
        assert(other);

        /* Invoked whenever the unit we trigger changes state or gains
         * or loses a job */

        if (other->load_state != UNIT_LOADED)
                return;

        if (p->state == PATH_RUNNING &&
            UNIT_IS_INACTIVE_OR_FAILED(unit_active_state(other))) {
                log_unit_debug(UNIT(p), "Got notified about unit deactivation.");

                /* Hmm, so inotify was triggered since the
                 * last activation, so I guess we need to
                 * recheck what is going on. */
                path_enter_waiting(p, false, p->inotify_triggered);
        }
}