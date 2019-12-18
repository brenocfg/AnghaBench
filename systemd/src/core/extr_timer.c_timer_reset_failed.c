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
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 TYPE_1__* TIMER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMER_DEAD ; 
 scalar_t__ TIMER_FAILED ; 
 int /*<<< orphan*/  TIMER_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_reset_failed(Unit *u) {
        Timer *t = TIMER(u);

        assert(t);

        if (t->state == TIMER_FAILED)
                timer_set_state(t, TIMER_DEAD);

        t->result = TIMER_SUCCESS;
}