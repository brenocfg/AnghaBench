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
struct TYPE_5__ {int /*<<< orphan*/  pending_switch; } ;
typedef  int /*<<< orphan*/  Session ;
typedef  TYPE_1__ Seat ;

/* Variables and functions */
 int /*<<< orphan*/ * TAKE_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  seat_set_active (TYPE_1__*,int /*<<< orphan*/ *) ; 

void seat_complete_switch(Seat *s) {
        Session *session;

        assert(s);

        /* if no session-switch is pending or if it got canceled, do nothing */
        if (!s->pending_switch)
                return;

        session = TAKE_PTR(s->pending_switch);

        seat_set_active(s, session);
}