#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_3__ {int /*<<< orphan*/  timer_event_source; int /*<<< orphan*/  controller_track; int /*<<< orphan*/  controller; } ;
typedef  TYPE_1__ Scope ;

/* Variables and functions */
 TYPE_1__* SCOPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_track_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scope_done(Unit *u) {
        Scope *s = SCOPE(u);

        assert(u);

        s->controller = mfree(s->controller);
        s->controller_track = sd_bus_track_unref(s->controller_track);

        s->timer_event_source = sd_event_source_unref(s->timer_event_source);
}