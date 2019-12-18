#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_synthesize_cgroup_empty_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_tidy_watch_pids (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_watch_all_pids (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_rewatch_pids_event(sd_event_source *s, void *userdata) {
        Unit *u = userdata;

        assert(s);
        assert(u);

        unit_tidy_watch_pids(u);
        unit_watch_all_pids(u);

        /* If the PID set is empty now, then let's finish this off. */
        unit_synthesize_cgroup_empty_event(u);

        return 0;
}