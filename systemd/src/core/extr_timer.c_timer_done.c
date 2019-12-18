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
struct TYPE_5__ {int /*<<< orphan*/  stamp_path; void* realtime_event_source; void* monotonic_event_source; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 TYPE_1__* TIMER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 
 int /*<<< orphan*/  timer_free_values (TYPE_1__*) ; 

__attribute__((used)) static void timer_done(Unit *u) {
        Timer *t = TIMER(u);

        assert(t);

        timer_free_values(t);

        t->monotonic_event_source = sd_event_source_unref(t->monotonic_event_source);
        t->realtime_event_source = sd_event_source_unref(t->realtime_event_source);

        free(t->stamp_path);
}