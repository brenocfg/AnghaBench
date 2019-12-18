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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 TYPE_1__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* TIMER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMER_ELAPSED ; 
 int /*<<< orphan*/  TIMER_RUNNING ; 
 int /*<<< orphan*/  TIMER_SUCCESS ; 
 int /*<<< orphan*/  TIMER_WAITING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int timer_stop(Unit *u) {
        Timer *t = TIMER(u);

        assert(t);
        assert(IN_SET(t->state, TIMER_WAITING, TIMER_RUNNING, TIMER_ELAPSED));

        timer_enter_dead(t, TIMER_SUCCESS);
        return 1;
}