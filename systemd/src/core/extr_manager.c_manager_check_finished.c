#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ timestamps; int /*<<< orphan*/ * confirm_spawn; scalar_t__ jobs_in_progress_event_source; int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ JOBS_IN_PROGRESS_WAIT_USEC ; 
 scalar_t__ MANAGER_IS_FINISHED (TYPE_1__*) ; 
 scalar_t__ MANAGER_IS_RELOADING (TYPE_1__*) ; 
 int /*<<< orphan*/  MANAGER_IS_RUNNING (TYPE_1__*) ; 
 scalar_t__ MANAGER_TIMESTAMP_FINISH ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dual_timestamp_get (scalar_t__) ; 
 scalar_t__ hashmap_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_check_basic_target (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_close_ask_password (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_close_idle_pipe (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_flip_auto_status (TYPE_1__*,int) ; 
 int /*<<< orphan*/  manager_invalidate_startup_units (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_notify_finished (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_set_first_boot (TYPE_1__*,int) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_set_time (scalar_t__,scalar_t__) ; 

void manager_check_finished(Manager *m) {
        assert(m);

        if (MANAGER_IS_RELOADING(m))
                return;

        /* Verify that we have entered the event loop already, and not left it again. */
        if (!MANAGER_IS_RUNNING(m))
                return;

        manager_check_basic_target(m);

        if (hashmap_size(m->jobs) > 0) {
                if (m->jobs_in_progress_event_source)
                        /* Ignore any failure, this is only for feedback */
                        (void) sd_event_source_set_time(m->jobs_in_progress_event_source, now(CLOCK_MONOTONIC) + JOBS_IN_PROGRESS_WAIT_USEC);

                return;
        }

        manager_flip_auto_status(m, false);

        /* Notify Type=idle units that we are done now */
        manager_close_idle_pipe(m);

        /* Turn off confirm spawn now */
        m->confirm_spawn = NULL;

        /* No need to update ask password status when we're going non-interactive */
        manager_close_ask_password(m);

        /* This is no longer the first boot */
        manager_set_first_boot(m, false);

        if (MANAGER_IS_FINISHED(m))
                return;

        dual_timestamp_get(m->timestamps + MANAGER_TIMESTAMP_FINISH);

        manager_notify_finished(m);

        manager_invalidate_startup_units(m);
}