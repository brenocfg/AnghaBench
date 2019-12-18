#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {scalar_t__ realtime; scalar_t__ monotonic; } ;
struct TYPE_5__ {TYPE_1__ last_trigger; int /*<<< orphan*/  result; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ Timer ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  FDSet ;

/* Variables and functions */
 TYPE_2__* TIMER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serialize_item (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_usec (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  timer_result_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int timer_serialize(Unit *u, FILE *f, FDSet *fds) {
        Timer *t = TIMER(u);

        assert(u);
        assert(f);
        assert(fds);

        (void) serialize_item(f, "state", timer_state_to_string(t->state));
        (void) serialize_item(f, "result", timer_result_to_string(t->result));

        if (t->last_trigger.realtime > 0)
                (void) serialize_usec(f, "last-trigger-realtime", t->last_trigger.realtime);

        if (t->last_trigger.monotonic > 0)
                (void) serialize_usec(f, "last-trigger-monotonic", t->last_trigger.monotonic);

        return 0;
}