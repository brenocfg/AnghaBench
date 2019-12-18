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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_5__ {scalar_t__ state; scalar_t__ on_timezone_change; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 TYPE_1__* TIMER (int /*<<< orphan*/ *) ; 
 scalar_t__ TIMER_WAITING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  timer_enter_running (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_enter_waiting (TYPE_1__*,int) ; 

__attribute__((used)) static void timer_timezone_change(Unit *u) {
        Timer *t = TIMER(u);

        assert(u);

        if (t->state != TIMER_WAITING)
                return;

        if (t->on_timezone_change) {
                log_unit_debug(u, "Timezone change, triggering activation.");
                timer_enter_running(t);
        } else {
                log_unit_debug(u, "Timezone change, recalculating next elapse.");
                timer_enter_waiting(t, false);
        }
}