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
struct TYPE_6__ {int was_abandoned; int /*<<< orphan*/  controller_track; int /*<<< orphan*/  controller; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Scope ;

/* Variables and functions */
 int EPERM ; 
 int ESTALE ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCOPE_ABANDONED ; 
 int /*<<< orphan*/  SCOPE_RUNNING ; 
 int /*<<< orphan*/  SPECIAL_INIT_SCOPE ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_track_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_enqueue_rewatch_pids (int /*<<< orphan*/ ) ; 
 scalar_t__ unit_has_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int scope_abandon(Scope *s) {
        assert(s);

        if (unit_has_name(UNIT(s), SPECIAL_INIT_SCOPE))
                return -EPERM;

        if (!IN_SET(s->state, SCOPE_RUNNING, SCOPE_ABANDONED))
                return -ESTALE;

        s->was_abandoned = true;

        s->controller = mfree(s->controller);
        s->controller_track = sd_bus_track_unref(s->controller_track);

        scope_set_state(s, SCOPE_ABANDONED);

        /* The client is no longer watching the remaining processes, so let's step in here, under the assumption that
         * the remaining processes will be sooner or later reassigned to us as parent. */
        (void) unit_enqueue_rewatch_pids(UNIT(s));

        return 0;
}