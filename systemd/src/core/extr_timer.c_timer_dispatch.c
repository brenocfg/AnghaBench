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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_6__ {scalar_t__ state; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 TYPE_1__* TIMER (void*) ; 
 scalar_t__ TIMER_WAITING ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  timer_enter_running (TYPE_1__*) ; 

__attribute__((used)) static int timer_dispatch(sd_event_source *s, uint64_t usec, void *userdata) {
        Timer *t = TIMER(userdata);

        assert(t);

        if (t->state != TIMER_WAITING)
                return 0;

        log_unit_debug(UNIT(t), "Timer elapsed.");
        timer_enter_running(t);
        return 0;
}