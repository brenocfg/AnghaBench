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
struct TYPE_6__ {scalar_t__ remain_after_elapse; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_ELAPSED ; 
 int /*<<< orphan*/  TIMER_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_enter_elapsed(Timer *t, bool leave_around) {
        assert(t);

        /* If a unit is marked with RemainAfterElapse=yes we leave it
         * around even after it elapsed once, so that starting it
         * later again does not necessarily mean immediate
         * retriggering. We unconditionally leave units with
         * TIMER_UNIT_ACTIVE or TIMER_UNIT_INACTIVE triggers around,
         * since they might be restarted automatically at any time
         * later on. */

        if (t->remain_after_elapse || leave_around)
                timer_set_state(t, TIMER_ELAPSED);
        else
                timer_enter_dead(t, TIMER_SUCCESS);
}