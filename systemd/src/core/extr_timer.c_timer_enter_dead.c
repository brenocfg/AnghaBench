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
typedef  scalar_t__ TimerResult ;
struct TYPE_6__ {scalar_t__ result; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_DEAD ; 
 int /*<<< orphan*/  TIMER_FAILED ; 
 scalar_t__ TIMER_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_result_to_string (scalar_t__) ; 
 int /*<<< orphan*/  timer_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_log_result (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_enter_dead(Timer *t, TimerResult f) {
        assert(t);

        if (t->result == TIMER_SUCCESS)
                t->result = f;

        unit_log_result(UNIT(t), t->result == TIMER_SUCCESS, timer_result_to_string(t->result));
        timer_set_state(t, t->result != TIMER_SUCCESS ? TIMER_FAILED : TIMER_DEAD);
}